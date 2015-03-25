#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED

#include <string>
#include <vector>

namespace ztest {

void printBaseFailed(std::string fileName, int lineNum, std::string expression, std::string expected, std::string actual);
void printPredFailed(std::string fileName, int lineNum, std::string expression,
                     std::vector<std::string> parameterNames,
                     std::vector<std::string> parameterValus);

};

#endif // PRINTER_H_INCLUDED
