cmake_minimum_required(VERSION 3.20)
project(computor_v1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Wunused")
add_executable(${PROJECT_NAME} main.cpp Computor_v1/Computor_v1.cpp Computor_v1/Computor_v1.h tools/tools.cpp tools/tools.h ErrorManager/ErrorManager.cpp ErrorManager/ErrorManager.h ErrorManager/IErrorManager.h Expression/IExpressionNode.h Expression/OperatorNode.h Expression/UnknownNode.h Expression/Node.h Expression/NumberNode.h Expression/PolynomialExpressionTree.h Expression/ExpressionTree.h)
