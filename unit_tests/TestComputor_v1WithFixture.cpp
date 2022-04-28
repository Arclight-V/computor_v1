//
// Created by VV-Kalanchin on 21.04.2022.
//

#include <gtest/gtest.h>
#include "Computor_v1/Computor_v1.h"

class Computor_v1Fixture : public ::testing::Test {
public:
    virtual ~Computor_v1Fixture() {
        delete cp0;
        delete utcp;
    }

protected:
    virtual void SetUp() {
        utcp = new UnitTestComputor_v1();
        cp0 = new Computor_v1("test_line");

    }
    Computor_v1* cp0;
    UnitTestComputor_v1* utcp;
};

TEST_F(Computor_v1Fixture, AllPointersAreEqualNullptr) {
    EXPECT_NE(0, utcp->getLine(*cp0).size());
    EXPECT_EQ("test_line", utcp->getLine(*cp0));
}
