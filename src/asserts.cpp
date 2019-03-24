/* Copyright 2019 Zhao HG

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
#include <cstring>
#include <string>
#include "asserts.h"

using std::string;

namespace test {

int strcasecmp(const char* a, const char* b) {
    while (*a != 0 && *b != 0) {
        if (tolower(*a) < tolower(*b)) {
            return -1;
        }
        if (tolower(*a) > tolower(*b)) {
            return 1;
        }
        ++a, ++b;
    }
    if (*b != 0) {
        return -1;
    }
    if (*a != 0) {
        return 1;
    }
    return 0;
}

inline char dec2hex(const int x) {
    return x < 10 ? '0' + x : 'A' + x - 10;
}

string mem2str(const void* mem, const int len) {
    string s;
    const char* data = reinterpret_cast<const char*>(mem);
    for (int i = 0; i < len; ++i) {
        if (32 <= data[i] && data[i] <= 126) {
            s += data[i];
        } else {
            s += "\\x";
            s += dec2hex(data[i] / 16);
            s += dec2hex(data[i] % 16);
        }
    }
    return s;
}

}  // namespace test
