//
// Created by Anatashi on 14.01.2022.
//

#ifndef COMPUTOR_V1_ERRORMANAGER_H
#define COMPUTOR_V1_ERRORMANAGER_H

#include <iostream>
#include <list>
#include <vector>

#define RED "\x1b[41m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

using error_list = std::list<std::string>;
using error_index = std::vector<bool>;

class ErrorManager {
private:
    error_list errors_;
    error_index indexes_;

public:
    ErrorManager();

    ErrorManager(const ErrorManager &rhs) = delete;

    ErrorManager &operator=(const ErrorManager &rhs) = delete;

    void PrintError(std::string& line_);

    void SetErrorIndex(size_t position);
};


#endif //COMPUTOR_V1_ERRORMANAGER_H
