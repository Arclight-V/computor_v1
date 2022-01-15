//
// Created by Anatashi on 14.01.2022.
//

#include "ErrorManager.h"

namespace {
    constexpr char kError[] = "error: ";
    constexpr char kUnderline = '~';
    constexpr char kWhitespace = ' ';
}


ErrorManager::ErrorManager() {}



void ErrorManager::PrintError(std::string& line) {
    std::string whitespaces;
    error_list::iterator begin = errors_.begin();
    whitespaces.reserve(indexes_.size());

    for (size_t i = 0; i < indexes_.size(); ++i) {
        if (indexes_[i] == true) {
            whitespaces.push_back(kUnderline);
            std::cout << RED <<  kError << NORMAL
                      << *begin << '\n' << GREEN
                      << whitespaces << NORMAL << '\n';
        }
        whitespaces.push_back(kWhitespace);
    }

    for (auto& elem: errors_) {
        std::cout << line << "\n";
        for (size_t i = 0; i < )
        std::cout << elem << "\n";
    }



}

void ErrorManager::SetErrorIndex(size_t position) {
    indexes_[position] = true;
}