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
    return ch == ADDITION || ch == SUBTRACTION || ch == MULTIPLICATION || ch == POWER;
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
            case Punctuator::left_bracket:
                // TODO: add an implementation after completing the main part
                break;
            case Punctuator::right_bracket:
                // TODO: add an implementation after completing the main part
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

#if defined(UNIT_TESTS)
    tokenVector_.push_back('=');
    tokenVector_.push_back('0');
    std::string throw_str;
    throw_str.reserve(line_.size());
    for(size_t i = 0; i < tokenVector_.size(); ++i) {
        throw_str += tokenVector_[i];
    }
    throw throw_str;
#endif

}

void Computor_v1::ConvertInfixNotationToRPN() {
    token_vector RPNVector;
    RPNVector.reserve(tokenVector_.size());
    std::stack<token> operatorStack;

    for (size_t i = 0; i < tokenVector_.size(); ++i) {
        if (IsOperator(tokenVector_[i])) {
            while (!operatorStack.empty()) {
                OperatorCv1 op1 = OperatorCv1(static_cast<Operators>(tokenVector_[i]));
                OperatorCv1 op2 = OperatorCv1(static_cast<Operators>(tokenVector_[i]));
                if ((op1.getAssociativity() == Associativity::LEFT && op1 <= op2) ||
                (op1.getAssociativity() == Associativity::RIGHT && op1 < op2)) {
                    RPNVector.push_back(operatorStack.top());
                    operatorStack.pop();
                    continue;
                }
                break;
            }
            operatorStack.push(tokenVector_[i]);
        }
        else if (tokenVector_[i] == left_bracket) {
            // TODO: add an implementation after completing the main part
        }
        else if (tokenVector_[i] == right_bracket) {
            // TODO: add an implementation after completing the main part
        } else {
            RPNVector.push_back(tokenVector_[i]);
        }
    }

    tokenVector_ = RPNVector;
// TODO: delete
//    while(!operatorStack.empty()) {
//        RPNVector.push_back(operatorStack.top());
//        operatorStack.pop();
//    }
//
//    for (auto& elem : RPNVector) {
//        std::cout << elem;
//    }
//    std::cout << "\n";
}

bool Computor_v1::CreateTree() {


    return true;
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
        //FIX:
        expressionTree_ = std::move(creator_.getPlynomialExpressionTree());
    } else {
        // Computor_v2
        return false;
    }

    line_.clear();

    ConvertInfixNotationToRPN();

    if (CreateTree()) {
        return false;
    }


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
            precedence_ = 1;
            break;
        case POWER:
            associativity_ = Associativity::RIGHT;
            precedence_ = 2;
        default:
            break;
    }
}

bool Computor_v1::OperatorCv1::operator<(const Computor_v1::OperatorCv1 &rhs) const {
    return precedence_ < rhs.precedence_;
}

bool Computor_v1::OperatorCv1::operator>(const Computor_v1::OperatorCv1 &rhs) const {
    return rhs < *this;
}

bool Computor_v1::OperatorCv1::operator<=(const Computor_v1::OperatorCv1 &rhs) const {
    return !(rhs < *this);
}

bool Computor_v1::OperatorCv1::operator>=(const Computor_v1::OperatorCv1 &rhs) const {
    return !(*this < rhs);
}

Associativity Computor_v1::OperatorCv1::getAssociativity() const {
    return associativity_;
}
