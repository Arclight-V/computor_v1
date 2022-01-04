//
// Created by Anatashi on 04.01.2022.
//

#ifndef COMPUTOR_V1_PARSERARGV_H
#define COMPUTOR_V1_PARSERARGV_H


#include <string>

class ParserArgv {
private:

    std::string line_;

    enum arithmetic_sign {
        multiply = '*',
        degree = '^',
        plus = '+',
        minus = '-',
        divide = '/',
        equally = '='
    };

    struct block {
        bool is_X;
        arithmetic_sign for_X;
        float num;
        arithmetic_sign for_next_block;

    };

    void printError(std::vector<bool>& error_index) ;

public:
    ParserArgv() = delete;
    ParserArgv(const char* line);
    ParserArgv(const ParserArgv& rhs) = delete;
    ParserArgv& operator=(const ParserArgv& rhs) = delete;

    void parse();
};


#endif //COMPUTOR_V1_PARSERARGV_H
