//
// Created by Arclight-V on 29.04.2023.
//

#include "Computor/Computor_v1.h"

Computor_v1::Computor_v1(std::stringstream &&ss) : errorHandler_(ss.str()), ss_(std::move(ss)) {}

bool Computor_v1::Analyzer() {
    LexicalAnalyzer(ss_.str());
    SyntaxAnalyzer();
    if (!errorHandler_.empty()) {
        return false;
    }

    return true;
}

// TODO:: to delete signature, to use ss_.str()
bool Computor_v1::LexicalAnalyzer(const std::string &str) {
    for (size_t found = str.find_first_not_of(allow_chars);
        found != std::string::npos;
        found = str.find_first_not_of(allow_chars, found)) {
        errorHandler_.add(errorhandler::err::INVALID_CHARACTER, found);
        ++found;
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
    check_first_last_elem(ss_.str()[0], errorhandler::err::INVALID_FIRST_CHARACTER, 0);

    bool isEquality = false;
    while (!ss_.eof()) {
        std::string token;
        ss_ >> token;
        //TODO: do it (for not work!!!)
        for (auto first(std::begin(token)),
                     second(first + 1);
             second != std::end(token); ++first, ++second) {

            switch (*first) {
                case '=':
                    if (!isEquality) {
                        isEquality = true;
                    } else {
                        errorHandler_.add(errorhandler::err::TWO_EQUALS, ss_.tellg());
                    }
                case 'x':
                case 'X':
                default:
                    break;
            }
        }
    }

    check_first_last_elem(*(ss_.str().end() - 1), errorhandler::err::INVALID_LAST_CHARACTER, ss_.str().size() - 1);
    return errorHandler_.empty();
}

void Computor_v1::PrintErrors() {
    errorHandler_.PrintErrors();
}

#if defined(UNIT_TESTS)
bool TestComputor_v1::TestLexicalAnalyzer(Computor_v1& computorV1, const std::string& str) {
    return computorV1.LexicalAnalyzer(str);
};

bool TestComputor_v1::TestSyntaxAnalyzer(Computor_v1& computorV1) {
    return computorV1.SyntaxAnalyzer();
};

#endif

