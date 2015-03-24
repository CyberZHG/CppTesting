#ifndef TEST_CASE_ITERATOR_H
#define TEST_CASE_ITERATOR_H

#include <map>
#include <string>

namespace ztest {

class UnitTest;

class TestCaseIterator {
public:
    TestCaseIterator(std::map<std::string, UnitTest*>* testCases);
    bool hasNext();
    void next();
    std::string caseName();
    UnitTest* testCase();
private:
    std::map<std::string, UnitTest*>* testCases;
    std::map<std::string, UnitTest*>::iterator it;
};

}

#endif // TEST_CASE_ITERATOR_H
