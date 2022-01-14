//
// Created by Sergey Sudnichnikov on 14.01.2022.
//

#include "ErrorManager.h"

namespace {
    constexpr char kError[] = "Error:";
    constexpr char kE
}


ErrorManager::ErrorManager() {}


void ErrorManager::PrintError(std::string& line) {

    std::cout << "Error: ";
    for(; i < line_.size(); ++i) {
        if (error_index_[i] == true) {
            std::cout << RED << line_[i] << NORMAL;
        } else {
            std::cout << line_[i];
        }
    }
    std::cout << '\n';

    throw EXIT_FAILURE;
}