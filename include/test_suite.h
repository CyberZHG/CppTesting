#ifndef TEST_SUITE_H_INCLUDED
#define TEST_SUITE_H_INCLUDED

#include <map>
#include <string>
#include <iostream>
#include "test_case.h"
#include "unit_test.h"

namespace ztest {

class UnitTest;

class TestSuite {
public:
    TestSuite() {}
    virtual ~TestSuite() {}

    void addTest(std::string testName, TestCase *testCase) {
        testCases[testName] = testCase;
    }

    virtual void runTests() = 0;

protected:
    std::map<std::string, TestCase*> testCases;
};

template<class UnitTestClass>
class TestSuiteSpecialize : public TestSuite {
public:
    TestSuiteSpecialize() {}

    virtual ~TestSuiteSpecialize() {
        for (auto testCase : this->testCases) {
            delete testCase.second;
        }
    }

    virtual void runTests() override final {
        UnitTestClass base;
        try {
            base.setUp();
        } catch (...) {
        }
        for (auto testCase : testCases) {
            std::cout << "    " << testCase.first << std::endl;
            UnitTest* test = testCase.second->newTest();
            *(UnitTestClass*)test = base;
            try {
                test->setUpEach();
                test->test();
                test->tearDownEach();
            } catch (...) {
            }
        }
        try {
            base.tearDown();
        } catch (...) {
        }
    }
};

}

#endif // TEST_SUITE_H_INCLUDED
