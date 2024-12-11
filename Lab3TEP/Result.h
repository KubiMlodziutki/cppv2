#ifndef RESULT_H
#define RESULT_H

#include <vector>

using namespace std;

template <typename T, typename E>
class Result {
public:
    Result(const T& value);
    Result(E* error);
    Result(vector<E*>& errors);
    Result(const Result<T, E>& other);

    ~Result();

    static Result<T, E> ok(const T& value);
    static Result<T, E> fail(E* error);
    static Result<T, E> fail(vector<E*>& errors);

    Result<T, E>& operator=(const Result<T, E>& other);

    bool isSuccess();

    T getValue();
    vector<E*>& getErrors();

private:
    T* resultValue;
    vector<E*> resultErrors;
};


template <typename E>
class Result<void, E> {
public:
    Result();
    Result(E* error);
    Result(vector<E*>& errors);
    Result(const Result<void, E>& other);

    ~Result();

    static Result<void, E> ok();
    static Result<void, E> fail(E* error);
    static Result<void, E> fail(vector<E*>& errors);

    Result<void, E>& operator=(const Result<void, E>& other);

    bool isSuccess();

    vector<E*>& getErrors();

private:
    bool resultSuccess;
    vector<E*> resultErrors;
};

template <typename T, typename E>
Result<T, E>::Result(const T& value) : resultValue(new T(value)) {}

template <typename T, typename E>
Result<T, E>::Result(E* error) : resultValue(0) {
    if (error) {
        resultErrors.push_back(error);
    }
}

template <typename T, typename E>
Result<T, E>::Result(vector<E*>& errors) : resultValue(0), resultErrors(errors) {}

template <typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other) : resultValue(other.resultValue ? new T(*other.resultValue) : 0), resultErrors(other.resultErrors) {}

template <typename T, typename E>
Result<T, E>::~Result() {
    delete resultValue;
}

template <typename T, typename E>
Result<T, E> Result<T, E>::ok(const T& value) {
    return Result<T, E>(value);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::fail(E* error) {
    return Result<T, E>(error);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::fail(vector<E*>& errors) {
    return Result<T, E>(errors);
}

template <typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other) {
    if (this != &other) {
        delete resultValue;
        resultValue = other.resultValue ? new T(*other.resultValue) : 0;
        resultErrors = other.resultErrors;
    }

    return *this;
}

template <typename T, typename E>
bool Result<T, E>::isSuccess() {
    return resultValue != 0;
}

template <typename T, typename E>
T Result<T, E>::getValue() {
    return *resultValue;
}

template <typename T, typename E>
vector<E*>& Result<T, E>::getErrors() {
    return resultErrors;
}


template <typename E>
Result<void, E>::Result() : resultSuccess(true) {}

template <typename E>
Result<void, E>::Result(E* error) : resultSuccess(false) {
    if (error) {
        resultErrors.push_back(error);
    }
}

template <typename E>
Result<void, E>::Result(vector<E*>& errors) : resultSuccess(false), resultErrors(errors) {}

template <typename E>
Result<void, E>::Result(const Result<void, E>& other) : resultSuccess(other.resultSuccess), resultErrors(other.resultErrors) {}

template <typename E>
Result<void, E>::~Result() {}

template <typename E>
Result<void, E> Result<void, E>::ok() {
    return Result<void, E>();
}

template <typename E>
Result<void, E> Result<void, E>::fail(E* error) {
    return Result<void, E>(error);
}

template <typename E>
Result<void, E> Result<void, E>::fail(vector<E*>& errors) {
    return Result<void, E>(errors);
}

template <typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& other) {
    if (this != &other) {
        resultSuccess = other.resultSuccess;
        resultErrors = other.resultErrors;
    }
    return *this;
}

template <typename E>
bool Result<void, E>::isSuccess() {
    return resultSuccess;
}

template <typename E>
vector<E*>& Result<void, E>::getErrors() {
    return resultErrors;
}

#endif