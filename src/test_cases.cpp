#include "unit_test.h"
#include "test_cases.h"
using namespace std;
using namespace ztest;

GlobalTestCases::GlobalTestCases() {
    this->globalTestSuites = new map<string, UnitTest*>();
    this->globalTestCases = new map<string, map<string, UnitTest*>*>();
}

GlobalTestCases::~GlobalTestCases() {
    for (auto suite : *this->globalTestSuites) {
        delete suite.second;
    }
    delete this->globalTestSuites;
    for (auto suite : *this->globalTestCases) {
        auto testCases = this->globalTestCases->find(suite.first)->second;
        for (auto testCase : *testCases) {
            delete testCase.second;
        }
        delete testCases;
    }
    delete this->globalTestCases;
}

GlobalTestCases* GlobalTestCases::instance = nullptr;

GlobalTestCases* GlobalTestCases::getInstance() {
    if (instance == nullptr) {
        instance = new GlobalTestCases();
    }
    return instance;
}

void GlobalTestCases::addTestCase(string testSuiteName, UnitTest* testSuite,
                                  string testCaseName, UnitTest* testCase) {
    if (globalTestSuites->find(testSuiteName) == globalTestSuites->end()) {
        (*globalTestSuites)[testSuiteName] = testSuite;
        (*globalTestCases)[testSuiteName] = new map<string, UnitTest*>();
    } else {
        delete testSuite;
    }
    (*((*globalTestCases)[testSuiteName]))[testCaseName] = testCase;
}

map<string, UnitTest*>* GlobalTestCases::testSuites() {
    return globalTestSuites;
}

map<string, map<string, UnitTest*>*>* GlobalTestCases::testCases() {
    return globalTestCases;
}
