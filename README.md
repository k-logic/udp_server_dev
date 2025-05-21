# UDP Receive Server

This project is a minimal C++23-based asynchronous UDP server using [ASIO (standalone)](https://think-async.com/Asio/) and [fmt](https://fmt.dev/).

It supports:

- Asynchronous UDP reception (`co_await`)
- Signal-based lifecycle control:
no commit

---

## Development Environment
- Device	Apple M1 Pro
- macOS Version	macOS 14.6.1

---

## Requirements

- C++ compiler with C++23 support (`g++ >= 12`, `clang++ >= 15`)
- CMake >= 3.16
- [ASIO (header-only)](https://github.com/chriskohlhoff/asio)
- [fmtlib (header-only)](https://github.com/fmtlib/fmt)
- POSIX-compatible system (for signal handling)

---

## Build Instructions

```bash
git clone <this_repo>
mkdir build && cd build
cmake ..
make
