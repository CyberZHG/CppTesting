#include "stream_color.h"
#include "results.h"
using namespace std;
using namespace ztest;

Result::Result() {}

Result::~Result() {}

ResultList::ResultList() {}

ResultList::~ResultList() {}

void ResultList::append(shared_ptr<Result> result) {
    this->results.push_back(result);
}

void ResultList::clear() {
    this->results.clear();
}

void ResultList::print() const {
    for (auto result : results) {
        result->print();
    }
}

void ResultList::printToHtml(ofstream& out) const {
    for (auto result : results) {
        result->printToHtml(out);
    }
}

ResultSuiteBegin::ResultSuiteBegin(string title) {
    this->title = title;
}

ResultSuiteBegin::~ResultSuiteBegin() {
}

void ResultSuiteBegin::print() const {
    cout << yellow << "[========] " << title << white << endl;
}

void ResultSuiteBegin::printToHtml(ofstream& out) const {
}

ResultSuiteEnd::ResultSuiteEnd() {
}

ResultSuiteEnd::~ResultSuiteEnd() {
}

void ResultSuiteEnd::print() const {
    cout << endl;
}

void ResultSuiteEnd::printToHtml(std::ofstream& out) const {
}

ResultTestFailed::ResultTestFailed(string file, int line, string expression, string expect, string actual) {
    this->file = file;
    this->line = line;
    this->expression = expression;
    this->expect = expect;
    this->actual = actual;
}

ResultTestFailed::~ResultTestFailed() {
}

void ResultTestFailed::print() const {
    cout << file << "(" << line << "): " << expression << endl;
    cout << "    Expect: " << expect << endl;
    cout << "    Actual: " << actual << endl;
}

void ResultTestFailed::printToHtml(ofstream& out) const {
}

ResultTestFailedVariables::ResultTestFailedVariables(string file, int line, string expression) {
    this->file = file;
    this->line = line;
    this->expression = expression;
}

ResultTestFailedVariables::~ResultTestFailedVariables() {
}

void ResultTestFailedVariables::addParameter(string name, string value) {
    this->names.push_back(name);
    this->values.push_back(value);
}

void ResultTestFailedVariables::print() const {
    cout << file << "(" << line << "): "  << expression << endl;
    for (size_t i = 0; i < names.size(); ++i) {
        cout << "    " << names[i] << " => " << values[i] << endl;
    }
}

void ResultTestFailedVariables::printToHtml(ofstream& out) const {
}

ResultCaseBegin::ResultCaseBegin() {
}

ResultCaseBegin::~ResultCaseBegin() {
}

void ResultCaseBegin::print() const {
}

void ResultCaseBegin::printToHtml(std::ofstream& out) const {
}

ResultCaseEnd::ResultCaseEnd(string caseName, bool passed) {
    this->caseName = caseName;
    this->passed = passed;
}

ResultCaseEnd::~ResultCaseEnd() {
}

void ResultCaseEnd::print() const {
    if (this->passed) {
        cout << green << "[ PASSED ] ";
    } else {
        cout << red << "[ FAILED ] ";
    }
    cout << white << this->caseName << endl;
}

void ResultCaseEnd::printToHtml(ofstream& out) const {
}

ResultPercentage::ResultPercentage(int passed, int total) {
    this->passed = passed;
    this->total = total;
}

ResultPercentage::~ResultPercentage() {
}

void ResultPercentage::print() const {
    if (passed == total) {
        cout << green << "[= 100% =] " << white << "Passed all test cases." << endl;
    } else {
        cout << red << "[= ";
        int percentage = passed * 100 / total;
        if (percentage >= 10) {
            cout << " ";
        } else {
            cout << "  ";
        }
        cout << percentage << "% =] " << white;
        cout << passed << " / " << total << " test cases passed. " << endl;
    }
}

void ResultPercentage::printToHtml(ofstream& out) const {
}
