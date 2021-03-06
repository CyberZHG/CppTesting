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
#ifndef INCLUDE_ASSERTS_H_
#define INCLUDE_ASSERTS_H_

#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "results.h"
#include "exceptions.h"

namespace test {

int strcasecmp(const char* a, const char* b);
std::string mem2str(const void* mem, int len);

#define __TEST_BASE_(actualText, result, expectValue, actualValue, fatal) { \
    if (!result) { \
        Framework* framework = Framework::getInstance(); \
        framework->setFailedFlag(); \
        framework->appendResult(std::shared_ptr<Result> \
                                (new ResultTestFailed(__FILE__, __LINE__, \
                                                      actualText, \
                                                      expectValue, \
                                                      actualValue))); \
        if (fatal) { \
            throw AssertException(); \
        } \
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
    __TEST_NE_(expect, actual, false)

#define __ASSERT_NE(expect, actual) \
    __TEST_NE_(expect, actual, true)

#define __TEST_LT_(expect, actual, fatal) \
    __TEST_ARITH_(<, expect, actual, fatal)

#define __EXPECT_LT(expect, actual) \
    __TEST_LT_(expect, actual, false)

#define __ASSERT_LT(expect, actual) \
    __TEST_LT_(expect, actual, true)

#define __TEST_LE_(expect, actual, fatal) \
    __TEST_ARITH_(<=, expect, actual, fatal)

#define __EXPECT_LE(expect, actual) \
    __TEST_LE_(expect, actual, false)

#define __ASSERT_LE(expect, actual) \
    __TEST_LE_(expect, actual, true)

#define __TEST_GT_(expect, actual, fatal) \
    __TEST_ARITH_(>, expect, actual, fatal)

#define __EXPECT_GT(expect, actual) \
    __TEST_GT_(expect, actual, false)

#define __ASSERT_GT(expect, actual) \
    __TEST_GT_(expect, actual, true)

#define __TEST_GE_(expect, actual, fatal) \
    __TEST_ARITH_(>=, expect, actual, fatal)

#define __EXPECT_GE(expect, actual) \
    __TEST_GE_(expect, actual, false)

#define __ASSERT_GE(expect, actual) \
    __TEST_GE_(expect, actual, true)

#define __TEST_NEAR_(expect, actual, absError, fatal) { \
    auto expectVal = (expect); \
    auto actualVal = (actual); \
    bool result = fabs(expectVal - actualVal) < absError; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_NEAR(expect, actual, absError) \
    __TEST_NEAR_(expect, actual, absError, false)

#define __ASSERT_NEAR(expect, actual, absError) \
    __TEST_NEAR_(expect, actual, absError, true)

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

#define __TEST_MEMEQ_(expect, actual, len, fatal) { \
    std::string expectVal = mem2str((expect), len); \
    std::string actualVal = mem2str((actual), len); \
    bool result = memcmp(expect, actual, len) == 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_MEMEQ(expect, actual, len) \
    __TEST_MEMEQ_(expect, actual, len, false)

#define __ASSERT_MEMEQ(expect, actual, len) \
    __TEST_MEMEQ_(expect, actual, len, true)


#define __TEST_MEMNE_(expect, actual, len, fatal) { \
    std::string expectVal = mem2str((expect), len); \
    std::string actualVal = mem2str((actual), len); \
    bool result = memcmp(expect, actual, len) != 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_MEMNE(expect, actual, len) \
    __TEST_MEMNE_(expect, actual, len, false)

#define __ASSERT_MEMNE(expect, actual, len) \
    __TEST_MEMNE_(expect, actual, len, true)

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
    bool result = test::strcasecmp(expectVal, actualVal) == 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_STRCASEEQ(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, false)

#define __ASSERT_STRCASEEQ(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, true)

#define __TEST_STRCASENE_(expect, actual, fatal) { \
    const char* expectVal = (expect); \
    const char* actualVal = (actual); \
    bool result = test::strcasecmp(expectVal, actualVal) != 0; \
    __TEST_DUAL_(actual, result, expectVal, actualVal, fatal) \
}

#define __EXPECT_STRCASENE(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, false)

#define __ASSERT_STRCASENE(expect, actual) \
    __TEST_STRCASEEQ_(expect, actual, true)

#define __SUCCESS() { \
    return; \
}

#define __FAIL() { \
    __TEST_BASE_("", false, "", "", true) \
}

#define __ADD_FAIL() { \
    __TEST_BASE_("", false, "", "", false) \
}

#define __TEST_THROW_(statement, exception_type, fatal) { \
    bool caught = false; \
    bool gotException = false; \
    try { \
        statement; \
    } catch (exception_type e) { \
        caught = true; \
    } catch (...) { \
        gotException = true; \
    } \
    if (!caught) { \
        if (gotException) { \
            __TEST_BASE_(#statement, false, #exception_type, \
                         "Unknown Exception", fatal) \
        } else { \
            __TEST_BASE_(#statement, false, #exception_type, \
                         "No Exception", fatal) \
        } \
    } \
}

#define __EXPECT_THROW(statement, exception_type) \
    __TEST_THROW_(statement, exception_type, false)

#define __ASSERT_THROW(statement, exception_type) \
    __TEST_THROW_(statement, exception_type, true)

#define __TEST_ANY_THROW_(statement, fatal) { \
    bool caught = false; \
    try { \
        statement; \
    } catch (...) { \
        caught = true; \
    } \
    if (!caught) { \
        __TEST_BASE_(#statement, false, "Any Throw", "No Throw", fatal) \
    } \
}

#define __EXPECT_ANY_THROW(statement) \
    __TEST_ANY_THROW_(statement, false)

#define __ASSERT_ANY_THROW(statement) \
    __TEST_ANY_THROW_(statement, true)

#define __TEST_NO_THROW_(statement, fatal) { \
    bool caught = false; \
    try { \
        statement; \
    } catch (...) { \
        caught = true; \
    } \
    if (caught) { \
        __TEST_BASE_(#statement, false, "No Throw", "Unknown Throw", fatal) \
    } \
}

#define __EXPECT_NO_THROW(statement) \
    __TEST_NO_THROW_(statement, false)

#define __ASSERT_NO_THROW(statement) \
    __TEST_NO_THROW_(statement, true)

#define __TEST_PRED_FORMAT_ADD_VALUE_(parameterName, parameterValue) \
    out.str(""); \
    out.clear(); \
    out << parameterValue; \
    std::static_pointer_cast<ResultTestFailedVariables>(result)-> \
        addParameter(parameterName, out.str());

#define __TEST_PRED_FORMAT1_(func, val1, fatal) { \
    auto val1Val = (val1); \
    if (!(func(val1Val))) { \
        std::ostringstream out; \
        Framework* framework = Framework::getInstance(); \
        framework->setFailedFlag(); \
        std::shared_ptr<Result> result(\
            new ResultTestFailedVariables(__FILE__, __LINE__, \
                                          ""#func"("#val1")")); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val1, val1Val); \
        framework->appendResult(result); \
        if (fatal) { \
            throw AssertException(); \
        } \
    } \
}

#define __EXPECT_PRED_FORMAT1(func, val1) \
    __TEST_PRED_FORMAT1_(func, val1, false)

#define __ASSERT_PRED_FORMAT1(func, val1) \
    __TEST_PRED_FORMAT1_(func, val1, true)

#define __TEST_PRED_FORMAT2_(func, val1, val2, fatal) { \
    auto val1Val = (val1); \
    auto val2Val = (val2); \
    if (!(func(val1Val, val2Val))) { \
        std::ostringstream out; \
        Framework* framework = Framework::getInstance(); \
        framework->setFailedFlag(); \
        std::shared_ptr<Result> result(\
            new ResultTestFailedVariables(__FILE__, __LINE__, \
                                          ""#func"("#val1", "#val2")")); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val1, val1Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val2, val2Val); \
        framework->appendResult(result); \
        if (fatal) { \
            throw AssertException(); \
        } \
    } \
}

#define __EXPECT_PRED_FORMAT2(func, val1, val2) \
    __TEST_PRED_FORMAT2_(func, val1, val2, false)

#define __ASSERT_PRED_FORMAT2(func, val1, val2) \
    __TEST_PRED_FORMAT2_(func, val1, val2, true)

#define __TEST_PRED_FORMAT3_(func, val1, val2, val3, fatal) { \
    auto val1Val = (val1); \
    auto val2Val = (val2); \
    auto val3Val = (val3); \
    if (!(func(val1Val, val2Val, val3Val))) { \
        std::ostringstream out; \
        Framework* framework = Framework::getInstance(); \
        framework->setFailedFlag(); \
        std::shared_ptr<Result> result(\
            new ResultTestFailedVariables(__FILE__, __LINE__, \
                                    ""#func"("#val1", "#val2", "#val3")")); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val1, val1Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val2, val2Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val3, val3Val); \
        framework->appendResult(result); \
        if (fatal) { \
            throw AssertException(); \
        } \
    } \
}

#define __EXPECT_PRED_FORMAT3(func, val1, val2, val3) \
    __TEST_PRED_FORMAT3_(func, val1, val2, val3, false)

#define __ASSERT_PRED_FORMAT3(func, val1, val2, val3) \
    __TEST_PRED_FORMAT3_(func, val1, val2, val3, true)

#define __TEST_PRED_FORMAT4_(func, val1, val2, val3, val4, fatal) { \
    auto val1Val = (val1); \
    auto val2Val = (val2); \
    auto val3Val = (val3); \
    auto val4Val = (val4); \
    if (!(func(val1Val, val2Val, val3Val, val4Val))) { \
        std::ostringstream out; \
        Framework* framework = Framework::getInstance(); \
        framework->setFailedFlag(); \
        std::shared_ptr<Result> result(\
            new ResultTestFailedVariables(__FILE__, __LINE__, \
                            ""#func"("#val1", "#val2", "#val3", "#val4")")); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val1, val1Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val2, val2Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val3, val3Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val4, val4Val); \
        framework->appendResult(result); \
        if (fatal) { \
            throw AssertException(); \
        } \
    } \
}

#define __EXPECT_PRED_FORMAT4(func, val1, val2, val3, val4) \
    __TEST_PRED_FORMAT4_(func, val1, val2, val3, val4, false)

#define __ASSERT_PRED_FORMAT4(func, val1, val2, val3, val4) \
    __TEST_PRED_FORMAT4_(func, val1, val2, val3, val4, true)

#define __TEST_PRED_FORMAT5_(func, val1, val2, val3, val4, val5, fatal) { \
    auto val1Val = (val1); \
    auto val2Val = (val2); \
    auto val3Val = (val3); \
    auto val4Val = (val4); \
    auto val5Val = (val5); \
    if (!(func(val1Val, val2Val, val3Val, val4Val, val5Val))) { \
        std::ostringstream out; \
        Framework* framework = Framework::getInstance(); \
        framework->setFailedFlag(); \
        std::shared_ptr<Result> result(\
            new ResultTestFailedVariables(__FILE__, __LINE__, \
                    ""#func"("#val1", "#val2", "#val3", "#val4", "#val5")")); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val1, val1Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val2, val2Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val3, val3Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val4, val4Val); \
        __TEST_PRED_FORMAT_ADD_VALUE_(#val5, val5Val); \
        framework->appendResult(result); \
        if (fatal) { \
            throw AssertException(); \
        } \
    } \
}

#define __EXPECT_PRED_FORMAT5(func, val1, val2, val3, val4, val5) \
    __TEST_PRED_FORMAT5_(func, val1, val2, val3, val4, val5, false)

#define __ASSERT_PRED_FORMAT5(func, val1, val2, val3, val4, val5) \
    __TEST_PRED_FORMAT5_(func, val1, val2, val3, val4, val5, true)

}  // namespace test

#endif  // INCLUDE_ASSERTS_H_
