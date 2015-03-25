# ZTest

This is a C++ testing framework which imitates gtest's interface since gtest is outside our great wall and it is difficult to compile on Windows. The framework is writtern based on some C++11 features, and it could be cross-platform.

![Sample](https://cloud.githubusercontent.com/assets/853842/6818613/0fe927b0-d2ee-11e4-830a-6c18a41e280e.png)

## Instruction

### Fundamental

A __test suite__ contains many __test cases__ of the same purpose. You can not create a __test case__ without creating a __test suite__. To create a test suite, just inherit `UnitTest` class, the name of the inherited class is the name of the test suite.

Example:
```cpp
#include "ztest.h"
using namespace ztest;

class ExampleUnitTest : public UnitTest {
public:
    virtual void setUp() override final {}
    virtual void setUpEach() override final {}
    virtual void tearDownEach() override final {}
    virtual void tearDown() override final {}
protected:
    int inClassValue;
};
```

In this example, `ExampleUnitTest` is the name of the test suite. There are four virtual function could be optionally implemented. `setUp()` and `tearDown()` will be invoked before and after running tests in the test suite separately, while `setUpEach()` and `tearDownEach()` will be called each time a single test case being tested.

**Note that** the variables you want to use in the test cases should be public or protected. If you insist on using private variables, please create getter/setter functions for them.

To create a *test case*, use the macro `__TEST_U`:

```cpp
__TEST_U(ExampleUnitTest, test1) {
    __ASSERT_EQ(this->inClassValue, 1);
}
__TEST_U(ExampleUnitTest, test2) {
    __EXPECT_TRUE(true);
}
```

The first parameter of `__TEST_U` is the name of the test suite, the second parameter is the name of the test case. The combination of suite name and case name should be identical.

After the definition of the test suites and test cases, we can run our tests:

```cpp
int main()
{
    Framework* framework = Framework::getInstance();
    framework->runTests();
    return 0;
}
```

The framework uses `ostream` to print the results, thus it is not a wise choice to turn off `sync_with_stdio` or print something without `\n`.

Compile the code above, you will see something like this:

![Example](https://cloud.githubusercontent.com/assets/853842/6819000/023a4df4-d2f5-11e4-80a1-b172ad871b3a.png)

## Expectation and Assertion

As shown above, there are some macros named like `__EXPECT_*` or `__ASSERT_*`. These two types of macros are the key parts of the test cases. They checks whether the actual value satisfy the specific relationship with the expected value, and `__ASSERT_*` will stop the test case immediately if the actual value could not meet the needs while `__EXPECT_*` will continue running the test case.

### Boolean

```cpp
__EXPECT_TRUE(actual) __ASSERT_TRUE(actual)
__EXPECT_FALSE(actual) __ASSERT_FALSE(actual)
```

### Arithmetic

```cpp
// Equal to...
__EXPECT_EQ(expect, actual) __ASSERT_EQ(expect, actual)
// Not equal to...
__EXPECT_NQ(expect, actual) __ASSERT_NQ(expect, actual)
// Less than...
__EXPECT_LT(expect, actual) __ASSERT_LT(expect, actual)
// Less than or equal to...
__EXPECT_LE(expect, actual) __ASSERT_LE(expect, actual)
// Greater than...
__EXPECT_GT(expect, actual) __ASSERT_GT(expect, actual)
// Greater than or equal to...
__EXPECT_GE(expect, actual) __ASSERT_GE(expect, actual)
```

**Note that** since you are comparing two objects, the corresponding arithmetic operators should have been overloaded. And since the value of the object will be printed if the test fails, `ostream` should also be overloaded.

### String in C

```cpp
// (Case-sensitive) Equal to
__EXPECT_STREQ(expect, actual) __ASSERT_STREQ(expect, actual)
// (Case-sensitive) Not equal to
__EXPECT_STRNE(expect, actual) __ASSERT_STRNE(expect, actual)
// (Case-insensitive) Equal to
__EXPECT_STRCASEEQ(expect, actual) __ASSERT_STRCASEEQ(expect, actual)
// (Case-insensitive) Not equal to
__EXPECT_STRCASENE(expect, actual) __ASSERT_STRCASENE(expect, actual)
```

These macros are used to compare C strings like `__EXPECT_STRCASEEQ("WORLD", "world")`.

### Sucess and Fail

```cpp
// Immediately success.
__SUCCESS()
// Immediately fail.
__FAIL()
// Fail and go on.
__ADD_FAIL()
```

### Throw

```cpp
// The statement should throw exception with exceptionType.
__EXPECT_THROW(statement, exceptionType) __ASSERT_THROW(statement, exceptionType)
// The statement should throw any exception.
__EXPECT_ANY_THROW(statement) __ASSERT_ANY_THROW(statement)
// The statement should not throw exception.
__EXPECT_NO_THROW(statement) __ASSERT_NO_THROW(statement)
```
