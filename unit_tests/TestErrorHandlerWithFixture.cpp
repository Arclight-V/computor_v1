//
// Created by Arclight-V on 01.05.2023.
//

#include <gtest/gtest.h>
#include "../src/ErrorHandler/ErrorHandler.h"

class TestErrorHandlerWithFixture : public ::testing::Test {

public:
    virtual ~TestErrorHandlerWithFixture() {}
protected:
    virtual void SetUp() {
        s_0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a";
        s_e_0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31ma\x1b[0m\n";
        s_e_0 += kInvalidCharacter;
        e_h_0 = std::make_unique<ErrorHandler>(s_0);

        s_1 = "5 * X^0 + 4 * Xa^1 - 9.3 * X^2 = 1 * X^0";
        s_e_1 = "5 * X^0 + 4 * X\x1b[31ma\x1b[0m^1 - 9.3 * X^2 = 1 * X^0\n";
        s_e_1 += kInvalidCharacter;
        e_h_1 = std::make_unique<ErrorHandler>(s_1);

        s_2 = "a5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        s_e_2 = "\x1b[31ma\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        s_e_2 += kInvalidCharacter;
        e_h_2 = std::make_unique<ErrorHandler>(s_2);

        s_3 = "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        s_e_3 = "\x1b[31m=\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        s_e_3 += kSyntaxErrorFirstCharacter;
        e_h_3 = std::make_unique<ErrorHandler>(s_3);

        s_4 = "*5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        s_e_4 = "\x1b[31m*\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        s_e_4 += kSyntaxErrorFirstCharacter;
        e_h_4 = std::make_unique<ErrorHandler>(s_4);

        s_5 = "^5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        s_e_5 = "\x1b[31m^\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        s_e_5 += kSyntaxErrorFirstCharacter;
        e_h_5 = std::make_unique<ErrorHandler>(s_5);

        s_6 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0^";
        s_e_6 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m^\x1b[0m\n";
        s_e_6 += kSyntaxErrorLastCharacter;
        e_h_6 = std::make_unique<ErrorHandler>(s_6);

        s_7 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0*";
        s_e_7 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m*\x1b[0m\n";
        s_e_7 += kSyntaxErrorLastCharacter;
        e_h_7 = std::make_unique<ErrorHandler>(s_7);

        s_8 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        s_e_8 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m=\x1b[0m\n";
        s_e_8 += kSyntaxErrorLastCharacter;
        e_h_8 = std::make_unique<ErrorHandler>(s_8);
    }
    TestErrorHandler  t_e_h;

    std::string s_0, s_1, s_2, s_3, s_4, s_5, s_6, s_7, s_8;
    std::string s_e_0, s_e_1, s_e_2, s_e_3, s_e_4, s_e_5, s_e_6, s_e_7, s_e_8;
    std::unique_ptr<ErrorHandler> e_h_0, e_h_1, e_h_2, e_h_3, e_h_4, e_h_5, e_h_6, e_h_7, e_h_8;

};

TEST_F(TestErrorHandlerWithFixture, addAndPrint) {
    EXPECT_EQ(s_e_0, t_e_h.TestAdd(*e_h_0, errorhandler::err::INVALID_CHARACTER, 39));
    EXPECT_EQ(s_e_1, t_e_h.TestAdd(*e_h_1, errorhandler::err::INVALID_CHARACTER, 15));
    EXPECT_EQ(s_e_2, t_e_h.TestAdd(*e_h_2, errorhandler::err::INVALID_CHARACTER, 0));
    EXPECT_EQ(s_e_3, t_e_h.TestAdd(*e_h_3, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(s_e_4, t_e_h.TestAdd(*e_h_4, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(s_e_5, t_e_h.TestAdd(*e_h_5, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(s_e_6, t_e_h.TestAdd(*e_h_6, errorhandler::err::INVALID_LAST_CHARACTER, 39));
    EXPECT_EQ(s_e_7, t_e_h.TestAdd(*e_h_7, errorhandler::err::INVALID_LAST_CHARACTER, 39));
    EXPECT_EQ(s_e_8, t_e_h.TestAdd(*e_h_8, errorhandler::err::INVALID_LAST_CHARACTER, 39));
}