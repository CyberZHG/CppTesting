/* Copyright 2019 Zhao HG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */
#ifndef INCLUDE_FRAMEWORK_H_
#define INCLUDE_FRAMEWORK_H_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <utility>

namespace test {

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

}  // namespace test

#endif  // INCLUDE_FRAMEWORK_H_
