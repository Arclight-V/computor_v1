cmake_minimum_required(VERSION 3.20)
project(computor_v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress")
include_directories("src")
add_executable(computor_v1 src/main.cpp src/Computor_v1/Computor_v1.cpp src/Computor_v1/Computor_v1.h src/tools/tools.cpp src/tools/tools.h src/ErrorManager/ErrorManager.cpp src/ErrorManager/ErrorManager.h src/ErrorManager/IErrorManager.h src/Expression/IExpressionNode.h src/Expression/OperatorNode.h src/Expression/UnknownNode.h src/Expression/Node.h src/Expression/UnknownNumberNode.h)
