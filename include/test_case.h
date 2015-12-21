/* Copyright 2015 ZhaoHG */
#ifndef INCLUDE_TEST_CASE_H_
#define INCLUDE_TEST_CASE_H_

namespace ztest {

class UnitTest;

class TestCase {
 public:
    TestCase() {}
    virtual ~TestCase() {}
    virtual UnitTest* newTest() = 0;
};

template<class UnitTestClass>
class TestCaseSpecialize : public TestCase {
 public:
    TestCaseSpecialize() {}
    virtual ~TestCaseSpecialize() {}
    UnitTest* newTest() final {
        return new UnitTestClass();
    }
};

}  // namespace ztest

#endif  // INCLUDE_TEST_CASE_H_
