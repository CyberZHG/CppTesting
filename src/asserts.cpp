#include <cstring>
#include "asserts.h"
using namespace ztest;

int ztest::strcasecmp(const char* a, const char* b) {
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
