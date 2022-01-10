//
// Created by Anatashi on 04.01.2022.
//

#include <iostream>
#include "ParserArgv.h"
#include "tools.h"

#define RED "\x1b[41m"
#define NORMAL "\x1b[0m"

ParserArgv::ParserArgv(const char* line) : line_(line) {}

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

    std::vector<std::string> vector(tools::ft_split(line_, "="));


    const char* ch = line_.c_str();

    while(isspace(*ch)) {
        ++ch;
    }

    if (!isdigit(*ch) && *ch != 'X' && *ch != 'x') {
        error_index[ch - line_.c_str()] = true;
    }

    std::unique_ptr<block> s_ptr_block = std::make_unique<block>();

    while (*ch) {
        switch (*ch) {
            case arithmetic_sign::multiply:
                break;
            case arithmetic_sign::degree:
                break;
            case arithmetic_sign::plus:
                break;
            case arithmetic_sign::minus:
                break;
            case arithmetic_sign::divide:
                break;
            case arithmetic_sign::equally:
                break;
            default:
                if (isdigit(*ch)) {

                } else {
                    error_index[ch - line_.c_str()] = true;
                }
                break;
        }

        ++ch;
    }


    printError(error_index);
}