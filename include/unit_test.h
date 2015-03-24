#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <map>
#include <string>
#include "framework.h"

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
    virtual void test() override final; \
    static int addToTestCases() { \
        TestCaseSpecialize< __TEST_CLASS_##suite##_##name##_ >* testCase; \
        testCase = new TestCaseSpecialize< __TEST_CLASS_##suite##_##name##_ >(); \
        TestSuiteSpecialize< suite >* testSuite;\
        testSuite = new TestSuiteSpecialize< suite >(); \
        Framework::getInstance()->addTestSuite(""#suite"", testSuite); \
        Framework::getInstance()->addTestCase(""#suite"", ""#name"", testCase); \
        return 0; \
    } \
}; \
static int __TEST_CONST_##suite##_##name##_ = __TEST_CLASS_##suite##_##name##_::addToTestCases(); \
void __TEST_CLASS_##suite##_##name##_::test()

};

#endif // UNIT_TEST_H
