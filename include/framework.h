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

private:
    static Framework* instance;
    Framework();
    std::map<std::string, TestSuite*> testSuites;
};

}

#endif // FRAMEWORK_H
