#ifndef TEST_CASES_H
#define TEST_CASES_H

#include <map>
#include <string>

namespace ztest {

class UnitTest;

class GlobalTestCases {
public:
    static GlobalTestCases* getInstance();
    void addTestCase(std::string testSuiteName, UnitTest* testSuite,
                     std::string testCaseName, UnitTest* testCase);
    std::map<std::string, UnitTest*>* testSuites();
    std::map<std::string, std::map<std::string, UnitTest*>*>* testCases();
private:
    GlobalTestCases();
    virtual ~GlobalTestCases();
    static GlobalTestCases* instance;

    std::map<std::string, UnitTest*>* globalTestSuites;
    std::map<std::string, std::map<std::string, UnitTest*>*>* globalTestCases;
};

};

#endif // UNIT_TEST_LIST_H
