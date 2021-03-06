C++ Unit Testing
================

[![travis-ci](https://travis-ci.org/CyberZHG/CppTesting.svg)](https://travis-ci.org/CyberZHG/CppTesting)

![Sample](https://cloud.githubusercontent.com/assets/853842/6818613/0fe927b0-d2ee-11e4-830a-6c18a41e280e.png)

## Instruction

### Fundamental

A __test suite__ contains several __test cases__. A test case cannot be created without creating a test suite. Inherit the `UnitTest` class to create a test suite:

```cpp
#include "test.h"

class ExampleUnitTest : public test::UnitTest {
 public:
    void setUp() final {}
    void setUpEach() final {}
    void tearDownEach() final {}
    void tearDown() final {}
 protected:
    int inClassValue;
};
```

In this example, `ExampleUnitTest` is the name of the test suite. There are four virtual function could be optionally implemented. `setUp()` and `tearDown()` will be invoked before and after running tests in the test suite respectively, while `setUpEach()` and `tearDownEach()` will be called each time a single test case being tested.

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

The first parameter of `__TEST_U` is the name of the test suite, the second parameter is the name of the test case. The combination of suite name and case name should be unique.

After the definition of the test suites and test cases, we can run our tests:

```cpp
int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    framework->finish();
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
__EXPECT_TRUE(actual);
__ASSERT_TRUE(actual);
__EXPECT_FALSE(actual);
__ASSERT_FALSE(actual);
```

### Arithmetic

```cpp
// Equal to...
__EXPECT_EQ(expect, actual);
__ASSERT_EQ(expect, actual);
// Not equal to...
__EXPECT_NQ(expect, actual);
__ASSERT_NQ(expect, actual);
// Less than...
__EXPECT_LT(expect, actual);
__ASSERT_LT(expect, actual);
// Less than or equal to...
__EXPECT_LE(expect, actual);
__ASSERT_LE(expect, actual);
// Greater than...
__EXPECT_GT(expect, actual);
__ASSERT_GT(expect, actual);
// Greater than or equal to...
__EXPECT_GE(expect, actual);
__ASSERT_GE(expect, actual);
// The difference of the two values does not exceed the given absolute error.
__EXPECT_NEAR(expect, actual, absError);
__ASSERT_NEAR(expect, actual, absError);
```

**Note that** since you are comparing two objects, the corresponding arithmetic operators should have been overloaded. And since the value of the object will be printed if the test fails, `ostream` should also be overloaded.

### String in C

```cpp
// (Case-sensitive) Equal to
__EXPECT_STREQ(expect, actual);
__ASSERT_STREQ(expect, actual);
// (Case-sensitive) Not equal to
__EXPECT_STRNE(expect, actual);
__ASSERT_STRNE(expect, actual);
// (Case-insensitive) Equal to
__EXPECT_STRCASEEQ(expect, actual);
__ASSERT_STRCASEEQ(expect, actual);
// (Case-insensitive) Not equal to
__EXPECT_STRCASENE(expect, actual);
__ASSERT_STRCASENE(expect, actual);
```

These macros are used to compare C strings like `__EXPECT_STRCASEEQ("WORLD", "world")`.

### Sucess and Fail

```cpp
// Immediately success.
__SUCCESS();
// Immediately fail.
__FAIL();
// Fail and go on.
__ADD_FAIL();
```

### Throw

```cpp
// The statement should throw exception with exceptionType.
__EXPECT_THROW(statement, exceptionType);
__ASSERT_THROW(statement, exceptionType);
// The statement should throw any exception.
__EXPECT_ANY_THROW(statement);
__ASSERT_ANY_THROW(statement);
// The statement should not throw exception.
__EXPECT_NO_THROW(statement);
__ASSERT_NO_THROW(statement);
```

### Predicate

```cpp
__EXPECT_PRED_FORMAT1(func, val1);
__ASSERT_PRED_FORMAT1(func, val1);

__EXPECT_PRED_FORMAT2(func, val1, val2);
__ASSERT_PRED_FORMAT2(func, val1, val2);

__EXPECT_PRED_FORMAT3(func, val1, val2, val3);
__ASSERT_PRED_FORMAT3(func, val1, val2, val3);

...
```

These macros take a function name and some parameter values as parameters. For example, `__ASSERT_PRED_FORMAT2` will test whether `func(val1, val2)` is true. If the result is not true, the corresponding parameter names and parameter values will be printed. The `func` takes at most 5 parameters.

## Output

The testing framework supports two output methods currently, which are printing to console using standard output and write the results to an HTML file:

```cpp
int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->printToHtml("results.html");
    framework->finish();
    return 0;
}
```
![HTML Result](https://cloud.githubusercontent.com/assets/853842/6884607/7ebd7b3c-d62c-11e4-9f6b-02401cd003a5.png)
