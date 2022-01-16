//
// Created by Anatashi on 14.01.2022.
//

#include <iomanip>

#include "ErrorManager.h"


namespace {
    constexpr char kError[] = "error: ";
    constexpr int kErrorLenght = 7;
    constexpr char kUnderline = '~';
    constexpr char kLid = '^';
    constexpr char kWhitespace = ' ';
}

ErrorManager::ErrorManager(size_t size) : indexes_(size) {}

void ErrorManager::PrintError(const std::string& line) {
    std::string whitespaces;
    error_list::iterator begin = errors_.begin();
    whitespaces.reserve(indexes_.size());

    for (size_t i = 0; i < indexes_.size(); ++i) {
        if (indexes_[i] == true) {
            whitespaces[kUnderline];
            std::cout <<  RED <<  kError << NORMAL << *begin++ << '\n'
                      << std::setfill(kWhitespace) << std::setw(kErrorLenght) << kWhitespace << line << '\n'
                      << std::setfill(kWhitespace) << std::setw(i + kErrorLenght) << kWhitespace << GREEN << kLid << NORMAL << '\n';
        }
        whitespaces.push_back(kWhitespace);
    }
}

void ErrorManager::SetErrorIndex(size_t position) {
    indexes_[position] = true;
}

void ErrorManager::AddErrorMessage(const std::string &message) {
    errors_.push_back(message);
}