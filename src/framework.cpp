#include <fstream>
#include <iostream>
#include "results.h"
#include "unit_test.h"
#include "test_case.h"
#include "test_suite.h"
#include "framework.h"
using namespace std;
using namespace ztest;

Framework* Framework::instance = nullptr;

Framework* Framework::getInstance() {
    if (instance == nullptr) {
        instance = new Framework();
    }
    return instance;
}

Framework::Framework() {
    this->resultList = new ResultList();
}

Framework::~Framework() {
    delete this->resultList;
}

void Framework::addTestSuite(string suiteName, TestSuite* testSuite) {
    if (testSuites.find(suiteName) == testSuites.end()) {
        this->testSuites[suiteName] = testSuite;
    } else {
        delete testSuite;
    }
}

void Framework::addTestCase(string suiteName, string caseName, TestCase* testCase) {
    testSuites[suiteName]->addTest(caseName, testCase);
}

void Framework::runTests() {
    int totalPassed = 0;
    int totalCount = 0;
    resultList->clear();
    for (auto suite : testSuites) {
        this->appendResult(shared_ptr<Result>(new ResultSuiteBegin(suite.first)));
        suite.second->runTests();
        int passedNum = suite.second->testPassed();
        int testCount = suite.second->testCount();
        totalPassed += passedNum;
        totalCount += testCount;
        this->appendResult(shared_ptr<Result>(new ResultPercentage(passedNum, testCount)));
        this->appendResult(shared_ptr<Result>(new ResultSuiteEnd()));
    }
    this->appendResult(shared_ptr<Result>(new ResultPercentage(totalPassed, totalCount)));
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
    resultList->printToHtml(out);
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
