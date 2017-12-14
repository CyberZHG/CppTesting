#include <cstring>
#include <string>
#include "../include/asserts.h"

using std::string;

namespace ztest {

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

}  // namespace ztest
