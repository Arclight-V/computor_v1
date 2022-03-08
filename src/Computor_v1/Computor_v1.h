//
// Created by Anatashi on 04.01.2022.
//

#ifndef COMPUTOR_V1_Computor_v1_H
#define COMPUTOR_V1_Computor_v1_H


#include <string>
#include <vector>
#include <algorithm>

#include "ErrorManager/ErrorManager.h"

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
} // namespace


class Computor_v1 {
private:

    class Element {
    private:
        double num_;
        int pow_;
        Punctuator sign_;
        bool is_ful_form_;
    public:
        virtual ~Element() = default;

        Element();
        Element(const Element& rhs) = delete;
        Element& operator=(const Element& rhs) = delete;

        double getNum() const;

        void setNum(double num);

        int getPow() const;

        void setPow(int pow);

        Punctuator getSign() const;

        void setSign(Punctuator sign);

        bool isFulForm() const;

        void setIsFulForm(bool isFulForm);

    };

    /*
     * The class is needed to store data about the token and its position in the source line
     */
    class Token {
    private:
        char token_;
        size_t position_;
    public:

        Token() = delete;
        Token(char token, size_t position) : token_(token),
                                             position_(position) {};
        Token(const Token& rhs) = delete;
        Token& operator=(const Token& rhs) = delete;

        virtual ~Token() = default;

        char getToken() const {
            return token_;
        };

        void setToken(char token) {
            token_ = token;
        };

        size_t getPosition() const {
            return position_;
        };

        void setPosition(size_t position) {
            position_ = position;
        };
    };

    using coefficients = std::vector<std::unique_ptr<Element>>;
    using token_vector = std::vector<std::unique_ptr<Token>>;
    using error_handler = std::unique_ptr<ErrorManager>;
    using token = char;
    using token_vector2 = std::vector<token>;

    coefficients coef_;
    token_vector tokens_;
    std::string line_;
    std::string reverse_polish_notation_;
    error_handler errorManager_;
    token_vector2 tokenVector2_;

    bool IsKeyWord(char ch);
    bool IsPunctuator(char ch);
    void LexicalAnalyzer();
    void LexicalAnalyzer_v2();
    void SyntaxAnalyzer();
    size_t SyntaxAnalyzer_v2();
    void MoveTokenToLeftFromEqually(size_t position);
    void CreateElements();
    // Shunting Yard Algorithm
    void ShuntingAlgorithm();
    void CheckError();

    std::unique_ptr<Element> CreateUniqElement() { return std::make_unique<Element>();};

public:
    Computor_v1() = delete;
    Computor_v1(const char* line);
    Computor_v1(const Computor_v1& rhs) = delete;
    Computor_v1& operator=(const Computor_v1& rhs) = delete;

    void parse();
};


#endif //COMPUTOR_V1_Computor_v1_H
