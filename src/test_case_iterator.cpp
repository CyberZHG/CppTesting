#include "unit_test.h"
#include "test_case_iterator.h"
using namespace std;
using namespace ztest;

TestCaseIterator::TestCaseIterator(map<string, UnitTest*>* testCases) {
    this->testCases = testCases;
    this->it = this->testCases->begin();
}

bool TestCaseIterator::hasNext() {
    return it != testCases->end();
}

void TestCaseIterator::next() {
    ++it;
}

string TestCaseIterator::caseName() {
    return it->first;
}

UnitTest* TestCaseIterator::testCase() {
    return it->second;
}
