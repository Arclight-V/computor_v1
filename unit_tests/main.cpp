//
// Created by VV-Kalanchin on 20.04.2022.
//

#include <gtest/gtest.h>
#include "Computor_v1/Computor_v1.h"

TEST(BasicTest, PunctuatorCompare) {
    EXPECT_EQ(' ', gap);
    EXPECT_EQ('+', plus);
    EXPECT_EQ('-', minus);
    EXPECT_EQ('*', multiply);
    EXPECT_EQ('^', pow);
    EXPECT_EQ('.', dot);
    EXPECT_EQ('=', equally);
    EXPECT_EQ('(', left_bracket);
    EXPECT_EQ(')', right_bracket);
}
