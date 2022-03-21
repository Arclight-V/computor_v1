//
// Created by Anatashi on 04.01.2022.
//

#include <iostream>
#include "Computor_v1/Computor_v1.h"
#include "tools/tools.h"
#include <stack>

namespace {
    constexpr char kInvalidCharacter[] = "invalid character";
    constexpr char kManyEquals[] = "the expression must not contain more than one equal to";
    constexpr char kInvalidEntry[] = "invalid entry";
    constexpr char kEmptyLine[] = "empty line";
    constexpr char kNotMathOperations[] = "does not contain mathematical operators";
//    constexpr char kOutOfRange[] = "the converted value would fall out of the range of the result type";
}

Computor_v1::Computor_v1(const char* line) :  line_(line)
                                             {
    reverse_polish_notation_.reserve(line_.size());
    tokenVector_.reserve(line_.size());
    errorManager_ = std::make_unique<ErrorManager>(line_.size() == 0 ? 1 : line_.size());
}

void Computor_v1::CheckError() {
    if (errorManager_->isError()) {
#if defined(UNIT_TESTS)
        throw line_;
#endif
        errorManager_->PrintErrors(line_);
    }
}

bool Computor_v1::IsPunctuator(char ch) {
    return  ch == gap || ch == pow || ch == minus ||
            ch == plus || ch == multiply || ch == dot ||
            ch == equally || ch == left_bracket || ch == right_bracket;
}

bool Computor_v1::IsOperator(char ch) {
    return ch == plus || ch == minus || ch == multiply || ch == pow;
}

bool Computor_v1::IsKeyWord(char ch) {
    return ch == X_ || ch == x_;
}

bool Computor_v1::LexicalAnalyzer() {
    const char* ch = line_.c_str();
    for (; *ch; ++ch) {
        if (!IsPunctuator(*ch) &&
            !std::isdigit(*ch) &&
            !IsKeyWord(*ch)) {
            errorManager_->SetErrorIndex(ch - line_.c_str());
            errorManager_->AddErrorMessage(kInvalidCharacter);
        }
        if (*ch != Punctuator::gap) {
            tokenVector_.push_back(*ch);
        }
    }

    if (errorManager_->isError()) {
#if defined(UNIT_TESTS)
        throw line_;
#endif
        return false;
    }
    return true;
}

bool Computor_v1::SyntaxAnalyzer(size_t& equal_position) {
    bool is_equally = false;
    bool is_math_operations = false;
    for (size_t i = 0; i < tokenVector_.size(); ++i) {
        const size_t next = i + 1;
        const char token = tokenVector_[i];
        switch (token) {
            // FIXME
            // delete case Punctuator::gap if not checked
            case Punctuator::gap:
                break;
            case Punctuator::plus:
            case Punctuator::minus:
            case Punctuator::multiply:
            case Punctuator::pow:
            case Punctuator::dot: {
                if (next == tokenVector_.size() ||
                    (i == 0 && token != Punctuator::plus && token != Punctuator::minus) ||
                    (next < tokenVector_.size() && (!std::isdigit(tokenVector_[next]) && tokenVector_[next] != KeyWord::X_ && tokenVector_[next] != KeyWord::x_)) ||
                    (token == Punctuator::dot && !std::isdigit(tokenVector_[next]))) {
                    errorManager_->SetErrorIndex(i);
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                if (!is_math_operations) {
                    is_math_operations = true;
                }
                break;
            }
            case KeyWord::X_:
            case KeyWord::x_:
                if (next < tokenVector_.size() &&
                    (tokenVector_[next] == Punctuator::dot ||
                     std::isdigit(tokenVector_[next])) ) {
                    errorManager_->SetErrorIndex(tokenVector_[next]);
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                break;
            case Punctuator::equally:
                if (!is_equally) {
                    is_equally = true;
                    equal_position = i;
                } else {
                    errorManager_->SetErrorIndex(i);
                    errorManager_->AddErrorMessage(kManyEquals);
                }
                break;
            default:
                if (next < tokenVector_.size() &&
                    (tokenVector_[next] == KeyWord::X_ ||
                    tokenVector_[next] == KeyWord::x_)) {
                    errorManager_->SetErrorIndex(i);
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                break;
        }
    }

    if (!is_math_operations) {
        errorManager_->SetErrorIndex(0);
        errorManager_->AddErrorMessage(kNotMathOperations);
    }

    if (errorManager_->isError()) {
#if defined(UNIT_TESTS)
        throw line_;
#endif
        return false;
    }
    return true;
}

void Computor_v1::ChangeMinusToPlus(size_t begin, size_t end) {
    for (; begin < end; ++begin) {
        if (tokenVector_[begin] == Punctuator::minus) {
            tokenVector_[begin] = Punctuator::plus;
        } else if (tokenVector_[begin] == Punctuator::plus) {
            tokenVector_[begin] = Punctuator::minus;
        }
    }
}

bool Computor_v1::IsNoMinusAndPlus(char ch) {
    return ch != Punctuator::minus && ch != Punctuator::plus;
}

void Computor_v1::MoveTokenToLeftFromEqually(size_t equal_position) {
    if (tokenVector_[tokenVector_.size() - 2] == Punctuator::equally &&
        tokenVector_[tokenVector_.size() - 1] == '0') {
#if defined(UNIT_TESTS)
        std::string throw_str;
        throw_str.reserve(line_.size());
        for(size_t i = 0; i < tokenVector_.size(); ++i) {
            throw_str += tokenVector_[i];
        }
        throw throw_str;
#endif
        return;
    } else if (tokenVector_[1] == Punctuator::equally &&
               tokenVector_[0] == '0') {
        tokenVector_.erase(tokenVector_.begin(), tokenVector_.begin() + 2);
    } else {
        if (equal_position > tokenVector_.size() / 2) {
            if (IsNoMinusAndPlus(tokenVector_[equal_position + 1])) {
                tokenVector_[equal_position] = Punctuator::minus;
            } else {
                tokenVector_.erase(tokenVector_.begin() + equal_position);
                --equal_position;
            }
            ChangeMinusToPlus(equal_position + 1, tokenVector_.size() - 1);
        } else {
            if (IsNoMinusAndPlus(tokenVector_[0])) {
                tokenVector_.insert(tokenVector_.begin(), Punctuator::minus);
                ++equal_position;
            }
            ChangeMinusToPlus(2, equal_position - 1);
            tokenVector_[equal_position] = Punctuator::plus;
        }
    }
    tokenVector_.push_back('=');
    tokenVector_.push_back('0');
#if defined(UNIT_TESTS)
    std::string throw_str;
    throw_str.reserve(line_.size());
    for(size_t i = 0; i < tokenVector_.size(); ++i) {
        throw_str += tokenVector_[i];
    }
    throw throw_str;
#endif

}
// TODO: add implementation
bool Computor_v1::ComparePrecedence() {

}

void Computor_v1::ConvertInfixNotationToRPN() {
    token_vector RPNVector;
    RPNVector.reserve(tokenVector_.size());
    std::stack<char> operatorStack;

    for (size_t i = 0; i < tokenVector_.size(); ++i) {
        if (IsOperator(tokenVector_[i])) {
            // TODO: add checking to compare precedence
            while (!operatorStack.empty()) {

            }
        } else if (std::isdigit(tokenVector_[i])) {

        } else if (tokenVector_[i] == left_bracket) {

        } else if (tokenVector_[i] == right_bracket) {

        } else {
            RPNVector.push_back(tokenVector_[i]);
        }
    }
}


void Computor_v1::PrintError() {
    // FIXME
    CheckError();
}

void Computor_v1::PrintSolution() {

}

bool Computor_v1::parse() {
    if (line_.size() == 0) {
#if defined(UNIT_TESTS)
        throw line_;
#endif
        errorManager_->SetErrorIndex(0);
        errorManager_->AddErrorMessage(kEmptyLine);
        return false;
    }
    size_t equal_position = 0;
    if (!LexicalAnalyzer() || !SyntaxAnalyzer(equal_position)) {
        return false;
    }

    if (equal_position != 0) {
        MoveTokenToLeftFromEqually(equal_position);
    } else {
        // Computor_v2
        return false;
    }
    ConvertInfixNotationToRPN();
//    line_.clear();

    return true;
}

Computor_v1::OperatorCv1::OperatorCv1(Operators op) : op_(op) {
    switch (op_) {
        case ADDITION:
        case SUBTRACTION:
            associativity_ = Associativity::LEFT;
            precedence_ = 0;
            break;
        case MULTIPLICATION:
            associativity_ = Associativity::LEFT;
            precedence_ = 5;
            break;
        case POWER:
            associativity_ = Associativity::RIGHT;
            precedence_ = 10;
        default:
            break;
    }
}
