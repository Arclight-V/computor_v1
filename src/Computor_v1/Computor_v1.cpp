//
// Created by Anatashi on 04.01.2022.
//

#include <iostream>
#include "Computor_v1/Computor_v1.h"
#include "tools/tools.h"

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
    tokenVector2_.reserve(line_.size());
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
    if (ch == Punctuator::gap || ch == Punctuator::pow || ch == Punctuator::minus ||
        ch == Punctuator::plus || ch == Punctuator::multiply || ch == Punctuator::dot ||
        ch == Punctuator::equally || ch == Punctuator::left_bracket || ch == Punctuator::right_bracket) {
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
            tokenVector2_.push_back(*ch);
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
    for (size_t i = 0; i < tokenVector2_.size(); ++i) {
        const size_t next = i + 1;
        const char token = tokenVector2_[i];
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
                if (next == tokenVector2_.size() ||
                    (i == 0 && token != Punctuator::plus && token != Punctuator::minus) ||
                    (next < tokenVector2_.size() && (!std::isdigit(tokenVector2_[next]) && tokenVector2_[next] != KeyWord::X_ && tokenVector2_[next] != KeyWord::x_)) ||
                    (token == Punctuator::dot && !std::isdigit(tokenVector2_[next]))) {
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
                if (next < tokenVector2_.size() &&
                    (tokenVector2_[next] == Punctuator::dot ||
                     std::isdigit(tokenVector2_[next])) ) {
                    errorManager_->SetErrorIndex(tokenVector2_[next]);
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
                if (next < tokenVector2_.size() &&
                    (tokenVector2_[next] == KeyWord::X_ ||
                    tokenVector2_[next] == KeyWord::x_)) {
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
        if (tokenVector2_[begin] == Punctuator::minus) {
            tokenVector2_[begin] = Punctuator::plus;
        } else if (tokenVector2_[begin] == Punctuator::plus) {
            tokenVector2_[begin] = Punctuator::minus;
        }
    }
}

bool Computor_v1::IsNoMinusAndPlus(char ch) {
    return ch != Punctuator::minus && ch != Punctuator::plus;
}

void Computor_v1::MoveTokenToLeftFromEqually(size_t equal_position) {
    if (tokenVector2_[tokenVector2_.size() - 2] == Punctuator::equally &&
        tokenVector2_[tokenVector2_.size() - 1] == '0') {
#if defined(UNIT_TESTS)
        std::string throw_str;
        throw_str.reserve(line_.size());
        for(size_t i = 0; i < tokenVector2_.size(); ++i) {
            throw_str += tokenVector2_[i];
        }
        throw throw_str;
#endif
        return;
    } else if (tokenVector2_[1] == Punctuator::equally &&
               tokenVector2_[0] == '0') {
        tokenVector2_.erase(tokenVector2_.begin(), tokenVector2_.begin() + 2);
    } else {
        if (equal_position > tokenVector2_.size() / 2) {
            if (IsNoMinusAndPlus(tokenVector2_[equal_position + 1])) {
                tokenVector2_[equal_position] = Punctuator::minus;
            } else {
                tokenVector2_.erase(tokenVector2_.begin() + equal_position);
                --equal_position;
            }
            ChangeMinusToPlus(equal_position + 1, tokenVector2_.size() - 1);
        } else {
            if (IsNoMinusAndPlus(tokenVector2_[0])) {
                tokenVector2_.insert(tokenVector2_.begin(), Punctuator::minus);
                ++equal_position;
            }
            ChangeMinusToPlus(2, equal_position - 1);
            tokenVector2_[equal_position] = Punctuator::plus;
        }
    }
    tokenVector2_.push_back('=');
    tokenVector2_.push_back('0');
#if defined(UNIT_TESTS)
    std::string throw_str;
    throw_str.reserve(line_.size());
    for(size_t i = 0; i < tokenVector2_.size(); ++i) {
        throw_str += tokenVector2_[i];
    }
    throw throw_str;
#endif

}

void Computor_v1::ShuntingAlgorithm() {
    for (auto& token: tokenVector2_) {
        (void)token;
    }
}

void Computor_v1::CreateElements() {
//    std::string buf_elem;
//    std::string buf_pow;
//    buf_elem.reserve(tokens_.size());
//    buf_pow.reserve(tokens_.size());
//    double num = 0;
//    int pow = 0;
//    bool is_full_form = false;
//    std::unique_ptr<Element> elem_ptr = CreateUniqElement();
//
//    for (size_t i = 0; i < tokens_.size(); ++i) {
//        char token = tokens_[i]->getToken();
//
//        switch (token) {
//            case Punctuator::plus:
//            case Punctuator::minus:
//                elem_ptr = CreateUniqElement();
//                if (!buf_elem.empty()) {
//                    try {
//                        num = std::stod(buf_elem);
//                    } catch (std::out_of_range) {
//                        errorManager_->SetErrorIndex(tokens_[i]->getPosition());
//                        errorManager_->AddErrorMessage(kOutOfRange);
//                        errorManager_->PrintErrors(line_);
//                        throw EXIT_FAILURE;
//                    }
//                }
//                elem_ptr->setNum(num);
//                elem_ptr->setPow(pow);
//                elem_ptr->setIsFulForm(is_full_form);
//                elem_ptr->setSign(static_cast<Punctuator>(token));
//                coef_.push_back(std::move(elem_ptr));
//                break;
//            case Punctuator::multiply: {
//                // after '*' can be 'digit' or 'X' or 'x'
//                 char next_token = tokens_[i + 1]->getToken();
//                if (std::isdigit(next_token)) {
//                    try {
////                        elem_ptr->  std::stod(buf);
//                    } catch (std::out_of_range) {
//                        errorManager_->SetErrorIndex(tokens_[i]->getPosition());
//                        errorManager_->AddErrorMessage(kOutOfRange);
//                        errorManager_->PrintErrors(line_);
//                        throw EXIT_FAILURE;
//                    }
//                    coef_.push_back(std::move(elem_ptr));
//                    buf_elem.clear();
//                }
//                break;
//            }
//            case Punctuator::equally:
//            case Punctuator::pow:
//                buf_elem.push_back(tokens_[i + 1]->getToken());
//            case Punctuator::dot:
//                buf_elem.push_back(token);
//                break;
//            case KeyWord::X_:
//            case KeyWord::x_:
//                is_full_form = true;
//                break;
//            default:
//                buf_elem.push_back(token);
//                break;
//        }
//    }
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
        expressionTree_ = creator_.getPlynomialExpressionTree();
    } else {
        //FIXME
        // implement the expression solution
    }

//    line_.clear();

//    CreateElements();
    return true;
}
