//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_UNKNOWNNODE_H
#define COMPUTOR_V1_UNKNOWNNODE_H

#include "Expression/Node.h"

class UnknownNode : private Node {
private:
    char value_;
    int pow_ = 0;
public:
    UnknownNode() = delete;
    UnknownNode(const UnknownNode& rhs) = delete;
    UnknownNode& operator=(const UnknownNode& rhs) = delete;
    virtual ~UnknownNode() = default;

    UnknownNode(char value) : value_(value) {}

    char getValue() const { return value_; }
    void setPow(int pow) {pow_ = pow; }
};

#endif //COMPUTOR_V1_UNKNOWNNODE_H
