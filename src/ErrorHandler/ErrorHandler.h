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
#include <vector>
#include <algorithm>
#include <iterator>

namespace {
    // Formatting
    constexpr const char* kRed = "\x1b[31m";
    constexpr const char* kNormal = "\x1b[0m";

    // Errors
    constexpr const char* kError = "Error #";
    constexpr const char* kInvalidCharacter = "Invalid character";
    constexpr const char* kSyntaxErrorFirstCharacter = "Expected \'number\' or \'X\' or \'x\'";
    constexpr const char* kSyntaxErrorLastCharacter = "Invalid character at the end of an equation";
    constexpr const char* kSyntaxErrorTwoEquals = "Two equals in equation";
    constexpr const char* kIncorrectEntry = "Incorrect entry";

    const size_t kLenRed = std::strlen(kRed);
    const size_t kLenNormal = std::strlen(kNormal);
    const size_t kLenError = std::strlen(kError);
    const size_t kLenInvalidCharacter = std::strlen(kInvalidCharacter);
    const size_t kLenSyntaxError1 = std::strlen(kSyntaxErrorFirstCharacter);
    const size_t kLenSyntaxErrorLastCharacter = std::strlen(kSyntaxErrorLastCharacter);
    const size_t kLenSyntaxErrorTwoEquals = std::strlen(kSyntaxErrorTwoEquals);
    const size_t kLenIncorrectEntry = std::strlen(kIncorrectEntry);

}

namespace errorhandler {
    enum err {
        INVALID_CHARACTER,
        INVALID_FIRST_CHARACTER,
        INVALID_LAST_CHARACTER,
        TWO_EQUALS,
        INCORRECT_ENTRY
    };

    size_t getLensError(errorhandler::err e);

    const char * getError(errorhandler::err e);

}

#if defined(UNIT_TESTS)
class ErrorHandler;

class TestErrorHandler {
public:
    TestErrorHandler() =default;
    TestErrorHandler(const TestErrorHandler&) = delete;
    TestErrorHandler& operator=(const TestErrorHandler&) = delete;
    ~TestErrorHandler() = default;

    const std::pair<std::string, errorhandler::err>& TestAdd(ErrorHandler& errorHandler_, errorhandler::err err, size_t pos);
    const std::pair<std::string, errorhandler::err>& TestAdd(ErrorHandler& errorHandler_, errorhandler::err err, size_t first, size_t last);
};
#endif

class ErrorHandler {
#if defined(UNIT_TESTS)
    friend class TestErrorHandler;
#endif
public:
    explicit ErrorHandler(const std::string &tokens);

    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
    ~ErrorHandler() = default;

    void add(errorhandler::err, size_t);
    void add(errorhandler::err, size_t, size_t);
    void PrintErrors();
    bool empty() {
        return errors.empty();
    };
private:
    std::list<std::pair<std::string, errorhandler::err>> errors;
    std::string tokens_;
};




#endif //COMPUTOR_V1_ERRORHANDLER_H
