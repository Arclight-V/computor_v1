//
// Created by Arclight-V on 29.04.2023.
//

#include "Computor/Computor_v1.h"

bool Computor_v1::Analyzer(std::stringstream &ss) {
    std::string str;
    str.reserve(ss.str().size());
    while (!ss.eof()) {
        std::string tmp;
        ss >> tmp;
        str +=tmp;
    }
    if (!LexicalAnalyzer(str) || !SyntaxAnalyzer(str)) {
        return false;
    }

    return true;
}

bool Computor_v1::LexicalAnalyzer(const std::string &str) {
    for (size_t found = str.find_first_not_of(allow_chars);
        found != std::string::npos;
        found = str.find_first_not_of(allow_chars, found)) {

        //TODO: move to error_manager
        errorHandler.add(str + "\nInvalid character", found);
        ++found;
    }
    return errorHandler.empty();
}

bool Computor_v1::SyntaxAnalyzer(const std::string &str) {
    bool isEquality = false;
    for (auto first(std::begin(str)),
            second(first + 1);
            second != std::end(str); ++first, ++second) {
        //TODO: do it
        switch (*first) {
            case '=':
                if (!isEquality) {

                } else {

                }
            case 'x':
            case 'X':
                std::cout << *first << " ";
            default:
                break;
        }
    }

    return true;
}

void Computor_v1::PrintErrors() {
    errorHandler.PrintErrors();
}

#if defined(UNIT_TESTS)
bool TestComputor_v1::TestLexicalAnalyzer(Computor_v1& computorV1, const std::string& str) {
    return computorV1.LexicalAnalyzer(str);
};

bool TestComputor_v1::TestSyntaxAnalyzer(Computor_v1& computorV1, const std::string& str) {
    return computorV1.SyntaxAnalyzer(str);
};

#endif

