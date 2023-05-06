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
        str_0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a";
        str_err_0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31ma\x1b[0m\n";
        str_err_0 += kInvalidCharacter;
        errorHandler_0 = std::make_unique<ErrorHandler>(str_0);

        str_1 = "5 * X^0 + 4 * Xa^1 - 9.3 * X^2 = 1 * X^0";
        str_err_1 = "5 * X^0 + 4 * X\x1b[31ma\x1b[0m^1 - 9.3 * X^2 = 1 * X^0\n";
        str_err_1 += kInvalidCharacter;
        errorHandler_1 = std::make_unique<ErrorHandler>(str_1);

        str_2 = "a5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        str_err_2 = "\x1b[31ma\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n";
        str_err_2 += kInvalidCharacter;
        errorHandler_2 = std::make_unique<ErrorHandler>(str_2);
    }
    TestErrorHandler  testErrorHandler;

    std::string str_0, str_1, str_2;
    std::string str_err_0, str_err_1, str_err_2;
    std::unique_ptr<ErrorHandler> errorHandler_0, errorHandler_1, errorHandler_2;

};

TEST_F(TestErrorHandlerWithFixture, addAndPrint) {
    EXPECT_EQ(str_err_0, testErrorHandler.TestAdd(*errorHandler_0, errorhandler::err::INVALID_CHARACTER, 39));
    EXPECT_EQ(str_err_1, testErrorHandler.TestAdd(*errorHandler_1, errorhandler::err::INVALID_CHARACTER, 15));
    EXPECT_EQ(str_err_2, testErrorHandler.TestAdd(*errorHandler_2, errorhandler::err::INVALID_CHARACTER, 0));
}