/* Copyright 2015 ZhaoHG */
#ifndef INCLUDE_TEST_SUITE_H_
#define INCLUDE_TEST_SUITE_H_

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include "./results.h"
#include "./stream_color.h"
#include "./unit_test.h"
#include "./framework.h"
#include "./exceptions.h"

namespace ztest {

class UnitTest;

class TestSuite {
 public:
    TestSuite() :
        testPassedNum(0), testCases() {
    }

    virtual ~TestSuite() {
        for (auto& item : this->testCases) {
            delete item.second;
        }
    }

    void addTest(std::string testName, TestCase *testCase) {
        testCases.push_back({testName, testCase});
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
    std::vector<std::pair<std::string, TestCase*>> testCases;
};

template<class UnitTestClass>
class TestSuiteSpecialize : public TestSuite {
 public:
    TestSuiteSpecialize() {}

    void runTests() final {
        UnitTestClass base;
        try {
            base.setUp();
        } catch (AssertException e) {
        } catch (...) {
        }
        testPassedNum = 0;
        Framework* framework = Framework::getInstance();
        for (auto testCase : testCases) {
            framework->appendResult(std::shared_ptr<Result>
                                    (new ResultCaseBegin()));
            UnitTest* test = testCase.second->newTest();
            *dynamic_cast<UnitTestClass*>(test) = base;
            framework->resetFailedFlag();
            try {
                test->setUpEach();
                test->test();
                test->tearDownEach();
            } catch (AssertException e) {
            } catch (...) {
                framework->setFailedFlag();
            }
            delete test;
            if (!framework->isTestFailed()) {
                ++testPassedNum;
            }
            framework->appendResult(std::shared_ptr<Result>(new
                ResultCaseEnd(testCase.first, !framework->isTestFailed())));
        }
        try {
            base.tearDown();
        } catch (AssertException e) {
        } catch (...) {
        }
    }
};

}  // namespace ztest

#endif  // INCLUDE_TEST_SUITE_H_
