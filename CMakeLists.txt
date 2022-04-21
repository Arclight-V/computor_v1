cmake_minimum_required(VERSION 3.20)
project(computor_v1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Wunused")

include_directories(src)

add_subdirectory(src)
add_subdirectory(unit_tests)
add_subdirectory(lib/googletest)
link_directories(lib/googletest/googletest/include)

