#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <string>

using namespace std;

class TestObject {
public:
    TestObject(int value);
    ~TestObject();

    int getValue() const;
    void setValue(int newTestValue);

private:
    int testValue;
    string TEST_CONSTRUCTOR = "Test object has been created: ";
    string TEST_DESTRUCTOR = "Test object has been destroyed: ";
};

#endif