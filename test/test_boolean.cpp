/* Copyright 2015 ZhaoHG */
#include "../include/ztest.h"

namespace ztest {

class TestBoolean : public UnitTest {
};

__TEST_U(TestBoolean, testAssertTrue_True) {
    __ASSERT_TRUE(1 == 1);
}

__TEST_U(TestBoolean, testAssertTrue_False) {
    __ASSERT_TRUE(0 == 1);
}

__TEST_U(TestBoolean, testAssertFalse_True) {
    __ASSERT_FALSE(1 == 1);
}

__TEST_U(TestBoolean, testAssertFalse_False) {
    __ASSERT_FALSE(0 == 1);
}

__TEST_U(TestBoolean, testExpectTrue_True) {
    __EXPECT_TRUE(1 == 1);
}

__TEST_U(TestBoolean, testExpectTrue_False) {
    __EXPECT_TRUE(0 == 1);
}

__TEST_U(TestBoolean, testExpectTrue_False_Continue) {
    __EXPECT_TRUE(0 == 1);
    __ASSERT_TRUE(false);
}

__TEST_U(TestBoolean, testExpectFalse_True) {
    __EXPECT_FALSE(1 == 1);
}

__TEST_U(TestBoolean, testExpectFalse_True_Continue) {
    __EXPECT_FALSE(1 == 1);
    __ASSERT_TRUE(false);
}

__TEST_U(TestBoolean, testExpectFalse_False) {
    __EXPECT_FALSE(0 == 1);
}

}  // namespace ztest

using ztest::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    return !framework->isAllPassed();
}

