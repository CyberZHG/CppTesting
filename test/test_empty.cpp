/* Copyright 2015 ZhaoHG */
#include "../include/ztest.h"

using ztest::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    return !framework->isAllPassed();
}

