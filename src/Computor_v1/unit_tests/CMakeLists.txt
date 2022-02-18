cmake_minimum_required(VERSION 3.20)
project(computor_v1_unit_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress")
include_directories("../../../src/")
add_compile_definitions(UNIT_TESTS)
add_executable(computor_v1_unit_tests   main.cpp
                                        ../Computor_v1.cpp
                                        ../Computor_v1.h
                                        ../../ErrorManager/ErrorManager.cpp
                                        ../../ErrorManager/ErrorManager.h
                                        ../../ErrorManager/IErrorManager.h)
