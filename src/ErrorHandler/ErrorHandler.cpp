//
// Created by Arclight-V on 01.05.2023.
//

#include "ErrorHandler.h"

void ErrorHandler::add(const std::string& err, size_t pos) {
    std::string to_add;
    to_add.reserve(err.size() + std::strlen(kRed) + std::strlen(kNormal));
    to_add = err;
    to_add.insert(pos, kRed);
    to_add.insert(pos + strlen(kRed) + 1, kNormal);
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
const std::string &TestErrorHandler::TestAdd(ErrorHandler &errorHandler, const std::string &str, size_t pos) {
    errorHandler.add(str, pos);
    return errorHandler.errors.back();
}

#endif
