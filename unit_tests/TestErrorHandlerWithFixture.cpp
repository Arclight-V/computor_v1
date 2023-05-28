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
        s0 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a";
        se0 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31ma\x1b[0m";
        eh0 = std::make_unique<ErrorHandler>(s0.str());

        s1 << "5 * X^0 + 4 * Xa^1 - 9.3 * X^2 = 1 * X^0";
        se1 = "5 * X^0 + 4 * X\x1b[31ma\x1b[0m^1 - 9.3 * X^2 = 1 * X^0";
        eh1 = std::make_unique<ErrorHandler>(s1.str());

        s2 << "a5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se2 = "\x1b[31ma\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh2 = std::make_unique<ErrorHandler>(s2.str());

        // INVALID FIRST CHARACTER
        s3 << "=5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se3 = "\x1b[31m=\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh3 = std::make_unique<ErrorHandler>(s3.str());

        s4 << "*5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se4 = "\x1b[31m*\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh4 = std::make_unique<ErrorHandler>(s4.str());

        s5 << "^5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se5 = "\x1b[31m^\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh5 = std::make_unique<ErrorHandler>(s5.str());

        // INVALID LAST CHARACTER
        s6 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0^";
        se6 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m^\x1b[0m";
        eh6 = std::make_unique<ErrorHandler>(s6.str());

        s7 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0*";
        se7 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m*\x1b[0m";
        eh7 = std::make_unique<ErrorHandler>(s7.str());

        s8 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        se8 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m=\x1b[0m";
        eh8 = std::make_unique<ErrorHandler>(s8.str());

        // INVALID FIRST CHARACTER
        s9 << ".5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se9 = "\x1b[31m.\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh9 = std::make_unique<ErrorHandler>(s9.str());

        // INVALID LAST CHARACTER
        s10 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0.";
        se10 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m.\x1b[0m";
        eh10 = std::make_unique<ErrorHandler>(s10.str());

        s11 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        se11 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m=\x1b[0m";
        eh11 = std::make_unique<ErrorHandler>(s11.str());

        s12 << "5 * 2^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0=";
        se12 = "5 * 2^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m=\x1b[0m";
        eh12 = std::make_unique<ErrorHandler>(s12.str());

        // INCORRECT ENTRY

        s13 << "**5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se13 = "\x1b[31m**\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh13 = std::make_unique<ErrorHandler>(s13.str());

        s14 << "***5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se14 = "\x1b[31m***\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh14 = std::make_unique<ErrorHandler>(s14.str());

        s15 << "****5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se15 = "\x1b[31m****\x1b[0m5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh15 = std::make_unique<ErrorHandler>(s15.str());

        s16 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0**";
        se16 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m**\x1b[0m";
        eh16 = std::make_unique<ErrorHandler>(s16.str());

        s17 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0***";
        se17 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m***\x1b[0m";
        eh17 = std::make_unique<ErrorHandler>(s17.str());

        s18 << "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0****";
        se18 = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\x1b[31m****\x1b[0m";
        eh18 = std::make_unique<ErrorHandler>(s18.str());

        s19 << "5 ** X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se19 = "5 \x1b[31m**\x1b[0m X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh19 = std::make_unique<ErrorHandler>(s19.str());

        s20 << "5 *** X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se20 = "5 \x1b[31m***\x1b[0m X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh20 = std::make_unique<ErrorHandler>(s20.str());

        s21 << "5 **** X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se21 = "5 \x1b[31m****\x1b[0m X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh21 = std::make_unique<ErrorHandler>(s21.str());


        // OPERATION NOT SUPPORTED

        s22 << "5 * X%0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se22 = "5 * \x1b[31mX%\x1b[0m0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh22 = std::make_unique<ErrorHandler>(s22.str());

        s23 << "5 * X/0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        se23 = "5 * \x1b[31mX/\x1b[0m0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
        eh23 = std::make_unique<ErrorHandler>(s23.str());


    }
    TestErrorHandler  teh;

    std::stringstream s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20,
                        s21, s22, s23;
    std::string se0, se1, se2, se3, se4, se5, se6, se7, se8, se9, se10, se11, se12, se13, se14, se15, se16, se17, se18,
                se19, se20, se21, se22, se23;
    std::unique_ptr<ErrorHandler> eh0, eh1, eh2, eh3, eh4, eh5, eh6, eh7, eh8, eh9, eh10, eh11, eh12, eh13, eh14, eh15,
                                    eh16, eh17, eh18, eh19, eh20, eh21, eh22, eh23;

};

TEST_F(TestErrorHandlerWithFixture, addAndPrint) {
    EXPECT_EQ(se0, teh.TestAdd(*eh0, errorhandler::err::INVALID_CHARACTER, 39).first);
    EXPECT_EQ(se1, teh.TestAdd(*eh1, errorhandler::err::INVALID_CHARACTER, 15).first);
    EXPECT_EQ(se2, teh.TestAdd(*eh2, errorhandler::err::INVALID_CHARACTER, 0).first);
    EXPECT_EQ(se3, teh.TestAdd(*eh3, errorhandler::err::INVALID_FIRST_CHARACTER, 0).first);
    EXPECT_EQ(se4, teh.TestAdd(*eh4, errorhandler::err::INVALID_FIRST_CHARACTER, 0).first);
    EXPECT_EQ(se5, teh.TestAdd(*eh5, errorhandler::err::INVALID_FIRST_CHARACTER, 0).first);
    EXPECT_EQ(se6, teh.TestAdd(*eh6, errorhandler::err::INVALID_LAST_CHARACTER, 39).first);
    EXPECT_EQ(se7, teh.TestAdd(*eh7, errorhandler::err::INVALID_LAST_CHARACTER, 39).first);
    EXPECT_EQ(se8, teh.TestAdd(*eh8, errorhandler::err::INVALID_LAST_CHARACTER, 39).first);
    EXPECT_EQ(se9, teh.TestAdd(*eh9, errorhandler::err::INVALID_FIRST_CHARACTER, 0).first);
    EXPECT_EQ(se10, teh.TestAdd(*eh10, errorhandler::err::INVALID_LAST_CHARACTER, 39).first);
    EXPECT_EQ(se11, teh.TestAdd(*eh11, errorhandler::err::TWO_EQUALS, 39).first);
    EXPECT_EQ(se12, teh.TestAdd(*eh12, errorhandler::err::TWO_EQUALS, 39).first);
    EXPECT_EQ(se13, teh.TestAdd(*eh13, errorhandler::err::INCORRECT_ENTRY, 0, 1).first);
    EXPECT_EQ(se14, teh.TestAdd(*eh14, errorhandler::err::INCORRECT_ENTRY, 0, 2).first);
    EXPECT_EQ(se15, teh.TestAdd(*eh15, errorhandler::err::INCORRECT_ENTRY, 0,  3).first);
    EXPECT_EQ(se16, teh.TestAdd(*eh16, errorhandler::err::INCORRECT_ENTRY, 39, 40).first);
    EXPECT_EQ(se17, teh.TestAdd(*eh17, errorhandler::err::INCORRECT_ENTRY, 39, 41).first);
    EXPECT_EQ(se18, teh.TestAdd(*eh18, errorhandler::err::INCORRECT_ENTRY, 39, 42).first);
    EXPECT_EQ(se19, teh.TestAdd(*eh19, errorhandler::err::INCORRECT_ENTRY, 2, 3).first);
    EXPECT_EQ(se20, teh.TestAdd(*eh20, errorhandler::err::INCORRECT_ENTRY, 2, 4).first);
    EXPECT_EQ(se21, teh.TestAdd(*eh21, errorhandler::err::INCORRECT_ENTRY, 2, 5).first);
    EXPECT_EQ(se22, teh.TestAdd(*eh22, errorhandler::err::INCORRECT_ENTRY, 4, 5).first);
    EXPECT_EQ(se23, teh.TestAdd(*eh23, errorhandler::err::INCORRECT_ENTRY, 4, 5).first);

}