//
// Created by Anatashi on 12.03.2022.
//

#ifndef COMPUTOR_V1_POLYNOMIALEXPRESSIONTREE_H
#define COMPUTOR_V1_POLYNOMIALEXPRESSIONTREE_H

#include "Expression/ExpressionTree.h"
#include "Expression/NumberNode.h"
#include "Expression/UnknownNode.h"
#include "Expression/OperatorNode.h"

//TODO
// implement a tree that solves a polynomial second or lower degree equation.


class PolynomialExpressionTree : public ExpressionTree {
public:
    PolynomialExpressionTree() = default;
    virtual ~PolynomialExpressionTree() = default;

    virtual void addNode(std::unique_ptr<Node> node) override {
        (void)node;
    }

};

#endif //COMPUTOR_V1_POLYNOMIALEXPRESSIONTREE_H
