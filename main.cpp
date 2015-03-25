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
    __ASSERT_EQ(this->inClassValue, 1 + 2);
}

__TEST_U(ExampleUnitTest, test2) {
    __ASSERT_TRUE(true);
}

__TEST_U(ExampleUnitTest, test3) {
    __ASSERT_LE(1, 2);
}

__TEST_U(ExampleUnitTest, test4) {
    __ASSERT_STREQ("hello", "world");
}

__TEST_U(ExampleUnitTest, test5) {
    __ASSERT_STREQ("hello", "hello");
}

__TEST_U(ExampleUnitTest, test6) {
    __ASSERT_STRCASEEQ("hello", "HELLO");
}

__TEST_U(ExampleUnitTest, test7) {
    __ASSERT_STREQ("hello", "Hello");
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
