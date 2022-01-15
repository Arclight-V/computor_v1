//
// Created by Anatashi on 14.01.2022.
//

#ifndef COMPUTOR_V1_ERRORMANAGER_H
#define COMPUTOR_V1_ERRORMANAGER_H

#include <iostream>
#include <list>
#include <vector>

#include "IErrorManager.h"

#define RED "\x1b[41m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

using error_list = std::list<std::string>;
using error_index = std::vector<bool>;

class ErrorManager  : public IErrorManager {
private:
    error_list errors_;
    error_index indexes_;

public:
    ErrorManager() = default;

    ErrorManager(const ErrorManager &rhs) = delete;

    virtual ~ErrorManager();

    ErrorManager &operator=(const ErrorManager &rhs) = delete;

    virtual void PrintError(std::string& line_);

    void SetErrorIndex(size_t position);

    void AddErrorMessage(const std::string& message);
};


#endif //COMPUTOR_V1_ERRORMANAGER_H
