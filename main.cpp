#include "ztest.h"
using namespace ztest;

class ExampleUnitTest : public UnitTest {
public:
    virtual void setUp() override final {}
    virtual void setUpEach() override final {}
    virtual void tearDownEach() override final {}
    virtual void tearDown() override final {}
protected:
    bool func1(int x) {return x == 1;}
    bool func2(int x, int y) {return x == 1;}
    bool func3(int x, int y, int z) {return x == 1;}
    bool func4(int x, int y, int z, int a) {return x == 1;}
    bool func5(int x, int y, int z, int a, int b) {return x == 1;}
};

__TEST_U(ExampleUnitTest, test1) {
    __ASSERT_PRED_FORMAT1(func1, 1);
}

__TEST_U(ExampleUnitTest, test2) {
    int m = 2;
    __ASSERT_PRED_FORMAT1(func1, m);
}

__TEST_U(ExampleUnitTest, test3) {
    __ASSERT_PRED_FORMAT1(func1, 1 + 1);
}

__TEST_U(ExampleUnitTest, test4) {
    __ASSERT_PRED_FORMAT2(func2, 1 + 1, 1 + 2 * 3);
}

__TEST_U(ExampleUnitTest, test5) {
    __ASSERT_PRED_FORMAT3(func3, 1+1, 1+2*3, 5-6);
}

__TEST_U(ExampleUnitTest, test6) {
    __ASSERT_PRED_FORMAT4(func4, 1+1, 1+2*3, 5-6, 1/2);
}

__TEST_U(ExampleUnitTest, test7) {
    __ASSERT_PRED_FORMAT5(func5, 1+1, 1+2*3, 5-6, 1/2, 8);
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
