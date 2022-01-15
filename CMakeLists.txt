cmake_minimum_required(VERSION 3.20)
project(computor_v1)

set(CMAKE_CXX_STANDARD 17)

add_executable(computor_v1 main.cpp ParserArgv.cpp ParserArgv.h tools.cpp tools.h ErrorManager/ErrorManager.cpp ErrorManager/ErrorManager.h ErrorManager/IErrorManager.h)
