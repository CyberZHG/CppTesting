/* Copyright 2020 Zhao HG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */
#ifndef INCLUDE_UNIT_TEST_H_
#define INCLUDE_UNIT_TEST_H_

#include <map>
#include <string>
#include "framework.h"

namespace test {

/**
 * Unit test base class.
 */
class UnitTest {
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
    void test() final; \
    static int addToTestCases() { \
        TestCaseSpecialize< __TEST_CLASS_##suite##_##name##_ >* \
                                                                testCase; \
        testCase = new \
                TestCaseSpecialize< __TEST_CLASS_##suite##_##name##_ >(__FILE__, __LINE__); \
        TestSuiteSpecialize< suite >* testSuite;\
        testSuite = new TestSuiteSpecialize< suite >(); \
        Framework::getInstance()->addTestSuite(""#suite"", testSuite); \
        Framework::getInstance()->addTestCase(""#suite"", ""#name"", \
                                              testCase); \
        return 0; \
    } \
}; \
static int __TEST_CONST_##suite##_##name##_ = \
                        __TEST_CLASS_##suite##_##name##_::addToTestCases(); \
void __TEST_CLASS_##suite##_##name##_::test()

}  // namespace test

#endif  // INCLUDE_UNIT_TEST_H_
