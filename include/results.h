#ifndef RESULTS_H_INCLUDED
#define RESULTS_H_INCLUDED

#include <vector>
#include <fstream>
#include <memory>

namespace ztest {

class Result {
public:
    Result();
    ~Result();
    virtual void print() const = 0;
    virtual void printToHtml(std::ofstream& out) const = 0;
};

class ResultList {
public:
    ResultList();
    virtual ~ResultList();
    void append(std::shared_ptr<Result> result);
    void print() const;
    void printToHtml(std::ofstream& out) const;

private:
    std::vector<std::shared_ptr<Result>> results;
};

class ResultSuiteTitle : public Result {
public:
    ResultSuiteTitle(std::string title);
    virtual ~ResultSuiteTitle();

    virtual void print() const override final;
    virtual void printToHtml(std::ofstream& out) const override final;

private:
    std::string title;
};

class ResultTestFailed : public Result {
public:
    ResultTestFailed(std::string file, int line, std::string expression, std::string expect, std::string actual);
    virtual ~ResultTestFailed();

    virtual void print() const override final;
    virtual void printToHtml(std::ofstream& out) const override final;

private:
    std::string file;
    int line;
    std::string expression;
    std::string expect;
    std::string actual;
};

class ResultTestFailedVariables : public Result {
public:
    ResultTestFailedVariables(std::string file, int line, std::string expression);
    virtual ~ResultTestFailedVariables();
    void addParameter(std::string name, std::string value);

    virtual void print() const override final;
    virtual void printToHtml(std::ofstream& out) const override final;

private:
    std::string file;
    int line;
    std::string expression;
    std::vector<std::string> names;
    std::vector<std::string> values;
};

class ResultCaseTitle : public Result {
public:
    ResultCaseTitle(std::string caseName, bool passed);
    virtual ~ResultCaseTitle();

    virtual void print() const override final;
    virtual void printToHtml(std::ofstream& out) const override final;

private:
    std::string caseName;
    bool passed;
};

class ResultPercentage : public Result {
public:
    ResultPercentage(int passed, int total);
    virtual ~ResultPercentage();

    virtual void print() const override final;
    virtual void printToHtml(std::ofstream& out) const override final;

private:
    int passed;
    int total;
};

}

#endif // RESULTS_H_INCLUDED
