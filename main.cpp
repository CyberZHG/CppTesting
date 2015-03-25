#include "ztest.h"
using namespace ztest;

class ExampleUnitTest : public UnitTest {
public:
    virtual void setUp() override final {}
    virtual void setUpEach() override final {}
    virtual void tearDownEach() override final {}
    virtual void tearDown() override final {}
protected:
    int inClassValue;
};

__TEST_U(ExampleUnitTest, test1) {
    __ASSERT_EQ(this->inClassValue, 1);
}
__TEST_U(ExampleUnitTest, test2) {
    __ASSERT_TRUE(true);
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
