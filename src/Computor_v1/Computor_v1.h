//
// Created by Anatashi on 04.01.2022.
//

#ifndef COMPUTOR_V1_Computor_v1_H
#define COMPUTOR_V1_Computor_v1_H


#include <string>
#include <vector>
#include <algorithm>

#include "ErrorManager/ErrorManager.h"
#include "Expression/PolynomialExpressionTree.h"
#include "Expression/Creator.h"

namespace {
    enum Punctuator {
        gap = ' ',
        plus = '+',
        minus = '-',
        multiply = '*',
        pow = '^',
        dot = '.',
        equally = '=',
        left_bracket = '(',
        right_bracket = ')',
        none
    };

    enum KeyWord {
        X_ = 'X',
        x_ = 'x',
    };

    enum Operators  {
        ADDITION = '+',
        SUBTRACTION = '-',
        MULTIPLICATION = '*',
        POWER = '^'
    };

    enum class Associativity {
        LEFT,
        RIGHT
    };

} // namespace


class Computor_v1 {
private:

    using error_handler = std::unique_ptr<ErrorManager>;
    using expression_tree = std::unique_ptr<PolynomialExpressionTree>;
    using token = char;
    using token_vector = std::vector<token>;

    std::string line_;
    error_handler errorManager_;
    token_vector tokenVector_;
    Creator creator_;
    expression_tree expressionTree_ = nullptr;

    class OperatorCv1 {
    private:

        Operators op_;
        Associativity associativity_;
        int precedence_;

    public:
        OperatorCv1() = delete;
        OperatorCv1(Operators op);
        OperatorCv1(const OperatorCv1& rhs) = delete;
        OperatorCv1(OperatorCv1&& rhs) = default;
        OperatorCv1& operator=(const OperatorCv1& rhs) = delete;

        Associativity getAssociativity() const;

        bool operator<(const OperatorCv1 &rhs) const;

        bool operator>(const OperatorCv1 &rhs) const;

        bool operator<=(const OperatorCv1 &rhs) const;

        bool operator>=(const OperatorCv1 &rhs) const;

    };

    bool IsKeyWord(char ch);
    bool IsPunctuator(char ch);
    bool IsOperator(char ch);
    bool LexicalAnalyzer();
    bool SyntaxAnalyzer(size_t& equal_position);
    void ChangeMinusToPlus(size_t begin, size_t end);
    bool IsNoMinusAndPlus(char ch);
    void MoveTokenToLeftFromEqually(size_t equal_position);
    // Shunting Yard Algorithm
    void ConvertInfixNotationToRPN();
    bool CreateTree();
    void CheckError();

public:
    Computor_v1() = delete;
    Computor_v1(const char* line);
    Computor_v1(const Computor_v1& rhs) = delete;
    Computor_v1& operator=(const Computor_v1& rhs) = delete;
    virtual ~Computor_v1() {};

    bool parse();
    void PrintSolution();
    void PrintError();
};


#endif //COMPUTOR_V1_Computor_v1_H
