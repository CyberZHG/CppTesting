#include <iostream>
#include "ztest.h"
#include "stream_color.h"
using namespace std;
using namespace ztest;

class SampleUnitTest1 : public UnitTest {
};

__TEST_U(SampleUnitTest1, test1) {
    cout << yellow << "Hello" << white << endl;
}
__TEST_U(SampleUnitTest1, test2) {
    cout << magenta << "World" << white << endl;
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
