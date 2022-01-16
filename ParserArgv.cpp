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
//    constexpr char kNotClaim[] = "there should be a multiplication sign between the number and the claim";
    constexpr char kNotPow[] = "there should be a multiplication sign between the number and the claim";

}

ParserArgv::ParserArgv(const char* line) :  line_(line)
                                             {
    tokens_.reserve(line_.size());
    errorManager_ = std::make_unique<ErrorManager>(line_.size());


}

void ParserArgv::CheckError() {
    if (errorManager_->isError()) {
        errorManager_->PrintErrors(line_);
        throw EXIT_FAILURE;
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

void ParserArgv::LexicalAnalyzer() {
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
        errorManager_->SetErrorIndex(line_.size() - 1);
        errorManager_->AddErrorMessage(kNotEquals);
        errorManager_->PrintErrors(line_);
        throw EXIT_FAILURE;
    }
}

void ParserArgv::SyntaxAnalyzer() {
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
            case KeyWord::X_:
            case KeyWord::x_:
                if (i + 1 < tokens_.size()) {
                    ++i;
                    char token = tokens_[i]->getToken();
                    if (token != Punctuator::pow && token != Punctuator::minus && token != Punctuator::plus &&
                        token != Punctuator::equally) {
                        errorManager_->SetErrorIndex(tokens_[i]->getPosition() - 1);
                        errorManager_->AddErrorMessage(kNotPow);
                    }
                    --i;
                }

                break;

            default:
                if (i + i < tokens_.size()) {
                    ++i;
//                    char token = tokens_[i]->getToken();
//                    if (token == KeyWord::X_ || token == KeyWord::x_) {
//                        errorManager_->SetErrorIndex(tokens_[i]->getPosition() - 1);
//                        errorManager_->SetErrorIndex(tokens_[i]->getPosition());
//                        errorManager_->AddErrorMessage(kNotClaim);
//                    }
                }
                break;
        }
        ++i;
    }

    CheckError();
}


void ParserArgv::parse() {
    LexicalAnalyzer();
    SyntaxAnalyzer();
}

