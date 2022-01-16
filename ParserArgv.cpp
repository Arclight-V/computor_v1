//
// Created by Anatashi on 04.01.2022.
//

#include <iostream>
#include "ParserArgv.h"
#include "tools.h"

namespace {
    constexpr char kInvalidCharacter[] = "invalid character";
    constexpr char kManyEquals[] = "the expression must not contain more than one equal to";
    constexpr char kNotEquals[] = "the expression does not contain \"=\"";
}

ParserArgv::ParserArgv(const char* line) :  line_(line)
                                             {
    tokens_.reserve(line_.size());
    token_line_.reserve(line_.size());
    errorManager_ = std::make_unique<ErrorManager>(line_.size());


}

void ParserArgv::CheckError() {
    if (errorManager_) {
        errorManager_->PrintError(line_);
    }
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
             errorManager_->SetErrorIndex(ch - line_.c_str());
             errorManager_->AddErrorMessage(kInvalidCharacter);
        }
        if (!(*ch == Punctuator::gap)) {
            std::unique_ptr<Token> s_ptr_token = std::make_unique<Token>(*ch, ch - line_.c_str());
            tokens_.push_back(std::move(s_ptr_token));
        }
        if (*ch == Punctuator::equally) {
            if (!is_equally) {
                is_equally = true;
            } else {
                errorManager_->SetErrorIndex(ch - line_.c_str());
                errorManager_->AddErrorMessage(kManyEquals);
            }
        }
        ++ch;
    }

    CheckError();
    if (!is_equally) {
        errorManager_->SetErrorIndex(line_.size());
        errorManager_->AddErrorMessage(kNotEquals);
        throw EXIT_FAILURE;
    }
}


void ParserArgv::CheckTokens() {
    size_t i = 0;
    while (i < tokens_.size()) {

        switch (tokens_[i]->getToken()) {
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
                ++i;
                if (tokens_[i]->getToken() == KeyWord::X_ || tokens_[i]->getToken() == KeyWord::x_) {
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

