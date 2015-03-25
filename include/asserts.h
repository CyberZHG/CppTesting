#ifndef ASSERTS_H_INCLUDED
#define ASSERTS_H_INCLUDED

#include <cstring>
#include <string>
#include <sstream>
#include "printer.h"

namespace ztest {

int strcasecmp(const char* a, const char* b);

#define __TEST_BASE_(actualText, result, expectValue, actualValue, fatal) \
if (!result) { \
    Framework* framework = Framework::getInstance(); \
    framework->setFailedFlag(); \
    ztest::printBaseFailed(__FILE__, __LINE__, actualText, expectValue, actualValue); \
    if (fatal) { \
        return; \
    } \
}

#define __TEST_TRUE_(expression, fatal) { \
    bool result = (expression); \
    std::string actualValue = result ? "true" : "false"; \
    __TEST_BASE_(#expression, result, "true", actualValue, fatal); \
}

#define __TEST_FALSE_(expression, fatal) { \
    bool result = (expression); \
    std::string actualValue = result ? "true" : "false"; \
    __TEST_BASE_(#expression, !result, "false", actualValue, fatal); \
}

#define __EXPECT_TRUE(expression) \
    __TEST_TRUE_(expression, false)

#define __EXPECT_FALSE(expression) \
    __TEST_FALSE_(expression, false)

#define __ASSERT_TRUE(expression) \
    __TEST_TRUE_(expression, true)

#define __ASSERT_FALSE(expression) \
    __TEST_FALSE_(expression, false)

#define __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) { \
    std::ostringstream out; \
    out << expectVal; \
    std::string expectValStr = out.str(); \
    out.str(""); \
    out.clear(); \
    out << actualVal; \
    std::string actualValStr = out.str(); \
    __TEST_BASE_(#actual, result, expectValStr, actualValStr, fatal); \
}

#define __TEST_ARITH_(op, expect, actual, fatal) { \
    auto expectVal = (expect); \
    auto actualVal = (actual); \
    bool result = (expectVal op actualVal); \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __TEST_EQ_(expect, actual, fatal) \
    __TEST_ARITH_(==, expect, actual, fatal)

#define __EXPECT_EQ(expect, actual) \
    __TEST_EQ_(expect, actual, false)

#define __ASSERT_EQ(expect, actual) \
    __TEST_EQ_(expect, actual, true)

#define __TEST_NE_(expect, actual, fatal) \
    __TEST_ARITH_(!=, expect, actual, fatal)

#define __EXPECT_NE(expect, actual) \
    __TEST_EQ_(expect, actual, false)

#define __ASSERT_NE(expect, actual) \
    __TEST_EQ_(expect, actual, true)

#define __TEST_LT_(expect, actual, fatal) \
    __TEST_ARITH_(<, expect, actual, fatal)

#define __EXPECT_LT(expect, actual) \
    __TEST_EQ_(expect, actual, false)

#define __ASSERT_LT(expect, actual) \
    __TEST_EQ_(expect, actual, true)

#define __TEST_LE_(expect, actual, fatal) \
    __TEST_ARITH_(<=, expect, actual, fatal)

#define __EXPECT_LE(expect, actual) \
    __TEST_EQ_(expect, actual, false)

#define __ASSERT_LE(expect, actual) \
    __TEST_EQ_(expect, actual, true)

#define __TEST_GT_(expect, actual, fatal) \
    __TEST_ARITH_(>, expect, actual, fatal)

#define __EXPECT_GT(expect, actual) \
    __TEST_EQ_(expect, actual, false)

#define __ASSERT_GT(expect, actual) \
    __TEST_EQ_(expect, actual, true)

#define __TEST_GE_(expect, actual, fatal) \
    __TEST_ARITH_(>=, expect, actual, fatal)

#define __EXPECT_GE(expect, actual) \
    __TEST_EQ_(expect, actual, false)

#define __ASSERT_GE(expect, actual) \
    __TEST_EQ_(expect, actual, true)

#define __TEST_STREQ_(expect, actual, fatal) { \
    const char* expectVal = (expect); \
    const char* actualVal = (actual); \
    bool result = strcmp(expectVal, actualVal) == 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_STREQ(expect, actual) \
    __TEST_STREQ_(expect, actual, false)

#define __ASSERT_STREQ(expect, actual) \
    __TEST_STREQ_(expect, actual, true)

#define __TEST_STRNE_(expect, actual, fatal) { \
    const char* expectVal = (expect); \
    const char* actualVal = (actual); \
    bool result = strcmp(expectVal, actualVal) != 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_STRNE(expect, actual) \
    __TEST_STREQ_(expect, actual, false)

#define __ASSERT_STRNE(expect, actual) \
    __TEST_STREQ_(expect, actual, true)

#define __TEST_STRCASEEQ_(expect, actual, fatal) { \
    const char* expectVal = (expect); \
    const char* actualVal = (actual); \
    bool result = ztest::strcasecmp(expectVal, actualVal) == 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_STRCASEEQ(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, false)

#define __ASSERT_STRCASEEQ(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, true)

#define __TEST_STRCASENE_(expect, actual, fatal) { \
    const char* expectVal = (expect); \
    const char* actualVal = (actual); \
    bool result = ztest::strcasecmp(expectVal, actualVal) != 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_STRCASENE(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, false)

#define __ASSERT_STRCASENE(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, true)

}

#endif // ASSERTS_H_INCLUDED
