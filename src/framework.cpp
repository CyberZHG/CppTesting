#include <iostream>
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
}

Framework::~Framework() {
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

void printPercentage(int passed, int total) {
    if (passed == total) {
        cout << green << "[= 100% =] " << white << "Passed all test cases." << endl;
    } else {
        cout << red << "[= ";
        int percentage = passed * 100 / total;
        if (percentage >= 10) {
            cout << " ";
        } else {
            cout << "  ";
        }
        cout << percentage << "% =] " << white;
        cout << passed << " / " << total << " test cases passed. " << endl;
    }
}

void Framework::runTests() {
    int totalPassed = 0;
    int totalCount = 0;
    for (auto suite : testSuites) {
        cout << yellow << "[========] " << suite.first << white << endl;
        suite.second->runTests();
        int passedNum = suite.second->testPassed();
        int testCount = suite.second->testCount();
        totalPassed += passedNum;
        totalCount += testCount;
        printPercentage(passedNum, testCount);
        cout << endl;
    }
    printPercentage(totalPassed, totalCount);
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
