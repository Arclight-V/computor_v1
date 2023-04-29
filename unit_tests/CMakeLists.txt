cmake_minimum_required(VERSION 3.24)
project(computor_v1_unit_tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Wunused")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(SOURCE_FILES TestComputor_v1WithFixture.cpp ../src/Computor/Computor_v1.h ../src/Computor/Computor_v1.cpp ../src/Computor/Computor.h)
add_executable( ${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(
        ${PROJECT_NAME}
        GTest::gtest
        GTest::gtest_main
)
include(GoogleTest)
