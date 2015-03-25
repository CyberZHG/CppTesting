#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <map>
#include <string>

namespace ztest {

class TestCase;
class TestSuite;

class Framework
{
public:
    static Framework* getInstance();
    virtual ~Framework();

    void addTestSuite(std::string suiteName, TestSuite* testSuite);
    void addTestCase(std::string suiteName, std::string caseName, TestCase* testCase);

    void runTests();

    void setFailedFlag();
    void resetFailedFlag();
    bool isTestFailed() const;

private:
    static Framework* instance;
    Framework();
    std::map<std::string, TestSuite*> testSuites;

    bool failedFlag;
};

}

#endif // FRAMEWORK_H
