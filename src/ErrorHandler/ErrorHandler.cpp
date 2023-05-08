//
// Created by Arclight-V on 01.05.2023.
//

#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(const std::string &str) : str(str) {}

void ErrorHandler::add(errorhandler::err err, size_t pos) {
    std::string to_add;
    auto len = [=](errorhandler::err e){
        switch (e) {
            case errorhandler::err::INVALID_CHARACTER:
                return kLenInvalidCharacter + 1;
            case errorhandler::err::INVALID_FIRST_CHARACTER:
                return kLenSyntaxError1 + 1;
            default:
                break;
        }
    }(err);
    to_add.reserve(str.size() + len + kLenRed + kLenNormal);
    auto* err_str = [](errorhandler::err e) {
        switch (e) {
            case errorhandler::err::INVALID_CHARACTER:
                return kInvalidCharacter;
            case errorhandler::err::INVALID_FIRST_CHARACTER:
                return kSyntaxError1;
            default:
                break;
        }
    }(err);
    to_add = str + '\n' + err_str;
    to_add.insert(pos, kRed);
    to_add.insert(pos + kLenRed + 1, kNormal);
    errors.push_back(to_add);
}



void ErrorHandler::PrintErrors() {
    size_t count = 0;
    for (auto& err: errors) {
        std::cout << kRed << kError << ++count << '\n' << kNormal;
        std::cout << err << '\n';
    }
}

#if defined(UNIT_TESTS)
const std::string &TestErrorHandler::TestAdd(ErrorHandler &errorHandler_, errorhandler::err err, size_t pos) {
    errorHandler_.add(err, pos);
    return errorHandler_.errors.back();
}

#endif
