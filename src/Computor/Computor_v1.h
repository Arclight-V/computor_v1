//
// Created by Владимир on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_V1_H
#define COMPUTOR_V1_COMPUTOR_V1_H

#include "Computor.h"

namespace {
    constexpr const char* allow_chars {"1234567890Xx*-+=^. "};
}

#if defined(UNIT_TESTS)
class Computor_v1;

class TestComputor_v1 {
public:
    TestComputor_v1() = default;
    ~TestComputor_v1() = default;
    bool TestLexicalAnalyzer(Computor_v1&, const std::string&);
    bool TestSyntaxAnalyzer(Computor_v1&, const std::string&);
};
#endif



class Computor_v1 : public Computor {

#if defined(UNIT_TESTS)
    friend class TestComputor_v1;
#endif

public:
    Computor_v1() = default;
    virtual ~Computor_v1() = default;

    // Computor
    bool Analyzer(const std::string& str) override;

private:
    // Computor
    bool LexicalAnalyzer(const std::string &str) override;
    bool SyntaxAnalyzer(const std::string& str) override;
};


#endif //COMPUTOR_V1_COMPUTOR_V1_H
