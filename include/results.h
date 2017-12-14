#ifndef INCLUDE_RESULTS_H_
#define INCLUDE_RESULTS_H_

#include <vector>
#include <string>
#include <fstream>
#include <memory>

namespace ztest {

class Result {
 public:
    Result();
    virtual ~Result();
    virtual void print() const = 0;
    virtual void printToHtml(std::ofstream* out) const = 0;
};

class ResultList {
 public:
    ResultList();
    virtual ~ResultList();

    void append(std::shared_ptr<Result> result);
    void clear();

    void print() const;
    void printToHtml(std::ofstream* out) const;

 private:
    std::vector<std::shared_ptr<Result>> results;
};

class ResultSuiteBegin : public Result {
 public:
    explicit ResultSuiteBegin(std::string title);
    virtual ~ResultSuiteBegin();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;

 private:
    std::string title;
};

class ResultSuiteEnd : public Result {
 public:
    ResultSuiteEnd();
    virtual ~ResultSuiteEnd();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;
};

class ResultTestFailed : public Result {
 public:
    ResultTestFailed(std::string file, int line,
                     std::string expression,
                     std::string expect, std::string actual);
    virtual ~ResultTestFailed();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;

 private:
    std::string file;
    int line;
    std::string expression;
    std::string expect;
    std::string actual;
};

class ResultTestFailedVariables : public Result {
 public:
    ResultTestFailedVariables(std::string file, int line,
                              std::string expression);
    virtual ~ResultTestFailedVariables();
    void addParameter(std::string name, std::string value);

    void print() const final;
    void printToHtml(std::ofstream* out) const final;

 private:
    std::string file;
    int line;
    std::string expression;
    std::vector<std::string> names;
    std::vector<std::string> values;
};

class ResultCaseBegin : public Result {
 public:
    ResultCaseBegin();
    virtual ~ResultCaseBegin();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;
};

class ResultCaseEnd : public Result {
 public:
    ResultCaseEnd(std::string caseName, bool passed);
    virtual ~ResultCaseEnd();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;

 private:
    std::string caseName;
    bool passed;
};

class ResultPercentage : public Result {
 public:
    ResultPercentage(int passed, int total);
    virtual ~ResultPercentage();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;

 private:
    int passed;
    int total;
};

}  // namespace ztest

#endif  // INCLUDE_RESULTS_H_
