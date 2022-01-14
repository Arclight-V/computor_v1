//
// Created by Anatashi on 04.01.2022.
//

#include <iostream>
#include "ParserArgv.h"
#include "tools.h"

#define RED "\x1b[41m"
#define NORMAL "\x1b[0m"

ParserArgv::ParserArgv(const char* line) :  line_(line),
                                            error_index_(line_.size()) {
    tokens_.reserve(line_.size());
    token_line_.reserve(line_.size());
}

void ParserArgv::CheckError() {
    for (size_t i = 0; i < error_index_.size(); ++i) {
        if (error_index_[i] == true) {
            PrintError();
            break;
        }
    }
}

void ParserArgv::PrintError() {
    size_t i = 0;

    while(isspace(line_[i])) {
        ++i;
    }

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

void ParserArgv::analyzeTerm(std::string& line, size_t first, size_t last) {

//    double num = 0;
//    double pow = 0;
//    arithmetic_sign sign = arithmetic_sign::none;
//    char* end;
//
//    for(; first <= last; ++first) {
//        switch (line[first]) {
//            case ' ':
//                break;
//            case arithmetic_sign::degree:
//                try {
//                    ++first;
//                    pow = std::strtod(line.c_str() + first, &end);
//                    std::string pow_str(std::to_string(pow));
//                    first += pow_str.size() - 1;
//                } catch (std::out_of_range) {
//                    std::cout << "ERROR\n";
//                    exit(1);
//                }
//                break;
//            case arithmetic_sign::plus:
//                sign = arithmetic_sign::plus;
//                break;
//            case arithmetic_sign::minus:
//                sign = arithmetic_sign::minus;
//                break;
//            case 'X':
//            case 'x':
//                break;
//            default:
//                try {
//                    num = std::strtod(line.c_str() +first, &end);
//                    std::string num_str(std::to_string(num));
//                    first += num_str.size() - 1;
//                } catch (std::out_of_range) {
//                    std::cout << "Error\n";
//                    exit(1);
//                }
//                break;
//        }
//    }

//    std::unique_ptr<block> s_ptr_block = std::make_unique<block>(num, pow, sign);

//    coef_.push_back(std::move(s_ptr_block));
}

bool ParserArgv::IsPunctuator(char ch) {
    if (ch == Punctuator::gap || ch == Punctuator::pow || ch == Punctuator::minus ||
        ch == Punctuator::plus || ch == Punctuator::multiply || ch == Punctuator::dot ||
        ch == Punctuator::equally) {
        return true;
    }
    return false;
}

bool ParserArgv::IsKeyWord(char ch) {
    if (ch == KeyWord::X_ || ch == KeyWord::x_) {
        return true;
    }
    return false;
}

void ParserArgv::CreateTokens() {
    const char* ch = line_.c_str();
    bool is_equally = false;

    while (*ch != '\0') {
        if (!IsPunctuator(*ch) &&
            !std::isdigit(*ch) &&
            !IsKeyWord(*ch)) {
            error_index_[ch - line_.c_str()] = true;
        }
        if (!(*ch == Punctuator::gap)) {
            std::unique_ptr<Token> s_ptr_token = std::make_unique<Token>(*ch, ch - line_.c_str());
            tokens_.push_back(std::move(s_ptr_token));
        }
        if (*ch == Punctuator::equally) {
            if (!is_equally) {
                is_equally = true;
            } else {
                error_index_[ch - line_.c_str()] = true;
            }
        }
        ++ch;
    }

    CheckError();
    if (!is_equally) {
        std::cout << "Error: the expression does not contain \"=\"";
        throw EXIT_FAILURE;
    }
}


void ParserArgv::CheckTokens() {
    const char* ch = token_line_.c_str();

    while (*ch != '\0') {
        switch (*ch) {
            case Punctuator::plus:
                break;
            case Punctuator::minus:
                break;
            case Punctuator::multiply:
                break;
            case Punctuator::pow:
                break;
            case Punctuator::dot:
                break;
            case Punctuator::equally:
                break;
            default:
                ++ch;
                if (*ch == KeyWord::X_ || *ch == KeyWord::x_) {
                    std::cout << "Error: There should be a multiplication sign between the number and the claim";
                }
                break;
        }
    }
}

void ParserArgv::LexicalAnalyzer() {
    CreateTokens();
}

void ParserArgv::parse() {
    LexicalAnalyzer();
}

