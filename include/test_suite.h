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
#ifndef INCLUDE_TEST_SUITE_H_
#define INCLUDE_TEST_SUITE_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
#include "results.h"
#include "stream_color.h"
#include "unit_test.h"
#include "framework.h"
#include "exceptions.h"

namespace test {

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
            std::streambuf* oldOutBuf = std::cout.rdbuf();
            std::streambuf* oldErrBuf = std::cerr.rdbuf();
            std::ostringstream strOut, strErr;
            std::cout.rdbuf(strOut.rdbuf());
            std::cerr.rdbuf(strErr.rdbuf());
            UnitTest* test = testCase.second->newTest();
            *dynamic_cast<UnitTestClass*>(test) = base;
            framework->resetFailedFlag();
            try {
                test->setUpEach();
                test->test();
                test->tearDownEach();
            } catch (const AssertException& e) {
            } catch (const std::exception& e) {
                framework->setFailedFlag();
                framework->appendResult(std::shared_ptr<Result>(new
                    ResultTestRuntimeError(testCase.second->file(),
                                           testCase.second->line(),
                                           e.what())));
            }
            delete test;
            std::cout.rdbuf(oldOutBuf);
            std::cerr.rdbuf(oldErrBuf);
            std::string testOut = strOut.str();
            std::string testErr = strErr.str();
            if (testOut.length() > 0) {
                if (testOut.back() == '\n') {
                    testOut.pop_back();
                }
                framework->appendResult(std::shared_ptr<Result>(new
                    ResultTestOutput("output", testOut)));
            }
            if (testErr.length() > 0) {
                if (testErr.back() == '\n') {
                    testErr.pop_back();
                }
                framework->appendResult(std::shared_ptr<Result>(new
                    ResultTestOutput("error", testErr)));
            }
            if (!framework->isTestFailed()) {
                ++testPassedNum;
            }
            if (framework->isShowPassed() || framework->isTestFailed() ||
                testOut.length() > 0 || testErr.length() > 0) {
                framework->appendResult(std::shared_ptr<Result>(new
                    ResultCaseEnd(testCase.first, !framework->isTestFailed())));
            }
        }
        try {
            base.tearDown();
        } catch (const AssertException& e) {
        } catch (...) {
        }
    }
};

}  // namespace test

#endif  // INCLUDE_TEST_SUITE_H_
