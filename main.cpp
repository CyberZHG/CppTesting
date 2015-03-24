#include <iostream>
#include "ztest.h"
using namespace std;
using namespace ztest;

class SampleUnitTest1 : public UnitTest {
};

__TEST_U(SampleUnitTest1, test1) {
    cout << "Hello" << endl;
}
__TEST_U(SampleUnitTest1, test2) {
    cout << "World" << endl;
}

class SampleUnitTest2 : public UnitTest {
public:
    virtual void setUp() {
        global = "Hello";
        cout << "Global Set Up" << endl;
    }
    virtual void setUpEach() {
        local = "world";
        cout << "Local Set Up" << endl;
    }
    virtual void tearDown() {
        cout << "Global Tear Down" << endl;
    }
    virtual void tearDownEach() {
        cout << "Local Tear Down" << endl;
    }
protected:
    string global;
    string local;
};

__TEST_U(SampleUnitTest2, test3) {
    cout << global << " " << local << endl;
}

__TEST_U(SampleUnitTest2, test4) {
    cout << global << " " << local << endl;
}

int main()
{
    Framework framework;
    framework.runTests();
    return 0;
}
