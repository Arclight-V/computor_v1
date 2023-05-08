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
    // Formatting
    constexpr const char* kRed = "\x1b[31m";
    constexpr const char* kNormal = "\x1b[0m";

    // Errors
    constexpr const char* kError = "Error #";
    constexpr const char* kInvalidCharacter = "Invalid character";
    constexpr const char* kSyntaxErrorFirstCharacter = "Expected \'number\' or \'X\' or \'x\'";
    constexpr const char* kSyntaxErrorLastCharacter = "Invalid character at the end of an equation";

    const size_t kLenRed = std::strlen(kRed);
    const size_t kLenNormal = std::strlen(kNormal);
    const size_t kLenError = std::strlen(kError);
    const size_t kLenInvalidCharacter = std::strlen(kInvalidCharacter);
    const size_t kLenSyntaxError1 = std::strlen(kSyntaxErrorFirstCharacter);
    const size_t kLenSyntaxErrorLastCharacter = std::strlen(kSyntaxErrorLastCharacter);

}

namespace errorhandler {
    enum err {
        INVALID_CHARACTER,
        INVALID_FIRST_CHARACTER,
        INVALID_LAST_CHARACTER
    };
}

#if defined(UNIT_TESTS)
class ErrorHandler;

class TestErrorHandler {
public:
    TestErrorHandler() =default;
    TestErrorHandler(const TestErrorHandler&) = delete;
    TestErrorHandler& operator=(const TestErrorHandler&) = delete;
    ~TestErrorHandler() = default;

    const std::string& TestAdd(ErrorHandler& errorHandler_, errorhandler::err err, size_t pos);
};
#endif

class ErrorHandler {
#if defined(UNIT_TESTS)
    friend class TestErrorHandler;
#endif
public:
    explicit ErrorHandler(const std::string &str);

    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
    ~ErrorHandler() = default;

    void add(errorhandler::err, size_t);
    void PrintErrors();
    bool empty() {
        return errors.empty();
    };
private:
    std::list<std::string> errors;
    std::string str;
};




#endif //COMPUTOR_V1_ERRORHANDLER_H
