#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <map>
#include <string>
#include "test_cases.h"

namespace ztest {

/**
 * Unit test base class.
 */
class UnitTest
{
public:
    UnitTest();
    virtual ~UnitTest();

    /**< Will be invoked before testing. */
    virtual void setUp();
    /**< Will be invoked after testing. */
    virtual void tearDown();
    /**< Will be invoked before testing a single test case. */
    virtual void setUpEach();
    /**< Will be invoked after testing a single test case. */
    virtual void tearDownEach();

    virtual void test();
};

#define __TEST_U(suite, name) \
class __TEST_CLASS_##suite##_##name##_ : public suite { \
public: \
    void run() { \
        this->setUpEach(); \
        this->test(); \
        this->tearDownEach(); \
    } \
    virtual void test() override final; \
    static int addToTestCases() { \
        suite *testSuite = new suite(); \
        __TEST_CLASS_##suite##_##name##_ *testCase = new __TEST_CLASS_##suite##_##name##_(); \
        GlobalTestCases* testCases = GlobalTestCases::getInstance(); \
        testCases->addTestCase(""#suite"", testSuite, ""#name"", testCase); \
        return 0; \
    } \
}; \
static int __TEST_CONST_##suite##_##name##_ = __TEST_CLASS_##suite##_##name##_::addToTestCases(); \
void __TEST_CLASS_##suite##_##name##_::test()

};

#endif // UNIT_TEST_H
