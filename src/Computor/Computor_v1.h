//
// Created by Владимир on 29.04.2023.
//

#ifndef COMPUTOR_V1_COMPUTOR_V1_H
#define COMPUTOR_V1_COMPUTOR_V1_H

#include <iostream>
#include <vector>
#include <array>
#include <list>

#include "Computor/Computor.h"
#include "ErrorHandler/ErrorHandler.h"

namespace {
    constexpr const  std::array<char, 18> allow_tokens {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                                       'X', 'x',
                                                       '*', '-', '+', '=', '^', '.' };
}


#if defined(UNIT_TESTS)
class Computor_v1;

class TestComputor_v1 {
public:
    TestComputor_v1() = default;
    ~TestComputor_v1() = default;
    bool TestLexicalAnalyzer(Computor_v1&);
    bool TestSyntaxAnalyzer(Computor_v1&);
};
#endif



class Computor_v1 : public Computor {

    using token = char;
    using position = size_t;

#if defined(UNIT_TESTS)
    friend class TestComputor_v1;
#endif

public:
    explicit Computor_v1(std::stringstream &ss);
    virtual ~Computor_v1() = default;

    // Computor
    bool Analyzer() override;
    void PrintErrors() override;
private:

    // Computor
    bool LexicalAnalyzer() override;
    bool SyntaxAnalyzer() override;
    bool isArithmeticOperator(const char ch) override;
    void print() override;

    void Transform();


    using iterator = std::list<std::pair<token , position >>::iterator;
    std::list<std::pair<token, position>> tokens_;
    ErrorHandler errorHandler_;
};


#endif //COMPUTOR_V1_COMPUTOR_V1_H
