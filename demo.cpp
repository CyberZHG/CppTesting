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
#include "include/test.h"

namespace test {

class ExampleUnitTest : public UnitTest {
 public:
    void setUp() final {}
    void setUpEach() final {}
    void tearDownEach() final {}
    void tearDown() final {}
 protected:
    bool func1(int x) {return x == 1;}
    bool func2(int x, int) {return x == 1;}
    bool func3(int x, int, int) {return x == 1;}
    bool func4(int x, int, int, int) {return x == 1;}
    bool func5(int x, int, int, int, int) {return x == 1;}
};

__TEST_U(ExampleUnitTest, test1) {
    __ASSERT_PRED_FORMAT1(func1, 2);
}

__TEST_U(ExampleUnitTest, test6) {
    __ASSERT_EQ(0, 1);
}

class CorrectUnitTest : public UnitTest {
};

__TEST_U(CorrectUnitTest, test1) {}
__TEST_U(CorrectUnitTest, test2) {}
__TEST_U(CorrectUnitTest, test3) {}
__TEST_U(CorrectUnitTest, test4) {}
__TEST_U(CorrectUnitTest, test5) {}

}  // namespace test

using test::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    framework->printToHtml("results.html");
    framework->finish();
    return !framework->isAllPassed();
}
