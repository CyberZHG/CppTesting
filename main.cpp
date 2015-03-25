#include <iostream>
#include "ztest.h"
using namespace std;
using namespace ztest;

class SampleUnitTest1 : public UnitTest {
};

__TEST_U(SampleUnitTest1, test1) {
    __ASSERT_EQ(true, false);
}
__TEST_U(SampleUnitTest1, test2) {
    __ASSERT_EQ(1, 2);
}
__TEST_U(SampleUnitTest1, test3) {
    __ASSERT_EQ("hello", "world");
}
__TEST_U(SampleUnitTest1, test4) {
    __ASSERT_EQ(1.23, 4);
}

class SampleUnitTest2 : public UnitTest {
};

__TEST_U(SampleUnitTest2, test5) {
    __ASSERT_TRUE(1 == 1);
}

__TEST_U(SampleUnitTest2, test6) {
    __EXPECT_TRUE(1 == 0);
}

class SampleUnitTest3 : public UnitTest {
};

__TEST_U(SampleUnitTest3, test7) {
    __ASSERT_TRUE(1 == 1);
}

__TEST_U(SampleUnitTest3, test8) {
    __EXPECT_FALSE(1 == 0);
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
