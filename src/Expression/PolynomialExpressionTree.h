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
    using node = std::unique_ptr<Node>;
private:
    node polynomialZero_;
    node polynomialFirst_;
    node polynomialSecond;

    StackNode stackNode_;
    node tree_;

public:
    PolynomialExpressionTree() = default;
    PolynomialExpressionTree(const PolynomialExpressionTree& rhs) = delete;
    PolynomialExpressionTree(PolynomialExpressionTree&& rhs) = default;
    PolynomialExpressionTree& operator=(const PolynomialExpressionTree& rhs) = delete;
    PolynomialExpressionTree& operator=(PolynomialExpressionTree&& rhs) = default;
    virtual ~PolynomialExpressionTree() = default;

    virtual void addNode(std::unique_ptr<Node> node) override {
        // TODO: add implementation
        if (node->getNodeType() == expression::oper) {
            node->setRightNode(stackNode_.pop());
            node->setLeftNode(stackNode_.pop());
            stackNode_.push(std::move(node));
        } else {
            stackNode_.push(std::move(node));
        }
    }

};

#endif //COMPUTOR_V1_POLYNOMIALEXPRESSIONTREE_H
