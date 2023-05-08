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
        str_0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a";
        ss_0 << str_0;
        computorV1_0 = std::make_unique<Computor_v1>(std::move(ss_0));

        str_1 = "a5 * X^b0 + b4 * Xb^1 - 9.3 * X^2 = 1 * X^0a";
        ss_1 << str_1;
        computorV1_1 = std::make_unique<Computor_v1>(std::move(ss_1));

        str_2 = "5 + 4 * X + X^2= X^2";
        ss_2 << str_2;
        computorV1_2 = std::make_unique<Computor_v1>(std::move(ss_2));

        str_3 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss_3 << str_3;
        computorV1_3 = std::make_unique<Computor_v1>(std::move(ss_3));


        str_4 = "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss_4 << str_4;
        computorV1_4 = std::make_unique<Computor_v1>(std::move(ss_4));

        str_5 = "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss_5 << str_5;
        computorV1_5 = std::make_unique<Computor_v1>(std::move(ss_5));

        str_6 = "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss_6 << str_6;
        computorV1_6 = std::make_unique<Computor_v1>(std::move(ss_6));


    }
    TestComputor_v1 t0;

    std::stringstream ss_0, ss_1, ss_2, ss_3, ss_4, ss_5, ss_6;
    std::string str_0, str_1, str_2, str_3, str_4, str_5, str_6;
    std::unique_ptr<Computor_v1> computorV1_0, computorV1_1, computorV1_2, computorV1_3, computorV1_4, computorV1_5,
                                    computorV1_6;
};

TEST_F(TestComputor_v1Fixture, LexicalAnalizer) {
    EXPECT_FALSE(t0.TestLexicalAnalyzer(*computorV1_0, str_0));
    EXPECT_FALSE(t0.TestLexicalAnalyzer(*computorV1_1, str_1));
}


TEST_F(TestComputor_v1Fixture, SyntaxAnalyzer) {
    EXPECT_TRUE(t0.TestSyntaxAnalyzer(*computorV1_2));
    EXPECT_TRUE(t0.TestSyntaxAnalyzer(*computorV1_3));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*computorV1_4));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*computorV1_5));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*computorV1_6));
}
