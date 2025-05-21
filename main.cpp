#include <asio.hpp>
// #include <asio/experimental/awaitable_operators.hpp>
#include <fmt/format.h>
#include <array>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <sstream>

using asio::ip::udp;
using asio::awaitable;
using asio::use_awaitable;
using asio::co_spawn;
using asio::detached;
namespace this_coro = asio::this_coro;

class UdpServer {
public:
    UdpServer(asio::io_context& io, uint16_t port)
        : executor_(io.get_executor()),
          socket_(executor_, udp::endpoint(udp::v4(), port)),
          running_(true) {}

    awaitable<void> start() {
        fmt::print("UDP server started on port {}\n", socket_.local_endpoint().port());
        while (running_) {
            std::array<char, 1500> buffer;
            udp::endpoint sender;

            std::size_t bytes = co_await socket_.async_receive_from(
                asio::buffer(buffer), sender, use_awaitable);

            std::string msg(buffer.data(), bytes);
            output_log(sender, msg);
        }
    }

    void stop() {
        running_ = false;
        socket_.close();
    }

private:
    void output_log(const udp::endpoint& sender, const std::string& msg) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now_time), "%F %T")
            << '.' << std::setfill('0') << std::setw(3) << ms.count();

        fmt::print(
            "[{}] from {}:{} [{} bytes] -> {}\n",
            oss.str(),
            sender.address().to_string(),
            sender.port(),
            msg.size(),
            msg
        );
    }

    asio::any_io_executor executor_;
    udp::socket socket_;
    std::atomic<bool> running_;
};

int main() {
    try {
        fmt::print("PID: {}\n", getpid());

        asio::io_context io;
        UdpServer server(io, 8004);

        co_spawn(io.get_executor(), server.start(), detached);
        io.run();
    }
    catch (const std::exception& e) {
        fmt::print("例外: {}\n", e.what());
    }
}
