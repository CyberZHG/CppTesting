#ifndef ASSERTS_H_INCLUDED
#define ASSERTS_H_INCLUDED

#include <string>
#include <sstream>
#include "printer.h"

#define __TEST_BASE_(actualText, result, expectValue, actualValue, fatal) \
if (!result) { \
    Framework* framework = Framework::getInstance(); \
    framework->setFailedFlag(); \
    printBaseFailed(__FILE__, __LINE__, actualText, expectValue, actualValue); \
    if (fatal) { \
        return; \
    } \
}

#define __TEST_TRUE_(expression, fatal) { \
    bool result = (expression); \
    std::string actualValue = result ? "true" : "false"; \
    __TEST_BASE_(#expression, result, "true", actualValue, false); \
}

#define __TEST_FALSE_(expression, fatal) { \
    bool result = (expression); \
    std::string actualValue = result ? "true" : "false"; \
    __TEST_BASE_(#expression, !result, "false", actualValue, false); \
}

#define __EXPECT_TRUE(expression) \
    __TEST_TRUE_(expression, false)

#define __EXPECT_FALSE(expression) \
    __TEST_FALSE_(expression, false)

#define __ASSERT_TRUE(expression) \
    __TEST_TRUE_(expression, true)

#define __ASSERT_FALSE(expression) \
    __TEST_FALSE_(expression, false)

#endif // ASSERTS_H_INCLUDED
