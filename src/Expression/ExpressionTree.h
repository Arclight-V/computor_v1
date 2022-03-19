//
// Created by OUT-Kalanchin-VV on 12.03.2022.
//

#ifndef COMPUTOR_V1_EXPRESSIONTREE_H
#define COMPUTOR_V1_EXPRESSIONTREE_H

#include "Expression/Node.h"

class ExpressionTree {
public:
    ExpressionTree() = default;
    ExpressionTree(const ExpressionTree& rhs) = delete;
    ExpressionTree(ExpressionTree&& rhs) = delete;
    ExpressionTree& operator=(const ExpressionTree& rhs) = delete;
    ExpressionTree& operator=(ExpressionTree&& rhs) = delete;

    virtual ~ExpressionTree() = default;

    virtual void addNode(std::unique_ptr<Node> node) = 0;
};

#endif //COMPUTOR_V1_EXPRESSIONTREE_H
