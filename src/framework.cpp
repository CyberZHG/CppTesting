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
#include <string>
#include <fstream>
#include <iostream>
#include <csignal>
#include "results.h"
#include "unit_test.h"
#include "test_case.h"
#include "test_suite.h"
#include "framework.h"

using std::string;
using std::ofstream;
using std::shared_ptr;

namespace test {

Framework* Framework::instance = nullptr;

Framework* Framework::getInstance() {
    if (instance == nullptr) {
        instance = new Framework();
    }
    return instance;
}

Framework::Framework() :
    testSuites(),
    testIndex(),
    resultList(new ResultList()),
    failedFlag(false),
    showPassed(true),
    totalPassed(0),
    totalCount(0) {
}

Framework::~Framework() {
    for (auto& item : testSuites) {
        delete item.second;
    }
    delete this->resultList;
}

void Framework::addTestSuite(string suiteName, TestSuite* testSuite) {
    if (testIndex.find(suiteName) == testIndex.end()) {
        testIndex[suiteName] =  static_cast<int>(testSuites.size());
        testSuites.push_back({suiteName, testSuite});
    } else {
        delete testSuite;
    }
}

void Framework::addTestCase(string suiteName, string caseName,
                            TestCase* testCase) {
    testSuites[testIndex[suiteName]].second->addTest(caseName, testCase);
}

void sig_action_handler(int signal) {
    throw std::runtime_error(std::string("Segment fault detected, ") +
                             "the test results may be unstable: " +
                             std::to_string(signal));
}

void Framework::runTests() {
    totalPassed = 0;
    totalCount = 0;
    resultList->clear();
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sig_action_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
    for (auto suite : testSuites) {
        this->appendResult(shared_ptr<Result>(
                                new ResultSuiteBegin(suite.first)));
        suite.second->runTests();
        int passedNum = suite.second->testPassed();
        int testCount = suite.second->testCount();
        totalPassed += passedNum;
        totalCount += testCount;
        this->appendResult(shared_ptr<Result>(
                                new ResultPercentage(passedNum, testCount)));
        this->appendResult(shared_ptr<Result>(new ResultSuiteEnd()));
    }
    this->appendResult(shared_ptr<Result>(
                            new ResultPercentage(totalPassed, totalCount)));
}

void Framework::appendResult(shared_ptr<Result> result) {
    this->resultList->append(result);
}

void Framework::print() {
    resultList->print();
}

void Framework::printToHtml(string filePath) {
    ofstream out;
    out.open(filePath.c_str());
    resultList->printToHtml(&out);
    out.close();
}

void Framework::finish() {
    delete instance;
    instance = nullptr;
}

void Framework::setFailedFlag() {
    this->failedFlag = true;
}

void Framework::resetFailedFlag() {
    this->failedFlag = false;
}

bool Framework::isTestFailed() const {
    return this->failedFlag;
}

int Framework::getTotalPassed() const {
    return this->totalPassed;
}

int Framework::getTotalCount() const {
    return this->totalCount;
}

bool Framework::isAllPassed() const {
    return this->totalPassed == this->totalCount;
}

void Framework::hidePassed() {
    this->showPassed = false;
}

bool Framework::isShowPassed() const {
    return this->showPassed;
}

}  // namespace test
