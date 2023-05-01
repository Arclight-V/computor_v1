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

    }
    TestErrorHandler  testErrorHandler;
    ErrorHandler errorHandler;
    std::string s{"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a"};
    std::string sErr{"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31ma\x1b[0m"};
    std::string s1{"5 * X^0 + 4 * Xa^1 - 9.3 * X^2 = 1 * X^0"};
    std::string sErr1{"5 * X^0 + 4 * X\x1b[31ma\x1b[0m^1 - 9.3 * X^2 = 1 * X^0"};
    std::string s2{"a5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"};
    std::string sErr2{"\x1b[31ma\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"};
};

TEST_F(TestErrorHandlerWithFixture, addAndPrint) {
    EXPECT_EQ(sErr, testErrorHandler.TestAdd(errorHandler, s, 39));
    EXPECT_EQ(sErr1, testErrorHandler.TestAdd(errorHandler, s1, 15));
    EXPECT_EQ(sErr2, testErrorHandler.TestAdd(errorHandler, s2, 0));
}