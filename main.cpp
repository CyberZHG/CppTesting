#include <iostream>
#include "ztest.h"
using namespace std;
using namespace ztest;

class SampleUnitTest1 : public UnitTest {
};

__TEST_U(SampleUnitTest1, test1) {
    __ASSERT_TRUE(1 == 0);
    __ASSERT_TRUE(1 == 1);
}
__TEST_U(SampleUnitTest1, test2) {
    __ASSERT_FALSE(1 == 0);
    __ASSERT_FALSE(1 == 1);
}
__TEST_U(SampleUnitTest1, test3) {
    __EXPECT_TRUE(1 == 0);
    __EXPECT_TRUE(1 == 0);
}
__TEST_U(SampleUnitTest1, test4) {
    __EXPECT_FALSE(1 == 1);
    __EXPECT_FALSE(1 == 1);
}

class SampleUnitTest2 : public UnitTest {
public:
    virtual void setUp() {
        global = "Hello";
        cout << blue << "Global Set Up" << white << endl;
    }
    virtual void setUpEach() {
        local = "world";
        cout << magenta << "Local Set Up" << white << endl;
    }
    virtual void tearDown() {
        cout << blue << "Global Tear Down" << white << endl;
    }
    virtual void tearDownEach() {
        cout << magenta << "Local Tear Down" << white << endl;
    }
protected:
    string global;
    string local;
};

__TEST_U(SampleUnitTest2, test3) {
    cout << red << global << white << " " << local << endl;
}

__TEST_U(SampleUnitTest2, test4) {
    cout << global << " " << green << local << white << endl;
}

int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
