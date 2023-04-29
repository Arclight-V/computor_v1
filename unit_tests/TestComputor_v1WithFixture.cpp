//
// Created by Arclight-V on 29.04.2023.
//

#include <gtest/gtest.h>
#include "../src/Computor/Computor_v1.h"

class Computor_v1Fixture : public ::testing::Test {

public:
    virtual ~Computor_v1Fixture() {
        delete c0;
    }
protected:
    virtual void SetUp() {
        c0 = new Computor_v1;
    }
    Computor_v1* c0;
    std::string s{"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0a"};
    std::string s1{"a5 * X^b0 + b4 * Xb^1 - 9.3 * X^2 = 1 * X^0a"};
};

TEST_F(Computor_v1Fixture, LexicalAnalizer) {
    EXPECT_FALSE(c0->LexicalAnalyzer(s));
    EXPECT_FALSE(c0->LexicalAnalyzer(s1));
}
