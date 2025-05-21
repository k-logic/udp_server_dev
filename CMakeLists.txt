cmake_minimum_required(VERSION 3.16)
project(udp_receive_server CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ヘッダーファイルのパス
include_directories(
    ${CMAKE_SOURCE_DIR}/asio/asio/include
    ${CMAKE_SOURCE_DIR}/fmt/include
)

# 実行ファイル
add_executable(udp_receive_server main.cpp)

# プリプロセッサマクロを定義（コンパイル時に -D... を渡す）
target_compile_definitions(udp_receive_server PRIVATE
    ASIO_STANDALONE
    FMT_HEADER_ONLY
)

# pthread をリンク
target_link_libraries(udp_receive_server pthread)