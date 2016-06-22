cmake_minimum_required(VERSION 2.6)
project(bot)

add_executable(bot src/main.cpp)

install(TARGETS bot RUNTIME DESTINATION bin)

add_subdirectory(src)