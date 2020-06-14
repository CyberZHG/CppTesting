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
#include <cstdio>
#include <string>
#include "stream_color.h"
#include "results.h"

namespace test {

using std::shared_ptr;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;

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

void ResultList::printToHtml(ofstream* out) const {
    (*out) << "<!DOCTYPE html>" << endl;
    (*out) << "<html>" << endl;
    (*out) << "  <head>" << endl;
    (*out) << "    <title>Results</title>" << endl;
    (*out) << "    <style>" << endl;
    (*out) << "html {" << endl;
    (*out) << "    font-family: 'Consolas';" << endl;
    (*out) << "} " << endl;
    (*out) << ".suite_title {" << endl;
    (*out) << "    text-align: center;" << endl;
    (*out) << "    color: rgb(163, 73, 164);" << endl;
    (*out) << "    font-weight: bold;" << endl;
    (*out) << "}" << endl;
    (*out) << ".case_title {" << endl;
    (*out) << "    text-align: center;" << endl;
    (*out) << "}" << endl;
    (*out) << ".passed {" << endl;
    (*out) << "    text-align: center; " << endl;
    (*out) << "    color: rgb(34, 177, 76); " << endl;
    (*out) << "    font-weight: bold;" << endl;
    (*out) << "}" << endl;
    (*out) << ".failed {" << endl;
    (*out) << "    text-align: center; " << endl;
    (*out) << "    color: rgb(237, 28, 36); " << endl;
    (*out) << "    font-weight: bold;" << endl;
    (*out) << "}" << endl;
    (*out) << ".text_expect {" << endl;
    (*out) << "    text-align: right;" << endl;
    (*out) << "    padding-right: 10px;" << endl;
    (*out) << "}" << endl;
    (*out) << ".text_actual {" << endl;
    (*out) << "    text-align: right;" << endl;
    (*out) << "    padding-right: 10px;" << endl;
    (*out) << "} " << endl;
    (*out) << ".parameter_name {" << endl;
    (*out) << "    text-align: right;" << endl;
    (*out) << "    padding-right: 10px;" << endl;
    (*out) << "}" << endl;
    (*out) << ".percentage_text {" << endl;
    (*out) << "    text-align: center;" << endl;
    (*out) << "} " << endl;
    (*out) << "    </style>" << endl;
    (*out) << "  </head>" << endl;
    (*out) << "  <body>" << endl;
    (*out) << "    <table class='results'>" << endl;
    for (auto result : results) {
        result->printToHtml(out);
    }
    (*out) << "    </table>" << endl;
    (*out) << "  </body>" << endl;
    (*out) << "</html>" << endl;
}

ResultSuiteBegin::ResultSuiteBegin(const std::string& _title) :
    title(_title) {
}

ResultSuiteBegin::~ResultSuiteBegin() {
}

void ResultSuiteBegin::print() const {
    color(&cout, TextColor::YELLOW, "[========] " + title);
    cout << endl;
}

void ResultSuiteBegin::printToHtml(ofstream* out) const {
    (*out) << "      <tr class='suite_title'>" << endl;
    (*out) << "        <td>[====================]</td>" << endl;
    (*out) << "        <td>" << title << "</td>" << endl;
    (*out) << "      </tr>" << endl;
}

ResultSuiteEnd::ResultSuiteEnd() {
}

ResultSuiteEnd::~ResultSuiteEnd() {
}

void ResultSuiteEnd::print() const {
    cout << endl;
}

void ResultSuiteEnd::printToHtml(std::ofstream* out) const {
    (*out) << "      <tr><td>&nbsp;</td></tr>" << endl;
}

ResultTestRuntimeError::ResultTestRuntimeError(const std::string& _file,
                                               int _line,
                                               const std::string& _what) :
    file(_file), line(_line), what(_what) {}

ResultTestRuntimeError::~ResultTestRuntimeError() {}

void ResultTestRuntimeError::print() const {
    cout << file << "(" << line << "):" << endl;
    cout << "    Exception: " << what << endl;
}

void ResultTestRuntimeError::printToHtml(std::ofstream* out) const {
    (*out) << "      <tr class='code_line'>" << endl;
    (*out) << "        <td colspan='2'>" << endl;
    (*out) << "          <a href='" << file << "'>" << file << "</a>";
    (*out) << "(" << line << "): " << "</td>" << endl;
    (*out) << "      </tr>" << endl;
    (*out) << "      <tr>" << endl;
    (*out) << "        <td>" << "Exception: " << what << "</td>" << endl;
    (*out) << "      </tr>" << endl;
}

ResultTestFailed::ResultTestFailed(const std::string& _file, int _line,
                                   const std::string& _expression,
                                   const std::string& _expect,
                                   const std::string& _actual) :
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

void ResultTestFailed::printToHtml(ofstream* out) const {
    (*out) << "      <tr class='code_line'>" << endl;
    (*out) << "        <td colspan='2'>" << endl;
    (*out) << "          <a href='" << file << "'>" << file << "</a>";
    (*out) << "(" << line << "):" << expression << "</td>" << endl;
    (*out) << "      </tr>" << endl;
    (*out) << "      <tr>" << endl;
    (*out) << "        <td class='text_expect'>Expect: </td>" << endl;
    (*out) << "        <td>" << expect << "</td>" << endl;
    (*out) << "      </tr>" << endl;
    (*out) << "      <tr>" << endl;
    (*out) << "        <td class='text_actual'>Actual: </td>" << endl;
    (*out) << "        <td>" << actual << "</td>" << endl;
    (*out) << "      </tr>" << endl;
}

ResultTestFailedVariables::ResultTestFailedVariables(
    const std::string& _file,
    int _line,
    const std::string& _expression) :
    file(_file), line(_line), expression(_expression),
    names(), values() {
}

ResultTestFailedVariables::~ResultTestFailedVariables() {
}

void ResultTestFailedVariables::addParameter(const std::string& name,
                                             const std::string& value) {
    this->names.push_back(name);
    this->values.push_back(value);
}

void ResultTestFailedVariables::print() const {
    cout << file << "(" << line << "): "  << expression << endl;
    for (size_t i = 0; i < names.size(); ++i) {
        cout << "    " << names[i] << " => " << values[i] << endl;
    }
}

void ResultTestFailedVariables::printToHtml(ofstream* out) const {
    (*out) << "      <tr class='code_line'>" << endl;
    (*out) << "        <td colspan='2'>" << endl;
    (*out) << "          <a href='" << file << "'>" << file << "</a>";
    (*out) << "(" << line << "): " << expression << "</td>" << endl;
    (*out) << "      </tr>" << endl;
    for (size_t i = 0; i < names.size(); ++i) {
        (*out) << "      <tr class='parameters'>" << endl;
        (*out) << "        <td class='parameter_name'>" << endl;
        (*out) << names[i] << " => " << endl;
        (*out) << "        </td>" << endl;
        (*out) << "        <td class='parameter_value'>" << endl;
        (*out) << values[i] << endl;
        (*out) << "        </td>" << endl;
        (*out) << "      </tr>" << endl;
    }
}

ResultCaseBegin::ResultCaseBegin() {
}

ResultCaseBegin::~ResultCaseBegin() {
}

void ResultCaseBegin::print() const {
}

void ResultCaseBegin::printToHtml(std::ofstream*) const {
}

ResultCaseEnd::ResultCaseEnd(const std::string& _caseName, bool _passed) :
    caseName(_caseName), passed(_passed) {
}

ResultCaseEnd::~ResultCaseEnd() {
}

void ResultCaseEnd::print() const {
    if (this->passed) {
        color(&cout, TextColor::GREEN, "[ PASSED ] ");
    } else {
        color(&cout, TextColor::RED, "[ FAILED ] ");
    }
    cout << this->caseName << endl;
}

void ResultCaseEnd::printToHtml(ofstream* out) const {
    if (this->passed) {
        (*out) << "      <tr>" << endl;
        (*out) << "        <td class='passed'>" << endl;
        (*out) << "[------ PASSED ------]" << endl;
        (*out) << "        </td>" << endl;
    } else {
        (*out) << "      <tr>" << endl;
        (*out) << "        <td class='failed'>" << endl;
        (*out) << "[------ FAILED ------]" << endl;
        (*out) << "        </td>" << endl;
    }
    (*out) << "        <td class='case_title'>" << endl;
    (*out) << this->caseName << endl;
    (*out) << "        </td>" << endl;
    (*out) << "      </tr>" << endl;
}

ResultPercentage::ResultPercentage(int _passed, int _total) :
    passed(_passed), total(_total) {
}

ResultPercentage::~ResultPercentage() {
}

void ResultPercentage::print() const {
    if (passed == total) {
        color(&cout, TextColor::GREEN, "[= 100% =] ");
        cout << "Passed all " << total << " test cases." << endl;
    } else {
        color(&cout, TextColor::RED, "[= ");
        int percentage = passed * 100 / total;
        if (percentage >= 10) {
            color(&cout, TextColor::RED, " ");
        } else {
            color(&cout, TextColor::RED, "  ");
        }
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", percentage);
        color(&cout, TextColor::RED, buf);
        color(&cout, TextColor::RED, "% =]");
        cout << endl;
        cout << passed << " / " << total << " test cases passed." << endl;
    }
}

void ResultPercentage::printToHtml(ofstream* out) const {
    if (passed == total) {
        (*out) << "      <tr>" << endl;
        (*out) << "        <td class='passed'>" << endl;
        (*out) << "[======= 100% =======]" << endl;
        (*out) << "        </td>" << endl;
        (*out) << "        <td class='percentage_text'>" << endl;
        (*out) << "Passed all " << total << " test cases." << "</td>" << endl;
        (*out) << "      </tr>" << endl;
    } else {
        (*out) << "      <tr>" << endl;
        (*out) << "        <td class='failed'>[======= ";
        int percentage = passed * 100 / total;
        if (percentage >= 10) {
            (*out) << "&nbsp;";
        } else {
            (*out) << "&nbsp;&nbsp;";
        }
        (*out) << percentage << "% =======] " << "</td>" << endl;
        (*out) << "        <td class='percentage_text'>";
        (*out) << passed << "/" << total << " test cases passed. </td>" << endl;
        (*out) << "      </tr>" << endl;
    }
}

}  // namespace test
