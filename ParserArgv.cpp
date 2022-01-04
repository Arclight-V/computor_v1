//
// Created by Anatashi on 04.01.2022.
//

#include <vector>
#include <iostream>
#include "ParserArgv.h"

#define RED "\x1b[41m"
#define NORMAL "\x1b[0m"

ParserArgv::ParserArgv(const char* line) : line_(line) {

}

void ParserArgv::printError(std::vector<bool> &error_index) {
    size_t i = 0;

    while(isspace(line_[i])) {
        ++i;
    }

    std::cout << "Error: ";
    for(; i < line_.size(); ++i) {
        if (error_index[i] == true) {
            std::cout << RED << line_[i] << NORMAL;
        } else {
            std::cout << line_[i];
        }
    }
    std::cout << '\n';

    throw EXIT_FAILURE;
}



void ParserArgv::parse() {
    std::vector<bool> error_index(line_.size());
    size_t i = 0;

    while(isspace(line_[i])) {
        ++i;
    }

    if (!isdigit(line_[i]) && line_[i] != 'X' && line_[i] != 'x') {
        error_index[i] = true;
    }

    printError(error_index);

}