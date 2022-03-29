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

//    StackNode stackNode_;
    node tree_;

    void push(node node_to_push) {
        if (tree_ == nullptr) {
            tree_ = std::move(node_to_push);
        } else {
            node_to_push->setRightNode(std::move(tree_));
            tree_ = std::move(node_to_push);
        }
    }

    node pop() {
        node p = std::move(tree_);
        tree_ = p->getRightNode();
        return p;
    }

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
            node->setRightNode(pop());
            node->setLeftNode(pop());
            push(std::move(node));
        } else {
            push(std::move(node));
        }
    }

#if defined(UNIT_TESTS)

    node getTreeNode() { return std::move(tree_); }

#endif

};

#endif //COMPUTOR_V1_POLYNOMIALEXPRESSIONTREE_H
