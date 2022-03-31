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
    using node_s = std::shared_ptr<Node>;
private:
    // FIXME: change node to std::shared_ptr
    node_s polynomialZero_;
    node_s polynomialFirst_;
    node_s polynomialSecond;

    Node* evl(Node* link) {
        if (!link->getLeftNode().get() && !link->getRightNode().get()) {
            return link;
        }

        sum(link->getLeftNode(), link->getRightNode());

//        Node* left = evl(link->getLeftNode().get());
//        Node* right = evl(link->getRightNode().get());
//
//        (void)left;
//        (void)right;

        return nullptr;
    }

public:
    PolynomialExpressionTree() = default;
    PolynomialExpressionTree(const PolynomialExpressionTree& rhs) = delete;
    PolynomialExpressionTree(PolynomialExpressionTree&& rhs) = default;
    PolynomialExpressionTree& operator=(const PolynomialExpressionTree& rhs) = delete;
    PolynomialExpressionTree& operator=(PolynomialExpressionTree&& rhs) = default;
    virtual ~PolynomialExpressionTree() = default;

    virtual void addNode(node_s node) override {
        ExpressionTree::addNode(std::move(node));
    }

    virtual bool eval() override {
//        evl(ExpressionTree::tree_.get());
        return true;
    }

#if defined(UNIT_TESTS)

    node getTreeNode() { return std::move(tree_); }

#endif

};

#endif //COMPUTOR_V1_POLYNOMIALEXPRESSIONTREE_H
