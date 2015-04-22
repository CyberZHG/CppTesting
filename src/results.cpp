#include "stream_color.h"
#include "results.h"
using namespace std;
using namespace ztest;

Result::Result() {}

Result::~Result() {}

ResultList::ResultList() : results() {}

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
    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "  <head>" << endl;
    out << "    <title>Results</title>" << endl;
    out << "    <style>" << endl;
    out << "html {font-family: 'Consolas';} " << endl;
    out << ".suite_title {text-align: center; color: rgb(163, 73, 164); font-weight: bold;} " << endl;
    out << ".case_title {text-align: center;} " << endl;
    out << ".passed {text-align: center; color: rgb(34, 177, 76); font-weight: bold;} " << endl;
    out << ".failed {text-align: center; color: rgb(237, 28, 36); font-weight: bold;} " << endl;
    out << ".text_expect {text-align: right; padding-right: 10px;} " << endl;
    out << ".text_actual {text-align: right; padding-right: 10px;} " << endl;
    out << ".parameter_name {text-align: right; padding-right: 10px;} " << endl;
    out << ".percentage_text {text-align: center;} " << endl;
    out << "    </style>" << endl;
    out << "  </head>" << endl;
    out << "  <body>" << endl;
    out << "    <table class='results'>" << endl;
    for (auto result : results) {
        result->printToHtml(out);
    }
    out << "    </table>" << endl;
    out << "  </body>" << endl;
    out << "</html>" << endl;
}

ResultSuiteBegin::ResultSuiteBegin(string _title) :
    title(_title) {
}

ResultSuiteBegin::~ResultSuiteBegin() {
}

void ResultSuiteBegin::print() const {
    cout << yellow << "[========] " << title << white << endl;
}

void ResultSuiteBegin::printToHtml(ofstream& out) const {
    out << "      <tr class='suite_title'>" << endl;
    out << "        <td>[====================]</td>" << endl;
    out << "        <td>" << title << "</td>" << endl;
    out << "      </tr>" << endl;
}

ResultSuiteEnd::ResultSuiteEnd() {
}

ResultSuiteEnd::~ResultSuiteEnd() {
}

void ResultSuiteEnd::print() const {
    cout << endl;
}

void ResultSuiteEnd::printToHtml(std::ofstream& out) const {
    out << "      <tr><td>&nbsp;</td></tr>" << endl;
}

ResultTestFailed::ResultTestFailed(string _file, int _line, string _expression,
                                   string _expect, string _actual) :
    file(_file), line(_line), expression(_expression),
    expect(_expect), actual(_actual) {
}

ResultTestFailed::~ResultTestFailed() {
}

void ResultTestFailed::print() const {
    cout << file << "(" << line << "): " << expression << endl;
    cout << "    Expect: " << expect << endl;
    cout << "    Actual: " << actual << endl;
}

void ResultTestFailed::printToHtml(ofstream& out) const {
    out << "      <tr class='code_line'>" << endl;
    out << "        <td colspan='2'><a href='" << file << "'>" << file << "</a>";
    out << "(" << line << "): " << expression << "</td>" << endl;
    out << "      </tr>" << endl;
    out << "      <tr>" << endl;
    out << "        <td class='text_expect'>Expect: </td>" << endl;
    out << "        <td>" << expect << "</td>" << endl;
    out << "      </tr>" << endl;
    out << "      <tr>" << endl;
    out << "        <td class='text_actual'>Actual: </td>" << endl;
    out << "        <td>" << actual << "</td>" << endl;
    out << "      </tr>" << endl;
}

ResultTestFailedVariables::ResultTestFailedVariables(string _file, int _line,
                                                     string _expression) :
    file(_file), line(_line), expression(_expression),
    names(), values() {
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
    out << "      <tr class='code_line'>" << endl;
    out << "        <td colspan='2'><a href='" << file << "'>" << file << "</a>";
    out << "(" << line << "): " << expression << "</td>" << endl;
    out << "      </tr>" << endl;
    for (size_t i = 0; i < names.size(); ++i) {
        out << "      <tr class='parameters'>" << endl;
        out << "        <td class='parameter_name'>" << names[i] << " => </td>" << endl;
        out << "        <td class='parameter_value'>" << values[i] << "</td>" << endl;
        out << "      </tr>" << endl;
    }
}

ResultCaseBegin::ResultCaseBegin() {
}

ResultCaseBegin::~ResultCaseBegin() {
}

void ResultCaseBegin::print() const {
}

void ResultCaseBegin::printToHtml(std::ofstream&) const {
}

ResultCaseEnd::ResultCaseEnd(string _caseName, bool _passed) :
    caseName(_caseName), passed(_passed) {
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
    if (this->passed) {
        out << "      <tr>" << endl;
        out << "        <td class='passed'>" << "[------ PASSED ------]" << "</td>" << endl;
    } else {
        out << "      <tr>" << endl;
        out << "        <td class='failed'>" << "[------ FAILED ------]" << "</td>" << endl;
    }
    out << "        <td class='case_title'>" << this->caseName << "</td>" << endl;
    out << "      </tr>" << endl;
}

ResultPercentage::ResultPercentage(int _passed, int _total) :
    passed(_passed), total(_total) {
}

ResultPercentage::~ResultPercentage() {
}

void ResultPercentage::print() const {
    if (passed == total) {
        cout << green << "[= 100% =] " << white << "Passed all " << total << " test cases." << endl;
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
    if (passed == total) {
        out << "      <tr>" << endl;
        out << "        <td class='passed'>" << "[======= 100% =======]" << "</td>" << endl;
        out << "        <td class='percentage_text'>" << "Passed all " << total << " test cases." << "</td>" << endl;
        out << "      </tr>" << endl;
    } else {
        out << "      <tr>" << endl;
        out << "        <td class='failed'>[======= ";
        int percentage = passed * 100 / total;
        if (percentage >= 10) {
            out << "&nbsp;";
        } else {
            out << "&nbsp;&nbsp;";
        }
        out << percentage << "% =======] " << "</td>" << endl;
        out << "        <td class='percentage_text'>";
        out << passed << "/" << total << " test cases passed. </td>" << endl;
        out << "      </tr>" << endl;
    }
}
