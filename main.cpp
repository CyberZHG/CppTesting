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
    void normalFunc() {}
    void exptFunc() {throw inClassValue;}
};

__TEST_U(ExampleUnitTest, test1) {
    __ASSERT_THROW(normalFunc(), int);
}

__TEST_U(ExampleUnitTest, test2) {
    __ASSERT_THROW(exptFunc(), int);
}

__TEST_U(ExampleUnitTest, test3) {
    __ASSERT_THROW(exptFunc(), char);
}

__TEST_U(ExampleUnitTest, test4) {
    __ASSERT_ANY_THROW(normalFunc());
}

__TEST_U(ExampleUnitTest, test5) {
    __ASSERT_ANY_THROW(exptFunc());
}

__TEST_U(ExampleUnitTest, test6) {
    __ASSERT_NO_THROW(normalFunc());
}

__TEST_U(ExampleUnitTest, test7) {
    __ASSERT_NO_THROW(exptFunc());
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
