#ifndef MYSMARTPOINTER_H
#define MYSMARTPOINTER_H

#include "RefCounter.h"

template<typename T>
class MySmartPointer {
public:
    MySmartPointer(T* pointer);
    MySmartPointer(const MySmartPointer& other);
    ~MySmartPointer();
    MySmartPointer(T* pointer, bool isDynamicallyAllocated);

    T& operator*();
    T* operator->();

    MySmartPointer& operator=(const MySmartPointer& other);

private:
    T* pointer;
    RefCounter* counter;
    bool dynamicallyAllocated;
};

template<typename T>
MySmartPointer<T>::MySmartPointer(T* pointer) {
    this->pointer = pointer;
    counter = new RefCounter();
    counter->add();
    dynamicallyAllocated = true;
}

template<typename T>
MySmartPointer<T>::MySmartPointer(const MySmartPointer& other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->add();
    dynamicallyAllocated = other.dynamicallyAllocated;
}

template<typename T>
MySmartPointer<T>::~MySmartPointer() {
    if (counter->dec() == 0) {
        if (dynamicallyAllocated) {
            delete pointer;
        }
        delete counter;
    }
}

template<typename T>
T& MySmartPointer<T>::operator*() {
    return *pointer;
}

template<typename T>
T* MySmartPointer<T>::operator->() {
    return pointer;
}

template<typename T>
MySmartPointer<T>& MySmartPointer<T>::operator=(const MySmartPointer& other) {
    if (this != &other) {
        if (counter->dec() == 0) {
            if (dynamicallyAllocated) {
                delete pointer;
            }
            delete counter;
        }

        pointer = other.pointer;
        counter = other.counter;
        counter->add();
        dynamicallyAllocated = other.dynamicallyAllocated;
    }
    return *this;
}

template<typename T>
MySmartPointer<T>::MySmartPointer(T* pointer, bool isDynamicallyAllocated) {
    this->pointer = pointer;
    counter = new RefCounter();
    counter->add();
    dynamicallyAllocated = isDynamicallyAllocated;
}

#endif