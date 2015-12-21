/* Copyright 2015 ZhaoHG */
#include <string>
#include <fstream>
#include <iostream>
#include "../include/results.h"
#include "../include/unit_test.h"
#include "../include/test_case.h"
#include "../include/test_suite.h"
#include "../include/framework.h"

using std::string;
using std::ofstream;
using std::shared_ptr;

namespace ztest {

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

void Framework::runTests() {
    totalPassed = 0;
    totalCount = 0;
    resultList->clear();
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

}  // namespace ztest
