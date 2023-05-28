//
// Created by Arclight-V on 01.05.2023.
//

#include <iterator>

#include "ErrorHandler.h"

namespace errorhandler {
    size_t getLensError(errorhandler::err e) {
        switch (e) {
            case errorhandler::err::INVALID_CHARACTER:
                return kLenInvalidCharacter + 1;
            case errorhandler::err::INVALID_FIRST_CHARACTER:
                return kLenSyntaxError1 + 1;
            case errorhandler::err::INVALID_LAST_CHARACTER:
                return kLenSyntaxErrorLastCharacter + 1;
            case errorhandler::err::TWO_EQUALS:
                return kLenSyntaxErrorTwoEquals + 1;
            case errorhandler::err::INCORRECT_ENTRY:
                return kLenIncorrectEntry;
            case errorhandler::err::OPERATION_NOT_SUPPORTED:
                return kLenOperationIsNotSupported;
            default:
                break;
        }
    }

    const char *getError(errorhandler::err e) {
        switch (e) {
            case errorhandler::err::INVALID_CHARACTER:
                return kInvalidCharacter;
            case errorhandler::err::INVALID_FIRST_CHARACTER:
                return kSyntaxErrorFirstCharacter;
            case errorhandler::err::INVALID_LAST_CHARACTER:
                return kSyntaxErrorLastCharacter;
            case errorhandler::err::TWO_EQUALS:
                return kSyntaxErrorTwoEquals;
            case errorhandler::err::INCORRECT_ENTRY:
                return kIncorrectEntry;
            case errorhandler::err::OPERATION_NOT_SUPPORTED:
                return kOperationIsNotSupported;
            default:
                break;
        }
    }

}

ErrorHandler::ErrorHandler(const std::string& tokens) : tokens_(tokens) {}

void ErrorHandler::add(errorhandler::err err, size_t pos) {
    std::string to_add(tokens_.size() + kLenRed + kLenNormal, '\0');
    std::copy(tokens_.begin(), std::next(tokens_.begin(), pos) , to_add.begin());
    std::copy_n(kRed, kLenRed, std::next(to_add.begin(), pos));
    std::copy_n(std::next(tokens_.begin(), pos), 1, std::next(to_add.begin(), pos + kLenRed));
    std::copy_n(kNormal, kLenNormal, std::next(to_add.begin(), pos + kLenRed + 1));
    std::copy(std::next(tokens_.begin(), pos + 1), tokens_.end(), std::next(to_add.begin(), pos + kLenRed + kLenNormal + 1));
    errors.push_back({to_add, err});
}

void ErrorHandler::add(errorhandler::err err, size_t first, size_t last) {
//    if (last - first == 1 ) {
//        ++last;
//    }
    std::string to_add(tokens_.size() + kLenRed + kLenNormal, '\0');
    std::copy(tokens_.begin(), std::next(tokens_.begin(), first) , to_add.begin());
    std::copy_n(kRed, kLenRed, std::next(to_add.begin(), first));
    std::copy(std::next(tokens_.begin(), first) , std::next(tokens_.begin(), last + 1) , std::next(to_add.begin(), first + kLenRed));
    std::copy_n(kNormal, kLenNormal, std::next(to_add.begin(), last + kLenRed + 1));
    std::copy(std::next(tokens_.begin(), last + 1), tokens_.end(), std::next(to_add.begin(), last + kLenRed + kLenNormal + 1));

    errors.push_back({to_add, err});
}


void ErrorHandler::PrintErrors() {
    size_t count = 0;
    for (auto &err: errors) {
        std::cout << kRed << kError << ++count << '\n' << kNormal;
        std::cout << err.first << '\n';
        std::cout << errorhandler::getError(err.second) << "\n";
    }
}

#if defined(UNIT_TESTS)
const std::pair<std::string, errorhandler::err> &TestErrorHandler::TestAdd(ErrorHandler &errorHandler_, errorhandler::err err, size_t pos) {
    errorHandler_.add(err, pos);
    return errorHandler_.errors.back();
}

const std::pair<std::string, errorhandler::err> &TestErrorHandler::TestAdd(ErrorHandler &errorHandler_, errorhandler::err err, size_t first, size_t last) {
    errorHandler_.add(err, first, last);
    return errorHandler_.errors.back();
}

#endif
