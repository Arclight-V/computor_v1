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
    constexpr char kOutOfRange[] = "the converted value would fall out of the range of the result type";
}

Computor_v1::Computor_v1(const char* line) :  line_(line)
                                             {
    tokens_.reserve(line_.size());
    reverse_polish_notation_.reserve(line_.size());
    tokenVector2_.reserve(line_.size());
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

void Computor_v1::LexicalAnalyzer_v2() {
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
                if (next < tokens_.size() &&
                    (tokens_[next]->getToken() == Punctuator::dot ||
                    std::isdigit(tokens_[i - 1]->getToken())) ) {
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

size_t Computor_v1::SyntaxAnalyzer_v2() {
    bool is_equally = false;
    size_t pos_equally = 0;
    for (size_t i = 0; i < tokenVector2_.size(); ++i) {
        const size_t next = i + 1;
        const char token = tokenVector2_[i];
        switch (token) {
            case Punctuator::gap:
                break;
            case Punctuator::plus:
            case Punctuator::minus:
            case Punctuator::multiply:
            case Punctuator::equally:
            case Punctuator::pow:
            case Punctuator::dot: {
                if (next == tokenVector2_.size() ||
                    (i == 0 && token != Punctuator::plus && token != Punctuator::minus) ||
                    (next < tokenVector2_.size() && (!std::isdigit(tokenVector2_[next]) && tokenVector2_[next] != KeyWord::X_ && tokenVector2_[next] != KeyWord::x_)) ||
                    (token == Punctuator::dot && !std::isdigit(tokenVector2_[next]))) {
                    errorManager_->SetErrorIndex(i);
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                if (token == Punctuator::equally) {
                    if (!is_equally) {
                        is_equally = true;
                        pos_equally = i;
                    } else {
                        errorManager_->SetErrorIndex(i);
                        errorManager_->AddErrorMessage(kManyEquals);
                    }
                }
                break;
            }
            case KeyWord::X_:
            case KeyWord::x_:
                if (next < tokens_.size() &&
                    (tokenVector2_[next] == Punctuator::dot ||
                     std::isdigit(tokenVector2_[next])) ) {
                    errorManager_->SetErrorIndex(tokenVector2_[next]);
                    errorManager_->AddErrorMessage(kInvalidEntry);
                }
                break;
            default:
                break;
        }
    }
    return pos_equally;
}

void Computor_v1::MoveTokenToLeftFromEqually(size_t position) {
    size_t next_position = position + 1;
    if (tokenVector2_[next_position] == '0') {
        return;
    }

    if (std::isdigit(tokenVector2_[next_position]) || IsKeyWord(tokenVector2_[next_position])) {
        tokenVector2_[position] = Punctuator::minus;
    } else if (tokenVector2_[next_position] == Punctuator::minus) {
        tokenVector2_[position] = Punctuator::plus;
    } else {
        tokenVector2_[position] = Punctuator::minus;
    }

    for (size_t i = next_position + 1; i < tokenVector2_.size(); ++i) {
        char& token = tokenVector2_[i];

        if (token == Punctuator::minus) {
            token = Punctuator::plus;
        } else if (token == Punctuator::plus) {
            token = Punctuator::minus;
        }
    }
}

void Computor_v1::ShuntingAlgorithm() {
    for (auto& token: tokenVector2_) {
        (void)token;
    }
}

void Computor_v1::CreateElements() {
    std::string buf_elem;
    std::string buf_pow;
    buf_elem.reserve(tokens_.size());
    buf_pow.reserve(tokens_.size());
    double num = 0;
    int pow = 0;
    bool is_full_form = false;
    std::unique_ptr<Element> elem_ptr = CreateUniqElement();

    for (size_t i = 0; i < tokens_.size(); ++i) {
        char token = tokens_[i]->getToken();

        switch (token) {
            case Punctuator::plus:
            case Punctuator::minus:
                elem_ptr = CreateUniqElement();
                if (!buf_elem.empty()) {
                    try {
                        num = std::stod(buf_elem);
                    } catch (std::out_of_range) {
                        errorManager_->SetErrorIndex(tokens_[i]->getPosition());
                        errorManager_->AddErrorMessage(kOutOfRange);
                        errorManager_->PrintErrors(line_);
                        throw EXIT_FAILURE;
                    }
                }
                elem_ptr->setNum(num);
                elem_ptr->setPow(pow);
                elem_ptr->setIsFulForm(is_full_form);
                elem_ptr->setSign(static_cast<Punctuator>(token));
                coef_.push_back(std::move(elem_ptr));
                break;
            case Punctuator::multiply: {
                // after '*' can be 'digit' or 'X' or 'x'
                 char next_token = tokens_[i + 1]->getToken();
                if (std::isdigit(next_token)) {
                    try {
//                        elem_ptr->  std::stod(buf);
                    } catch (std::out_of_range) {
                        errorManager_->SetErrorIndex(tokens_[i]->getPosition());
                        errorManager_->AddErrorMessage(kOutOfRange);
                        errorManager_->PrintErrors(line_);
                        throw EXIT_FAILURE;
                    }
                    coef_.push_back(std::move(elem_ptr));
                    buf_elem.clear();
                }
                break;
            }
            case Punctuator::equally:
            case Punctuator::pow:
                buf_elem.push_back(tokens_[i + 1]->getToken());
            case Punctuator::dot:
                buf_elem.push_back(token);
                break;
            case KeyWord::X_:
            case KeyWord::x_:
                is_full_form = true;
                break;
            default:
                buf_elem.push_back(token);
                break;
        }
    }
}


void Computor_v1::parse() {
    if (line_.size() == 0) {
#if defined(UNIT_TESTS)
        throw line_;
#endif
        errorManager_->PrintError(kEmptyLine);
        throw EXIT_FAILURE;
    }

//    LexicalAnalyzer();
//    SyntaxAnalyzer();
    LexicalAnalyzer_v2();
    size_t pos_equally = SyntaxAnalyzer_v2();
    CheckError();
    MoveTokenToLeftFromEqually(pos_equally);
    for (auto& elem: tokenVector2_) {
        std::cout << elem;
    }
    std::cout << "\n";
    line_.clear();

//    CreateElements();
}

Computor_v1::Element::Element() :   num_(0),
                                    pow_(0),
                                    sign_(none),
                                    is_ful_form_(false) {}

double Computor_v1::Element::getNum() const {
    return num_;
}

void Computor_v1::Element::setNum(double num) {
    num_ = num;
}

int Computor_v1::Element::getPow() const {
    return pow_;
}

void Computor_v1::Element::setPow(int pow) {
    pow_ = pow;
}

Punctuator Computor_v1::Element::getSign() const {
    return sign_;
}

void Computor_v1::Element::setSign(Punctuator sign) {
    sign_ = sign;
}

bool Computor_v1::Element::isFulForm() const {
    return is_ful_form_;
}

void Computor_v1::Element::setIsFulForm(bool isFulForm) {
    is_ful_form_ = isFulForm;
};