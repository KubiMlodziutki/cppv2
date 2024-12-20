#include <iostream>
#include "TestObject.h"

using namespace std;

TestObject::TestObject(int value) : testValue(value) {
    cout << TEST_CONSTRUCTOR << testValue << endl;
}

TestObject::~TestObject() {
    cout << TEST_DESTRUCTOR << testValue << endl;
}

int TestObject::getValue() const {
    return testValue;
}

void TestObject::setValue(int newTestValue) {
    testValue = newTestValue;
}