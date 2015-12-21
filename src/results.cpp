/* Copyright 2015 ZhaoHG */
#include <cstdio>
#include <string>
#include "../include/stream_color.h"
#include "../include/results.h"

namespace ztest {

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

ResultSuiteBegin::ResultSuiteBegin(string _title) :
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

void ResultTestFailed::printToHtml(ofstream* out) const {
    (*out) << "      <tr class='code_line'>" << endl;
    (*out) << "        <td colspan='2'>" << endl;
    (*out) << "          <a href='" << file << "'>" << file << "</a>";
    (*out) << "(" << line << "): " << expression << "</td>" << endl;
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

ResultCaseEnd::ResultCaseEnd(string _caseName, bool _passed) :
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
        sprintf(buf, "%d", percentage);
        color(&cout, TextColor::RED, buf);
        color(&cout, TextColor::RED, "% =] ");
        cout << endl;
        cout << passed << " / " << total << " test cases passed. " << endl;
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

}  // namespace ztest
