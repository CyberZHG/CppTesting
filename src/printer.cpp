#include <iostream>
#include "printer.h"
using namespace std;

const int MAX_LINE_WIDTH = 80;

void printBaseFailed(string fileName, int lineNum, string expression, string expected, string actual) {
    cout << fileName << "(" << lineNum << "): "  << expression << endl;
    cout << "    " << "Expect: " << expected.substr(0, MAX_LINE_WIDTH - 13) << endl;
    cout << "    " << "Actual: " << actual.substr(0, MAX_LINE_WIDTH - 13) << endl;
}
