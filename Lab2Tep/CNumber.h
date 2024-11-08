#ifndef CNUMBER_H
#define CNUMBER_H

#include <string>

using namespace std;

class CNumber {
public:
    CNumber();
    CNumber(int value);
    CNumber(const string& value);
    CNumber(const CNumber& other);
    ~CNumber();

    CNumber& operator=(const int value);
    CNumber& operator=(const CNumber& other);

    CNumber operator+(const CNumber& other) const;
    CNumber operator-(const CNumber& other) const;
    CNumber operator*(const CNumber& other) const;
    CNumber operator/(const CNumber& other) const;

    string toStr() const;

private:
    int* num_tab;
    int num_tab_len;
    bool is_negative;
    string num_as_str;

    void allocate(int length);
    void copy(const CNumber& other);
    bool abs_compare(const CNumber& other) const;

    int divide_val = 10;
    int mult_val = 10;
};

#endif