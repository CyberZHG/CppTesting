/* Copyright 2019 Zhao HG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */
#include "../include/test.h"

namespace test {

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

}  // namespace test

using test::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    return !framework->isAllPassed();
}

