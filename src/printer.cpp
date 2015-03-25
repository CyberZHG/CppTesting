#include <iostream>
#include "printer.h"
using namespace std;

const int MAX_LINE_WIDTH = 80;

void ztest::printBaseFailed(string fileName, int lineNum, string expression, string expected, string actual) {
    cout << fileName << "(" << lineNum << "): "  << expression << endl;
    if (expected.length() > 0 && actual.length() > 0) {
        cout << "    " << "Expect: " << expected.substr(0, MAX_LINE_WIDTH - 13) << endl;
        cout << "    " << "Actual: " << actual.substr(0, MAX_LINE_WIDTH - 13) << endl;
    }
}

void ztest::printPredFailed(string fileName, int lineNum, string expression,
                            vector<string> parameterNames,
                            vector<string> parameterValus) {
    cout << fileName << "(" << lineNum << "): "  << expression << endl;
    for (size_t i = 0; i < parameterNames.size(); ++i) {
        cout << "    " << parameterNames[i] << " => " << parameterValus[i] << endl;
    }
}
