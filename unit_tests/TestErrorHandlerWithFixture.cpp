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
        // INVALID CHARACTER
        s0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a";
        se0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31ma\x1b[0m\n";
        se0 += kInvalidCharacter;
        eh0 = std::make_unique<ErrorHandler>(s0);

        s1 = "5 * X^0 + 4 * Xa^1 - 9.3 * X^2 = 1 * X^0";
        se1 = "5 * X^0 + 4 * X\x1b[31ma\x1b[0m^1 - 9.3 * X^2 = 1 * X^0\n";
        se1 += kInvalidCharacter;
        eh1 = std::make_unique<ErrorHandler>(s1);

        s2 = "a5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se2 = "\x1b[31ma\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        se2 += kInvalidCharacter;
        eh2 = std::make_unique<ErrorHandler>(s2);

        // INVALID FIRST CHARACTER
        s3 = "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se3 = "\x1b[31m=\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        se3 += kSyntaxErrorFirstCharacter;
        eh3 = std::make_unique<ErrorHandler>(s3);

        s4 = "*5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se4 = "\x1b[31m*\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        se4 += kSyntaxErrorFirstCharacter;
        eh4 = std::make_unique<ErrorHandler>(s4);

        s5 = "^5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se5 = "\x1b[31m^\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        se5 += kSyntaxErrorFirstCharacter;
        eh5 = std::make_unique<ErrorHandler>(s5);

        // INVALID LAST CHARACTER
        s6 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0^";
        se6 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m^\x1b[0m\n";
        se6 += kSyntaxErrorLastCharacter;
        eh6 = std::make_unique<ErrorHandler>(s6);

        s7 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0*";
        se7 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m*\x1b[0m\n";
        se7 += kSyntaxErrorLastCharacter;
        eh7 = std::make_unique<ErrorHandler>(s7);

        s8 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        se8 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m=\x1b[0m\n";
        se8 += kSyntaxErrorLastCharacter;
        eh8 = std::make_unique<ErrorHandler>(s8);

        // INVALID FIRST CHARACTER
        s9 = ".5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se9 = "\x1b[31m.\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        se9 += kSyntaxErrorFirstCharacter;
        eh9 = std::make_unique<ErrorHandler>(s9);

        // INVALID LAST CHARACTER
        s10 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0.";
        se10 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m.\x1b[0m\n";
        se10 += kSyntaxErrorLastCharacter;
        eh10 = std::make_unique<ErrorHandler>(s10);
    }
    TestErrorHandler  teh;

    std::string s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    std::string se0, se1, se2, se3, se4, se5, se6, se7, se8, se9, se10;
    std::unique_ptr<ErrorHandler> eh0, eh1, eh2, eh3, eh4, eh5, eh6, eh7, eh8, eh9, eh10;

};

TEST_F(TestErrorHandlerWithFixture, addAndPrint) {
    EXPECT_EQ(se0, teh.TestAdd(*eh0, errorhandler::err::INVALID_CHARACTER, 39));
    EXPECT_EQ(se1, teh.TestAdd(*eh1, errorhandler::err::INVALID_CHARACTER, 15));
    EXPECT_EQ(se2, teh.TestAdd(*eh2, errorhandler::err::INVALID_CHARACTER, 0));
    EXPECT_EQ(se3, teh.TestAdd(*eh3, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(se4, teh.TestAdd(*eh4, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(se5, teh.TestAdd(*eh5, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(se6, teh.TestAdd(*eh6, errorhandler::err::INVALID_LAST_CHARACTER, 39));
    EXPECT_EQ(se7, teh.TestAdd(*eh7, errorhandler::err::INVALID_LAST_CHARACTER, 39));
    EXPECT_EQ(se8, teh.TestAdd(*eh8, errorhandler::err::INVALID_LAST_CHARACTER, 39));
    EXPECT_EQ(se9, teh.TestAdd(*eh9, errorhandler::err::INVALID_FIRST_CHARACTER, 0));
    EXPECT_EQ(se10, teh.TestAdd(*eh10, errorhandler::err::INVALID_LAST_CHARACTER, 39));
}