cmake_minimum_required(VERSION 3.24)
project(EaglePay0)

set(CMAKE_CXX_STANDARD 17)

find_package(PostgreSQL REQUIRED)
add_executable(EaglePay0 main.cpp)
target_link_libraries(EaglePay0 PUBLIC pq)