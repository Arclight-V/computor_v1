//
// Created by Anatashi on 04.01.2022.
//

#ifndef COMPUTOR_V1_Computor_v1_H
#define COMPUTOR_V1_Computor_v1_H


#include <string>
#include <vector>

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
    public:
        double num_;
        int pow_;
        Punctuator sign_;

        virtual ~Element() = default;

        Element();
        Element(const Element& rhs) = delete;
        Element& operator=(const Element& rhs) = delete;

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

    coefficients coef_;
    token_vector tokens_;
    const std::string line_;
    error_handler errorManager_;

    bool IsKeyWord(char ch);
    bool IsPunctuator(char ch);
    void LexicalAnalyzer();
    void SyntaxAnalyzer();
    void CreateElements();
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
