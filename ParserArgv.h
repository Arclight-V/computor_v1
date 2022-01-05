//
// Created by Anatashi on 04.01.2022.
//

#ifndef COMPUTOR_V1_PARSERARGV_H
#define COMPUTOR_V1_PARSERARGV_H


#include <string>
#include <vector>

class ParserArgv {
private:

    enum arithmetic_sign {
        multiply = '*',
        degree = '^',
        plus = '+',
        minus = '-',
        divide = '/',
        equally = '=',
        none
    };

    class block {
    public:
        arithmetic_sign for_X_;
        float num_;
        float pow;
        arithmetic_sign for_next_block_;


        block() : for_X_(none),
                  num_(0),
                  for_next_block_(none) {};
        block(bool is_X,
              arithmetic_sign for_X,
              float num,
              arithmetic_sign for_next_block) : for_X_(for_X),
                                                num_(num),
                                                for_next_block_(for_next_block) {}
        block(const block& rhs) = delete;
        block& operator=(const block& rhs) = delete;
    };

    using coefficients = std::vector<std::unique_ptr<block>>;

    coefficients coef_;
    const std::string line_;

    void printError(std::vector<bool>& error_index);

public:
    ParserArgv() = delete;
    ParserArgv(const char* line);
    ParserArgv(const ParserArgv& rhs) = delete;
    ParserArgv& operator=(const ParserArgv& rhs) = delete;

    void parse();
};


#endif //COMPUTOR_V1_PARSERARGV_H
