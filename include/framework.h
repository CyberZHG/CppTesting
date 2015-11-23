#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <map>
#include <string>
#include <memory>

namespace ztest {

class TestCase;
class TestSuite;
class Result;
class ResultList;

class Framework {
public:
    static Framework* getInstance();
    virtual ~Framework();

    Framework(const Framework&) = default;
    Framework& operator=(const Framework&) = default;

    void addTestSuite(std::string suiteName, TestSuite* testSuite);
    void addTestCase(std::string suiteName, std::string caseName, TestCase* testCase);

    void runTests();
    void appendResult(std::shared_ptr<Result> result);

    void print();
    void printToHtml(std::string filePath);

    void finish();

    void setFailedFlag();
    void resetFailedFlag();
    bool isTestFailed() const;

private:
    static Framework* instance;
    Framework();
    std::map<std::string, TestSuite*> testSuites;
    ResultList* resultList;

    bool failedFlag;
};

}

#endif // FRAMEWORK_H
