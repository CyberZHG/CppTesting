#ifndef TEST_SUITE_H_INCLUDED
#define TEST_SUITE_H_INCLUDED

#include <map>
#include <string>
#include <iostream>
#include "stream_color.h"
#include "unit_test.h"
#include "framework.h"

namespace ztest {

class UnitTest;

class TestSuite {
public:
    TestSuite() {}
    virtual ~TestSuite() {
        for (auto testCase : this->testCases) {
            delete testCase.second;
        }
    }

    void addTest(std::string testName, TestCase *testCase) {
        testCases[testName] = testCase;
    }

    int testCount() const {
        return testCases.size();
    }

    int testPassed() const {
        return testPassedNum;
    }

    virtual void runTests() = 0;

protected:
    int testPassedNum;
    std::map<std::string, TestCase*> testCases;
};

template<class UnitTestClass>
class TestSuiteSpecialize : public TestSuite {
public:
    TestSuiteSpecialize() {}

    virtual void runTests() override final {
        UnitTestClass base;
        try {
            base.setUp();
        } catch (...) {
        }
        testPassedNum = 0;
        Framework* framework = Framework::getInstance();
        for (auto testCase : testCases) {
            UnitTest* test = testCase.second->newTest();
            *dynamic_cast<UnitTestClass*>(test) = base;
            framework->resetFailedFlag();
            try {
                test->setUpEach();
                test->test();
                test->tearDownEach();
            } catch (...) {
            }
            delete test;
            if (framework->isTestFailed()) {
                std::cout << red << "[ FAILED ] " << white;
            } else {
                ++testPassedNum;
                std::cout << green << "[ PASSED ] " << white;
            }
            std::cout << testCase.first << std::endl;
        }
        try {
            base.tearDown();
        } catch (...) {
        }
    }
};

}

#endif // TEST_SUITE_H_INCLUDED
