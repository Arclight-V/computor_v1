//
// Created by Anatashi on 21.01.2022.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Computor_v1/Computor_v1.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

void checkMoveTokenToLeftFromEqually() {
    std::unordered_map <std::string, std::string> values =  {
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0", "5*X^0+4*X^1-9.3*X^2-1*X^0"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2= -1 * X^0", "5*X^0+4*X^1-9.3*X^2+1*X^0"},
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = +1 * X^0", "5*X^0+4*X^1-9.3*X^2-1*X^0"},
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 0", "5*X^0+4*X^1-9.3*X^2"},
            {"0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "5*X^0+4*X^1-9.3*X^2"},
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = -1", "5*X^0+4*X^1-9.3*X^2+1"},
            {"1 * X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-1*X^0+5*X^0+4*X^1-9.3*X^2"},
            {"X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-X^0+5*X^0+4*X^1-9.3*X^2"},
            {"0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "5*X^0+4*X^1-9.3*X^2"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = 0 * X^0", "5*X^0+4*X^1-9.3*X^2-0*X^0"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = -0 * X^0", "5*X^0+4*X^1-9.3*X^2+0*X^0"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = 0 + 1", "5*X^0+4*X^1-9.3*X^2-0-1"},
            {"-1 * X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-1*X^0+5*X^0+4*X^1-9.3*X^2"}
    };

    std::cout << "Move token to left from equally test" << "\n";
    int i = 0;
    for (const auto& [key, value] : values) {
        Computor_v1 computorV1(key.c_str());
        std::cout << "Test " << ++i << " ";
//        std::cout << "\n" << key.c_str() << "\n";
        try {
            computorV1.parse();
        } catch (std::string str) {
            if (str != value) {
                std::cout << RED << "FAILURE"  << " " << key << '\n';
                std::cout << value << "\n" << GREEN << str << '\n' << NORMAL;
            } else {
                std::cout << GREEN << "OK" << '\n' << NORMAL;
//                std::cout << value << "\n" << GREEN << str << '\n' << NORMAL;
            }
        }
    }
}

void checkInvalidValues() {
    std::vector<std::string> vec_invalid_values = {"hello",
                                                   "",
                                                   "11",
                                                   "11 11",
                                                   "=",
                                                   ".0",
                                                   "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * 0X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5a * 0X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^0 & 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^0 + 4 * X^1 - 9.3 * X^2 == 1 * X^0",
                                                   "0.0.05 * X^0 + 4 * X^1 - 9.3 * X^2 == 1 * X^0 ",
                                                   "5 *-X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = *1 * X^0",
                                                   "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = 1 * X^*",
                                                   "5 * X^0.0. + 4 * X^1 - 9.3 * X^2 = 1 * ",
                                                   "*5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^-0 + 4 * X^-1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^.0 + 4 * X^-1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^5^005 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
                                                   "5 * X^5^0^05 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
                                                    };
    std::vector<std::string> vec_values;

    std::cout << "Invalid values test" << "\n";
    for (size_t i = 0; i < vec_invalid_values.size(); ++i) {
        Computor_v1 computorV1(vec_invalid_values[i].c_str());
        std::cout << "Test " << i + 1 << " ";
        try {
            computorV1.parse();
        } catch (std::string str) {
            std::cout << GREEN << "OK" << '\n' << NORMAL;
            continue;
        }
        std::cout << RED << "FAILURE" << '\n';
        std::cout << vec_invalid_values[i] << '\n' << NORMAL;
    }
}

void сheckReversePolishNotation() {
    std::unordered_map <std::string, std::string> values =  {
            {"5 * X^0 + 4*X^1 - 9.3 * X^2  = 0", "5X0^*4X1^*+9.3X2^*-"}
//            {"5 * X^0 + 4*X^1 - 9.3 * X^2= -1 * X^0", "5*X^0+4*X^1-9.3*X^2+1*X^0=0"},
//            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = +1 * X^0", "5*X^0+4*X^1-9.3*X^2-1*X^0=0"},
//            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 0", "5*X^0+4*X^1-9.3*X^2=0"},
//            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = -1", "5*X^0+4*X^1-9.3*X^2+1=0"},
//            {"1 * X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-1*X^0+5*X^0+4*X^1-9.3*X^2=0"},
//            {"X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-X^0+5*X^0+4*X^1-9.3*X^2=0"},
//            {"0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "5*X^0+4*X^1-9.3*X^2=0"},
//            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = 0 * X^0", "5*X^0+4*X^1-9.3*X^2-0*X^0=0"},
//            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = -0 * X^0", "5*X^0+4*X^1-9.3*X^2+0*X^0=0"},
//            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = 0 + 1", "5*X^0+4*X^1-9.3*X^2-0-1=0"},
//            {"-1 * X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-1*X^0+5*X^0+4*X^1-9.3*X^2=0"}
    };

    std::cout << "check Reverse Polish Notation" << "\n";
    int i = 0;
    for (const auto& [key, value] : values) {
        Computor_v1 computorV1(key.c_str());
        std::cout << "Test " << ++i << " ";
//        std::cout << "\n" << key.c_str() << "\n";
        try {
            computorV1.parse();
        } catch (std::string str) {
            if (str != value) {
                std::cout << RED << "FAILURE"  << " " << key << '\n';
                std::cout << value << "\n" << GREEN << str << '\n' << NORMAL;
            } else {
                std::cout << GREEN << "OK" << '\n' << NORMAL;
//                std::cout << value << "\n" << GREEN << str << '\n' << NORMAL;
            }
        }
    }
}

void inorder(std::unique_ptr<Node> node, std::string& str) {
    if (node == nullptr) {
        return;
    } else {
        inorder(node->getLeftNode(), str);
        switch (node->getNodeType()) {
            case expression::oper:
                str.push_back(static_cast<OperatorNode*>(node.get())->getOperator());
                break;
            case expression::number:
                str.push_back(static_cast<NumberNode<double>*>(node.get())->getValue());
                break;
            case expression::unknown:
                str.push_back(static_cast<UnknownNode*>(node.get())->getValue());
            default:
                break;
        }
        inorder(node->getRightNode(), str);
    }
}

std::string TreeToStr(std::unique_ptr<PolynomialExpressionTree> tree) {
    std::unique_ptr<Node> s_ptr = tree->getTreeNode();
    std::string str;

    inorder(std::move(s_ptr), str);

    return str;
}

void checkConstructTree() {
    std::unordered_map <std::string, std::string> values =  {
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0", "5*X^0+4*X^1-9.3*X^2-1*X^0"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2= -1 * X^0", "5*X^0+4*X^1-9.3*X^2+1*X^0"},
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = +1 * X^0", "5*X^0+4*X^1-9.3*X^2-1*X^0"},
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 0", "5*X^0+4*X^1-9.3*X^2"},
            {"0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "5*X^0+4*X^1-9.3*X^2"},
            {"5 * X^0 + 4 * X^1 - 9.3 * X^2 = -1", "5*X^0+4*X^1-9.3*X^2+1"},
            {"1 * X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-1*X^0+5*X^0+4*X^1-9.3*X^2"},
            {"X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-X^0+5*X^0+4*X^1-9.3*X^2"},
            {"0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "5*X^0+4*X^1-9.3*X^2"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = 0 * X^0", "5*X^0+4*X^1-9.3*X^2-0*X^0"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = -0 * X^0", "5*X^0+4*X^1-9.3*X^2+0*X^0"},
            {"5 * X^0 + 4*X^1 - 9.3 * X^2 = 0 + 1", "5*X^0+4*X^1-9.3*X^2-0-1"},
            {"-1 * X^0 = 5 * X^0 + 4 * X^1 - 9.3 * X^2", "-1*X^0+5*X^0+4*X^1-9.3*X^2"}
    };

    std::cout << "Checking tree traversal" << "\n";
    int i = 0;
    for (const auto& [key, value] : values) {
        Computor_v1 computorV1(key.c_str());
        std::cout << "Test " << ++i << " ";
//        std::cout << "\n" << key.c_str() << "\n";
        computorV1.parse();
        std::unique_ptr<PolynomialExpressionTree> tree = computorV1.getExpressionTree();
        std::string str = TreeToStr(std::move(tree));
        if (str != value) {
            std::cout << RED << "FAILURE"  << " " << key << '\n';
            std::cout << value << "\n" << GREEN << str << '\n' << NORMAL;
        } else {
            std::cout << GREEN << "OK" << '\n' << NORMAL;
//            std::cout << value << "\n" << GREEN << str << '\n' << NORMAL;
        }
    }

}

int main() {
//    checkInvalidValues();
//    checkMoveTokenToLeftFromEqually();
    сheckReversePolishNotation();
//    checkConstructTree();

    return 0;
}
