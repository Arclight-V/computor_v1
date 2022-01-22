//
// Created by Anatashi on 04.01.2022.
//

#include <iostream>
#include "Computor_v1/Computor_v1.h"
#include "tools/tools.h"

namespace {
    constexpr char kInvalidCharacter[] = "invalid character";
    constexpr char kManyEquals[] = "the expression must not contain more than one equal to";
    constexpr char kNotEquals[] = "the expression does not contain \"=\"";
    constexpr char kInvalidEntry[] = "invalid entry";
    constexpr char kEmptyLine[] = "empty line";
}

Computor_v1::Computor_v1(const char* line) :  line_(line)
                                             {
    tokens_.reserve(line_.size());
    errorManager_ = std::make_unique<ErrorManager>(line_.size());


}

void Computor_v1::CheckError() {
    if (errorManager_->isError()) {
#if defined(UNIT_TESTS)
        throw line_;
#endif
        errorManager_->PrintErrors(line_);
        throw EXIT_FAILURE;
    }
}

bool Computor_v1::IsPunctuator(char ch) {
    if (ch == Punctuator::gap || ch == Punctuator::pow || ch == Punctuator::minus ||
        ch == Punctuator::plus || ch == Punctuator::multiply || ch == Punctuator::dot ||
        ch == Punctuator::equally) {
        return true;
    }
    return false;
}

bool Computor_v1::IsKeyWord(char ch) {
    if (ch == KeyWord::X_ || ch == KeyWord::x_) {
        return true;
    }
    return false;
}

void Computor_v1::LexicalAnalyzer() {
    const char* ch = line_.c_str();
    if (*ch == '\0') {

#if defined(UNIT_TESTS)
        throw line_;
#endif
        errorManager_->PrintError(kEmptyLine);
        throw EXIT_FAILURE;
    }
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

#if defined(UNIT_TESTS)
        throw line_;
#endif
        errorManager_->SetErrorIndex(line_.size() - 1);
        errorManager_->AddErrorMessage(kNotEquals);
        errorManager_->PrintErrors(line_);
        throw EXIT_FAILURE;
    }
}

void Computor_v1::SyntaxAnalyzer() {
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

void Computor_v1::CreateElements() {
    std::string buf;
    buf.reserve(tokens_.size());
    double num = 0;
    int pow = 0;

    for (size_t i = 0; i < tokens_.size(); ++i) {
        char token = tokens_[i]->getToken();

        switch (token) {
            case Punctuator::plus:
            case Punctuator::minus:
                break;
            case Punctuator::multiply: {
                char next_token = tokens_[i + 1]->getToken();
                if (std::isdigit(next_token)) {

                } else {

                }
                break;
            }
            case Punctuator::equally:
            case Punctuator::pow:
            case Punctuator::dot:
                break;
            case KeyWord::X_:
            case KeyWord::x_:
                break;
            default:
                buf.push_back(token);
                break;
        }
    }
}


void Computor_v1::parse() {
    LexicalAnalyzer();
    SyntaxAnalyzer();
    CreateElements();
}

