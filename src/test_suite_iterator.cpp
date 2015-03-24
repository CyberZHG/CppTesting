#include "unit_test.h"
#include "test_cases.h"
#include "test_case_iterator.h"
#include "test_suite_iterator.h"
using namespace std;
using namespace ztest;

TestSuiteIterator::TestSuiteIterator() {
    GlobalTestCases* global = GlobalTestCases::getInstance();
    this->testSuites = global->testSuites();
    this->testCases = global->testCases();
    it = this->testSuites->begin();
}

bool TestSuiteIterator::hasNext() {
    return it != this->testSuites->end();
}

void TestSuiteIterator::next() {
    ++it;
}

std::string TestSuiteIterator::suiteName() {
    return it->first;
}

UnitTest* TestSuiteIterator::testSuite() {
    return it->second;
}

TestCaseIterator TestSuiteIterator::testCaseIterator() {
    return TestCaseIterator((*this->testCases)[it->first]);
}
