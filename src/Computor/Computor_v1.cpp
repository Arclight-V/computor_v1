//
// Created by Arclight-V on 29.04.2023.
//

#include "Computor/Computor_v1.h"
#include <list>

Computor_v1::Computor_v1(std::stringstream &ss) : errorHandler_(ss.str()) {
    for (auto begin = std::istream_iterator<char>(ss), end = std::istream_iterator<char>(); begin != end; ++begin) {
        tokens_.push_back({*begin, static_cast<size_t>(ss.tellg()) - 1});
    }
}

bool Computor_v1::Analyzer() {
    LexicalAnalyzer();
    SyntaxAnalyzer();
    if (!errorHandler_.empty()) {
        return false;
    }

    return true;
}

bool Computor_v1::LexicalAnalyzer() {
    auto pred = [&](auto &first) {
        if (auto found = std::find(allow_tokens.begin(), allow_tokens.end(), first.first); found !=
                                                                                           allow_tokens.end()) {
            return false;
        }
        return true;
    };
    for (auto found = std::find_if(tokens_.begin(), tokens_.end(), pred);
         found != tokens_.end();
         found = std::find_if(++found, tokens_.end(), pred)) {
        errorHandler_.add(errorhandler::err::INVALID_CHARACTER,
                          std::next(tokens_.begin(), std::distance(tokens_.begin(), found))->second);;
    }
    return errorHandler_.empty();
}

bool Computor_v1::SyntaxAnalyzer() {
    auto check_first_last_elem = [=](char ch, errorhandler::err err, size_t pos) {
        switch (ch) {
            case '^':
            case '=':
            case '*':
            case '.':
                errorHandler_.add(err, pos);
                return false;
            default:
                return true;
        }
    };
    check_first_last_elem(tokens_.begin()->first, errorhandler::err::INVALID_FIRST_CHARACTER, 0);

    if (bool isEquality = false; !isEquality) {
        for (iterator first_token = tokens_.begin();
             first_token != tokens_.end(); ++first_token) {
            switch (first_token->first) {
                case '=':
                    if (!isEquality) {
                        isEquality = true;
                    } else {
                        errorHandler_.add(errorhandler::err::TWO_EQUALS, std::distance(tokens_.begin(), first_token));
                    }
                case '*':
                case '+':
                case '-':
                case '/':
                case '%':
                case '^':
                    if (auto ft = std::next(first_token, 1); ft != tokens_.end()) {
                        while (isArithmeticOperator(ft->first)) {
                            ++ft;
                        }
                        if (std::distance(first_token,  ft) != std::distance(first_token,std::next(first_token, 1))) {
                            --ft;
                            errorHandler_.add(errorhandler::err::INCORRECT_ENTRY, first_token->second, ft->second);
                            first_token = ft;
                        }
                    }
                case 'x':
                case 'X':

                default:
                    break;
            }
        }
    }

    check_first_last_elem(tokens_.back().first, errorhandler::err::INVALID_LAST_CHARACTER, tokens_.back().second);
    return errorHandler_.empty();
}

bool Computor_v1::isArithmeticOperator(const char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

void Computor_v1::PrintErrors() {
    errorHandler_.PrintErrors();
}

#if defined(UNIT_TESTS)
bool TestComputor_v1::TestLexicalAnalyzer(Computor_v1& computorV1) {
    return computorV1.LexicalAnalyzer();
};

bool TestComputor_v1::TestSyntaxAnalyzer(Computor_v1& computorV1) {
    return computorV1.SyntaxAnalyzer();
};

#endif

