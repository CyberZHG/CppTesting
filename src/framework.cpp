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

void Framework::runTests() {
    for (auto suite : testSuites) {
        cout << suite.first << endl;
        suite.second->runTests();
    }
}
