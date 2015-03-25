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
    ztest::StaticAssertTypeEq<int, bool>();
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
