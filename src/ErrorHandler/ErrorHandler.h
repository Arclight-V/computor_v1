//
// Created by Arclight-V on 01.05.2023.
//

#ifndef COMPUTOR_V1_ERRORHANDLER_H
#define COMPUTOR_V1_ERRORHANDLER_H

#include <list>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace {
    constexpr const char* kRed = "\x1b[31m";
    constexpr const char* kNormal = "\x1b[0m";
    constexpr const char* kError = "Error #";
}

#if defined(UNIT_TESTS)
class ErrorHandler;

class TestErrorHandler {
public:
    TestErrorHandler() =default;
    TestErrorHandler(const TestErrorHandler&) = delete;
    TestErrorHandler& operator=(const TestErrorHandler&) = delete;
    ~TestErrorHandler() = default;

    const std::string& TestAdd(ErrorHandler& errorHandler, const std::string& str, size_t pos);
};
#endif

class ErrorHandler {
#if defined(UNIT_TESTS)
    friend class TestErrorHandler;
#endif
public:
    ErrorHandler() = default;
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
    ~ErrorHandler() = default;

    void add(const std::string&, size_t);
    void PrintErrors();
    bool empty() {
        return errors.empty();
    };
private:
    std::list<std::string> errors;
    std::stringstream ss;
};




#endif //COMPUTOR_V1_ERRORHANDLER_H
