#ifndef TEST_CASE_H_INCLUDED
#define TEST_CASE_H_INCLUDED

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
    virtual UnitTest* newTest() override final {
        return new UnitTestClass();
    }
};

}

#endif // TEST_CASE_H_INCLUDED
