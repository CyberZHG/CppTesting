/* Copyright 2015 ZhaoHG */
#include "include/ztest.h"
using namespace ztest;

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

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    framework->printToHtml("results.html");
    framework->finish();
    return 0;
}
