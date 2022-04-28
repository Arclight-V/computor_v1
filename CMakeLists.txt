cmake_minimum_required(VERSION 3.20)
project(computor_v1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Wunused")

include_directories(src)

add_subdirectory(src)
enable_testing()
option(tests "Build unit tests." ON)
if (tests)
    add_compile_definitions(UNIT_TESTS)
    add_subdirectory(unit_tests)
endif()
