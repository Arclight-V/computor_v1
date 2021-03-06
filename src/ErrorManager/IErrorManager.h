//
// Created by Arclight Natashia on 1/15/22.
//

#ifndef COMPUTOR_V1_IERRORMANAGER_H
#define COMPUTOR_V1_IERRORMANAGER_H

#include <string>

// interface for the error manager
class IErrorManager {
public:
    virtual ~IErrorManager() = default;

    virtual void PrintErrors(const std::string& line) = 0;
    virtual void PrintError(const std::string& line) = 0;

};

#endif //COMPUTOR_V1_IERRORMANAGER_H
