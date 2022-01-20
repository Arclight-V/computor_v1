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
    constexpr char kInvalidEntry[] = "invalid entry";
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
        size_t next = i + 1;
        char token = tokens_[i]->getToken();

        switch (token) {
            case Punctuator::plus:
            case Punctuator::minus:
            case Punctuator::multiply:
            case Punctuator::equally:
            case Punctuator::pow:
            case Punctuator::dot: {
                if (next == tokens_.size() ||
                    (i == 0 && token != Punctuator::plus && token != Punctuator::minus) ||
                    (next < tokens_.size() && (!std::isdigit(tokens_[next]->getToken()) && tokens_[next]->getToken() != KeyWord::X_ && tokens_[next]->getToken() != KeyWord::x_)) ||
                    (token == Punctuator::dot && !std::isdigit(tokens_[next]->getToken()))) {
                    errorManager_->SetErrorIndex(tokens_[i]->getPosition());
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                break;
            }
            case KeyWord::X_:
            case KeyWord::x_:
                if (next < tokens_.size() && tokens_[next]->getToken() == Punctuator::dot) {
                    errorManager_->SetErrorIndex(tokens_[i]->getPosition());
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                break;
            default:
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

