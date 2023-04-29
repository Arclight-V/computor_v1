//
// Created by Arclight-V on 29.04.2023.
//

#include <gtest/gtest.h>
#include "../src/Computor/Computor_v1.h"

class TestComputor_v1Fixture : public ::testing::Test {

public:
    virtual ~TestComputor_v1Fixture() {

    }
protected:
    virtual void SetUp() {

    }
    TestComputor_v1 t0;
    Computor_v1 c0;
    std::string s{"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a"};
    std::string s1{"a5 * X^b0 + b4 * Xb^1 - 9.3 * X^2 = 1 * X^0a"};
    std::string s2{"5 + 4 * X + X^2= X^2"};
    std::string s3{"a5 * X^b0 + b4 * Xb^1 - 9.3 * X^2 = 1 * X^0a"};
};

TEST_F(TestComputor_v1Fixture, LexicalAnalizer) {
    EXPECT_FALSE(t0.TestLexicalAnalyzer(c0, s));
    EXPECT_FALSE(t0.TestLexicalAnalyzer(c0, s1));
}

TEST_F(TestComputor_v1Fixture, SyntaxAnalyzer) {
    EXPECT_TRUE(t0.TestSyntaxAnalyzer(c0, s2));
    EXPECT_TRUE(t0.TestSyntaxAnalyzer(c0, s3));
}
