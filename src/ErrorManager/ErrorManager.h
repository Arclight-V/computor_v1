//
// Created by Anatashi on 14.01.2022.
//

#ifndef COMPUTOR_V1_ERRORMANAGER_H
#define COMPUTOR_V1_ERRORMANAGER_H

#include <iostream>
#include <list>
#include <vector>

#include "ErrorManager/IErrorManager.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

using error_list = std::list<std::string>;
using error_index = std::vector<bool>;

class ErrorManager  : public IErrorManager {
private:
    error_list errors_;
    error_index indexes_;

public:
    ErrorManager() = delete;
    ErrorManager(size_t size);
    ErrorManager(const ErrorManager &rhs) = delete;
    virtual ~ErrorManager() {};

    ErrorManager &operator=(const ErrorManager &rhs) = delete;

    // IErrorManger
    virtual void PrintErrors(const std::string& line_);
    virtual void PrintError(const std::string& line);

    void SetErrorIndex(size_t position);
    void AddErrorMessage(const std::string& message);
    bool isError() const;
};


#endif //COMPUTOR_V1_ERRORMANAGER_H
