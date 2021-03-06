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
#ifndef INCLUDE_TEST_CASE_H_
#define INCLUDE_TEST_CASE_H_

#include <string>

namespace test {

class UnitTest;

class TestCase {
 public:
    TestCase(const std::string& file, int line) : _file(file), _line(line) {}
    virtual ~TestCase() {}
    virtual UnitTest* newTest() = 0;

    inline const std::string& file() const { return _file; }
    inline int line() const {  return _line; }

 private:
     std::string _file;
     int _line;
};

template<class UnitTestClass>
class TestCaseSpecialize : public TestCase {
 public:
    TestCaseSpecialize(const std::string& file, int line) :
        TestCase(file, line) {}
    virtual ~TestCaseSpecialize() {}
    UnitTest* newTest() final {
        return new UnitTestClass();
    }
};

}  // namespace test

#endif  // INCLUDE_TEST_CASE_H_
