#include "MySmartPointer.h"

template<typename T>
MySmartPointer<T>::MySmartPointer(T* pointer) {
    this->pointer = pointer;
    counter = new RefCounter();
    counter->add();
    allocated_with_new = true;
}

template<typename T>
MySmartPointer<T>::MySmartPointer(const MySmartPointer& other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->add();
    allocated_with_new = other.allocated_with_new;
}

template<typename T>
MySmartPointer<T>::~MySmartPointer() {
    if (counter->dec() == 0) {
        if (allocated_with_new) {
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
            if (allocated_with_new) {
                delete pointer;
            }
            delete counter;
        }

        pointer = other.pointer;
        counter = other.counter;
        counter->add();
        allocated_with_new = other.allocated_with_new;
    }
    return *this;
}

template<typename T>
MySmartPointer<T>::MySmartPointer(T* pointer, bool isDynamicallyAllocated) {
    this->pointer = pointer;
    counter = new RefCounter();
    counter->add();
    allocated_with_new = isDynamicallyAllocated;
}
