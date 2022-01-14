//
// Created by Anatashi on 04.01.2022.
//

#ifndef COMPUTOR_V1_PARSERARGV_H
#define COMPUTOR_V1_PARSERARGV_H


#include <string>
#include <vector>

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

class ParserArgv {
private:

    class block {
    public:
        double num_;
        int pow_;
        Punctuator sign_;

        block() : num_(0),
                  pow_(0),
                  sign_(none) {};
        block(double num,
              double pow,
              Punctuator sign) : num_(num),
                                 pow_(pow),
                                 sign_(sign) {
        }
        block(const block& rhs) = delete;
        block& operator=(const block& rhs) = delete;
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

    using coefficients = std::vector<std::unique_ptr<block>>;
    using token_vector = std::vector<std::unique_ptr<Token>>;

    coefficients coef_;
    token_vector tokens_;

    const std::string line_;
    std::string token_line_;

    std::vector<bool> error_index_;

    bool IsKeyWord(char ch);
    bool IsPunctuator(char ch);
    void CreateTokens();
    void CheckTokens();
    void LexicalAnalyzer();

    void analyzeTerm(std::string& line, size_t first, size_t last);
    void CheckError();
    void PrintError();

public:
    ParserArgv() = delete;
    ParserArgv(const char* line);
    ParserArgv(const ParserArgv& rhs) = delete;
    ParserArgv& operator=(const ParserArgv& rhs) = delete;

    void parse();
};


#endif //COMPUTOR_V1_PARSERARGV_H
