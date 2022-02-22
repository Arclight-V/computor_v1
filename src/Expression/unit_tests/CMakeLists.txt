cmake_minimum_required(VERSION 3.20)
project(expression_unit_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress")
include_directories("../../../src/")
add_compile_definitions(UNIT_TESTS)
add_executable(expression_unit_tests    main.cpp
                                        ../IExpressionNode.h
                                        ../Node.h
                                        ../NumberNode.h
                                        ../OperatorNode.h
                                        ../UnknownNode.h)