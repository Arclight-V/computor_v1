//
// Created by Anatashi on 19.02.2022.
//

#include <iostream>

#include "Expression/Creator.h"

namespace {
    constexpr int kIntNumberFirst = 100;
    constexpr int kIntNumberNext = 200;
//
    constexpr double kDoubleNumberFirst = 100.01;
//    constexpr double kDoubleNumberNext = 200.50;
    constexpr char kOper = '+';
    constexpr char kX = 'X';
}

using uniq_node_ptr = std::unique_ptr<Node>;

int main() {
    Creator creator = Creator();

    uniq_node_ptr operatorNode(creator.createOperatorNode(kOper));
    std::cout << "operatorNode value_: " << *static_cast<OperatorNode*>(operatorNode.get()) << "\n";

    uniq_node_ptr numberNodeInt(creator.createNumberNodeInt(kIntNumberFirst));
    std::cout << "numberNodeInt value_: " << *static_cast<NumberNode<int>*>(numberNodeInt.get()) << "\n";

    uniq_node_ptr numberNodeDouble(creator.createNumberNodeDouble(kDoubleNumberFirst));
    std::cout << "numberNodeInt value_: " << *static_cast<NumberNode<double>*>(numberNodeDouble.get()) << "\n";

    uniq_node_ptr unknownNode(creator.createUnknowNode(kX));
    std::cout << "unknownNode value_: " << *static_cast<UnknownNode*>(unknownNode.get()) << "\n";

    uniq_node_ptr numberNodeIntNext(creator.createNumberNodeInt(kIntNumberNext));
    *static_cast<NumberNode<int>*>(numberNodeInt.get()) += *static_cast<NumberNode<int>*>(numberNodeIntNext.get());
    std::cout << "numberNodeInt value_: " << *static_cast<NumberNode<int>*>(numberNodeInt.get()) << "\n";
    std::cout << *static_cast<NumberNode<int>*>(numberNodeInt.get()) + *static_cast<NumberNode<int>*>(numberNodeIntNext.get()) << "\n";
    std::cout << (*static_cast<NumberNode<int>*>(numberNodeInt.get()) != *static_cast<NumberNode<int>*>(numberNodeIntNext.get())) << "\n";

    std::unique_ptr<ExpressionTree> pExpressionTree(creator.getPlynomialExpressionTree());
    PolynomialExpressionTree polynomialExpressionTree;
    return 0;

}
