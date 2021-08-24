cmake_minimum_required(VERSION 2.7)


project(p2 C)

set(CMAKE_C_STANDARD 11)


set(CMAKE_C_FLAGS "-Wall -Werror")


add_executable(p2 main.c)

target_link_libraries(p2 m)