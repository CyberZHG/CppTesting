#include <iostream>
#include "unit_test.h"
#include "test_cases.h"
#include "test_suite_iterator.h"
#include "test_case_iterator.h"
#include "framework.h"
using namespace std;
using namespace ztest;

Framework::Framework() {}

Framework::~Framework() {}

void Framework::runTests() {
    for (TestSuiteIterator suiteIt; suiteIt.hasNext(); suiteIt.next()) {
        cout << suiteIt.suiteName() << endl;
        UnitTest* testSuite = suiteIt.testSuite();
        testSuite->setUp();
        for (TestCaseIterator caseIt = suiteIt.testCaseIterator(); caseIt.hasNext(); caseIt.next()) {
            cout << "    " << caseIt.caseName() << endl;
            UnitTest* testCase = caseIt.testCase();
            *testCase = *testSuite;
            testCase->setUpEach();
            testCase->test();
            testCase->tearDownEach();
        }
        testSuite->tearDown();
    }
}
