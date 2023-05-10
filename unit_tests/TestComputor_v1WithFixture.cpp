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
        // INVALID CHARACTER
        s0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a";
        ss0 << s0;
        c0 = std::make_unique<Computor_v1>(std::move(ss0));

        s1 = "a5 * X^b0 + b4 * Xb^1 - 9.3 * X^2 = 1 * X^0a";
        ss1 << s1;
        c1 = std::make_unique<Computor_v1>(std::move(ss1));

        // ALL CHARACTER VALID
        s2 = "5 + 4 * X + X^2= X^2";
        ss2 << s2;
        c2 = std::make_unique<Computor_v1>(std::move(ss2));

        s3 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss3 << s3;
        c3 = std::make_unique<Computor_v1>(std::move(ss3));

        // IVALID FIRST CHARACTER
        s4 = "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss4 << s4;
        c4 = std::make_unique<Computor_v1>(std::move(ss4));

        s5 = "^5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss5 << s5;
        c5 = std::make_unique<Computor_v1>(std::move(ss5));

        s6 = "*5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss6 << s6;
        c6 = std::make_unique<Computor_v1>(std::move(ss6));

        s7 = ".5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        ss7 << s7;
        c7 = std::make_unique<Computor_v1>(std::move(ss7));

        // INVALID LAST CHARACTER
        s8 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        ss8 << s8;
        c8 = std::make_unique<Computor_v1>(std::move(ss8));

        s9 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0.";
        ss9 << s9;
        c9 = std::make_unique<Computor_v1>(std::move(ss9));

        s10 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0*";
        ss10 << s10;
        c10 = std::make_unique<Computor_v1>(std::move(ss10));

        s11 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0^";
        ss11 << s11;
        c11 = std::make_unique<Computor_v1>(std::move(ss11));

        s12 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        ss12 << s12;
        c12 = std::make_unique<Computor_v1>(std::move(ss12));


    }
    TestComputor_v1 t0;

    std::stringstream ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9, ss10, ss11, ss12;
    std::string s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;
    std::unique_ptr<Computor_v1> c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12;
};

TEST_F(TestComputor_v1Fixture, LexicalAnalizer) {
    EXPECT_FALSE(t0.TestLexicalAnalyzer(*c0, s0));
    EXPECT_FALSE(t0.TestLexicalAnalyzer(*c1, s1));
}


TEST_F(TestComputor_v1Fixture, SyntaxAnalyzer) {
    EXPECT_TRUE(t0.TestSyntaxAnalyzer(*c2));
    EXPECT_TRUE(t0.TestSyntaxAnalyzer(*c3));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c4));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c5));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c6));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c7));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c8));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c9));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c10));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c11));
    EXPECT_FALSE(t0.TestSyntaxAnalyzer(*c12));

}
