#ifndef TEST_SUITE_ITERATOR_H
#define TEST_SUITE_ITERATOR_H

#include <map>
#include <string>

namespace ztest {

class UnitTest;
class TestCaseIterator;

class TestSuiteIterator {
public:
    TestSuiteIterator();
    bool hasNext();
    void next();
    std::string suiteName();
    UnitTest* testSuite();
    TestCaseIterator testCaseIterator();
private:
    std::map<std::string, UnitTest*>* testSuites;
    std::map<std::string, std::map<std::string, UnitTest*>*>* testCases;
    std::map<std::string, UnitTest*>::iterator it;
};

}

#endif // TEST_SUITE_ITERATOR_H
