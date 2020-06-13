/* Copyright 2020 Zhao HG

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
#ifndef INCLUDE_RESULTS_H_
#define INCLUDE_RESULTS_H_

#include <vector>
#include <string>
#include <fstream>
#include <memory>

namespace test {

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
    explicit ResultSuiteBegin(const std::string& title);
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

class ResultTestRuntimeError : public Result {
 public:
    ResultTestRuntimeError(const std::string& file, int line,
                           const std::string& what);
    virtual ~ResultTestRuntimeError();

    void print() const final;
    void printToHtml(std::ofstream* out) const final;

 private:
    std::string file;
    int line;
    std::string what;
};

class ResultTestFailed : public Result {
 public:
    ResultTestFailed(const std::string& file, int line,
                     const std::string& expression,
                     const std::string& expect, const std::string& actual);
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
    ResultTestFailedVariables(const std::string& file, int line,
                              const std::string& expression);
    virtual ~ResultTestFailedVariables();
    void addParameter(const std::string& name, const std::string& value);

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
    ResultCaseEnd(const std::string& caseName, bool passed);
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

}  // namespace test

#endif  // INCLUDE_RESULTS_H_
