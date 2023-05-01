cmake_minimum_required(VERSION 3.24)
project(computor_v1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Wunused")
include_directories(src)
add_executable(computor_v1 main.cpp
        src/Computor/Computor.h
        src/Computor/Computor_v1.cpp src/Computor/Computor_v1.h
        src/ErrorHandler/ErrorHandler.cpp src/ErrorHandler/ErrorHandler.h)
