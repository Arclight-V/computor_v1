cmake_minimum_required(VERSION 3.20)
project(GoogleTestDemo)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp TestComputor_v1WithFixture.cpp)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries( ${PROJECT_NAME} gtest gtest_main)
