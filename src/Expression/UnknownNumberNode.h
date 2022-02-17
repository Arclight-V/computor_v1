//
// Created by Sergey Sudnichnikov on 17.02.2022.
//

#ifndef COMPUTOR_V1_UNKNOWNNUMBERNODE_H
#define COMPUTOR_V1_UNKNOWNNUMBERNODE_H

#include "Expression/Node.h"

template <typename T>
class UnknownNumberNode : private Node {
private:
    T value_;
public:
    UnknownNumberNode() = delete;
    UnknownNumberNode(const UnknownNumberNode& rhs) = delete;
    UnknownNumberNode& operator=(const UnknownNumberNode& rhs) = delete;
    virtual ~UnknownNumberNode() = default;

    UnknownNumberNode(T value) : value_(value) {}

    T getValue() const { return value_; }
};

// Relational Operators
template <typename T>
bool operator==(const UnknownNumberNode<T>& lhs, const UnknownNumberNode<T>& rhs) { return lhs.getValue() == rhs.getValue(); }

template <typename T>
bool operator!=(const UnknownNumberNode<T>& lhs, const UnknownNumberNode<T>& rhs) { return lhs.getValue() != rhs.getValue(); }

template <typename T>
bool operator<(const UnknownNumberNode<T>& lhs, const UnknownNumberNode<T>& rhs) { return lhs.getValue() < rhs.getValue(); }

template <typename T>
bool operator<=(const UnknownNumberNode<T>& lhs, const UnknownNumberNode<T>& rhs) { return lhs.getValue() <= rhs.getValue(); }

template <typename T>
bool operator>(const UnknownNumberNode<T>& lhs, const UnknownNumberNode<T>& rhs) { return lhs.getValue() > rhs.getValue(); }

template <typename T>
bool operator>=(const UnknownNumberNode<T>& lhs, const UnknownNumberNode<T>& rhs) { return lhs.getValue() >= rhs.getValue(); }



#endif //COMPUTOR_V1_UNKNOWNNUMBERNODE_H
