#ifndef INCLUDE_FRAMEWORK_H_
#define INCLUDE_FRAMEWORK_H_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <utility>

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
    void addTestCase(std::string suiteName, std::string caseName,
                     TestCase* testCase);

    void runTests();
    void appendResult(std::shared_ptr<Result> result);

    void print();
    void printToHtml(std::string filePath);

    void finish();

    void setFailedFlag();
    void resetFailedFlag();
    bool isTestFailed() const;

    int getTotalPassed() const;
    int getTotalCount() const;
    bool isAllPassed() const;

 private:
    static Framework* instance;
    Framework();
    std::vector<std::pair<std::string, TestSuite*>> testSuites;
    std::map<std::string, int> testIndex;
    ResultList* resultList;

    bool failedFlag;
    int totalPassed;
    int totalCount;
};

}  // namespace ztest

#endif  // INCLUDE_FRAMEWORK_H_
