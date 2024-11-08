#include "CNumber.h"
#include <iostream>
#include <cassert>

using namespace std;

CNumber::CNumber() : num_tab(nullptr), num_tab_len(0), is_negative(false), num_as_str("") {}

CNumber::CNumber(int value) {
    is_negative = (value < 0);
    int abs_value = (value < 0) ? -value : value;
    num_as_str = "";

    int temp = abs_value;
    num_tab_len = 0;
    while (temp > 0) {
        temp /= divide_val;
        num_tab_len++;
    }

    if (num_tab_len == 0) {
        num_tab_len = 1;
    }

    allocate(num_tab_len);

    temp = abs_value;
    for (int i = num_tab_len - 1; i >= 0; --i) {
        int digit = temp % divide_val;
        num_tab[i] = digit;
        num_as_str = char('0' + digit) + num_as_str;
        temp /= 10;
    }
}

CNumber::CNumber(const string& value) {
    is_negative = (value[0] == '-');
    num_as_str = is_negative ? value.substr(1) : value;

    num_tab_len = num_as_str.length();
    allocate(num_tab_len);

    for (int i = 0; i < num_tab_len; ++i) {
        num_tab[i] = num_as_str[i] - '0';
    }
}

CNumber::CNumber(const CNumber& other) {
    is_negative = other.is_negative;
    num_as_str = other.num_as_str;
    num_tab_len = other.num_tab_len;
    allocate(num_tab_len);
    for (int i = 0; i < num_tab_len; ++i) {
        num_tab[i] = other.num_tab[i];
    }
}

CNumber::~CNumber() {
    if (num_tab != nullptr) {
        delete[] num_tab;
        num_tab = nullptr;
    }
}

void CNumber::allocate(int length) {
    if (num_tab != nullptr) {
        delete[] num_tab;
    }

    if (length <= 0) {
        length = 1;
    }

    num_tab = new int[length]();
    num_tab_len = length;
}



void CNumber::copy(const CNumber& other) {
    is_negative = other.is_negative;
    num_as_str = other.num_as_str;
    allocate(other.num_tab_len);
    for (int i = 0; i < num_tab_len; ++i) {
        num_tab[i] = other.num_tab[i];
    }
}

bool CNumber::abs_compare(const CNumber& other) const {
    if (num_tab_len > other.num_tab_len) {
        return true;
    }
    else if (num_tab_len < other.num_tab_len) {
        return false;
    }
    else {
        for (int i = 0; i < num_tab_len; i++) {
            if (num_tab[i] > other.num_tab[i]) {
                return true;
            }
            else if (num_tab[i] < other.num_tab[i]) {
                return false;
            }
        }
        return false;
    }
}

CNumber& CNumber::operator=(const int value) {
    *this = CNumber(value);
    return *this;
}

CNumber& CNumber::operator=(const CNumber& other) {
    if (this != &other) {
        if (num_tab != nullptr) {
            delete[] num_tab;
        }
        is_negative = other.is_negative;
        num_as_str = other.num_as_str;
        num_tab_len = other.num_tab_len;
        allocate(num_tab_len);
        for (int i = 0; i < num_tab_len; ++i) {
            num_tab[i] = other.num_tab[i];
        }
    }
    return *this;
}

CNumber CNumber::operator+(const CNumber& other) const {
    CNumber result;

    if (is_negative && !other.is_negative) {
        CNumber temp = *this;
        temp.is_negative = false;
        result = other - temp;
    }

    else if (!is_negative && other.is_negative) {
        CNumber temp = other;
        temp.is_negative = false;
        result = *this - temp;
    }

    else {
        int max_len = max(num_tab_len, other.num_tab_len);
        int carry = 0;
        string result_str = "";

        for (int i = 0; i < max_len; ++i) {
            int digit1 = (i < num_tab_len) ? num_tab[num_tab_len - 1 - i] : 0;
            int digit2 = (i < other.num_tab_len) ? other.num_tab[other.num_tab_len - 1 - i] : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result_str = char((sum % divide_val) + '0') + result_str;
        }

        if (carry > 0) {
            result_str = char(carry + '0') + result_str;
        }

        result.num_as_str = result_str;
        result.num_tab_len = result_str.length();
        result.allocate(result.num_tab_len);

        for (int i = 0; i < result.num_tab_len; ++i) {
            result.num_tab[i] = result_str[i] - '0';
        }

        result.is_negative = is_negative && other.is_negative;
    }

    if (result.num_as_str == "0") {
        result.is_negative = false;
    }

    return result;
}




CNumber CNumber::operator-(const CNumber& other) const {
    CNumber result;

    if ((is_negative && !other.is_negative) || (!is_negative && other.is_negative)) {
        CNumber temp = other;
        temp.is_negative = !other.is_negative;
        result = *this + temp;
    }

    else {
        bool result_is_negative = false;

        if (abs_compare(other)) {
            result_is_negative = is_negative;
        }
        else {
            result_is_negative = !is_negative;
        }

        int carry = 0;
        string result_str = "";
        bool first_larger = abs_compare(other);

        for (int i = 0; i < max(num_tab_len, other.num_tab_len); i++) {
            int digit = (i < num_tab_len) ? num_tab[num_tab_len - 1 - i] : 0;
            int other_digit = (i < other.num_tab_len) ? other.num_tab[other.num_tab_len - 1 - i] : 0;

            if (!first_larger) swap(digit, other_digit);

            int sub = digit - other_digit - carry;
            if (sub < 0) {
                sub += divide_val;
                carry = 1;
            }
            else {
                carry = 0;
            }

            result_str = char(sub + '0') + result_str;
        }

        int non_zero_index = 0;
        while (non_zero_index < result_str.length() - 1 && result_str[non_zero_index] == '0') {
            non_zero_index++;
        }

        result.num_as_str = result_str.substr(non_zero_index);
        result.num_tab_len = result_str.length();
        result.allocate(result.num_tab_len);

        for (int i = 0; i < result.num_tab_len; i++) {
            result.num_tab[i] = result_str[i] - '0';
        }

        result.is_negative = result_is_negative;
    }

    if (result.num_as_str == "0") {
        result.is_negative = false;
    }

    return result;
}



CNumber CNumber::operator*(const CNumber& other) const {
    CNumber result;
    result.is_negative = (is_negative != other.is_negative);

    int max_len = num_tab_len + other.num_tab_len;
    int* result_digits = new int[max_len]();

    for (int i = num_tab_len - 1; i >= 0; i--) {
        int carry = 0;
        int to_mult_1 = num_tab[i];

        for (int j = other.num_tab_len - 1; j >= 0; j--) {
            int to_mult_2 = other.num_tab[j];
            int sum = to_mult_1 * to_mult_2 + result_digits[i + j + 1] + carry;

            carry = sum / 10;
            result_digits[i + j + 1] = sum % divide_val;
        }

        result_digits[i] += carry;
    }

    int start_index = 0;
    while (start_index < max_len - 1 && result_digits[start_index] == 0) {
        start_index++;
    }

    result.num_tab_len = max_len - start_index;
    result.allocate(result.num_tab_len);

    result.num_as_str = "";
    for (int i = start_index; i < max_len; i++) {
        result.num_tab[i - start_index] = result_digits[i];
        result.num_as_str += char(result_digits[i] + '0');
    }

    if (result.num_as_str == "0") {
        result.is_negative = false;
    }

    delete[] result_digits;

    return result;
}

CNumber CNumber::operator/(const CNumber& other) const {
    long long divisor = stoll(other.num_as_str);
    assert(divisor != 0 && "Error: Division by zero");

    string result_str;

    bool result_is_negative = (is_negative != other.is_negative);
    divisor = abs(divisor);

    long long remainder = 0;
    for (char digit : num_as_str) {
        remainder = remainder * mult_val + (digit - '0');
        result_str += (remainder / divisor) + '0';
        remainder %= divisor;
    }

    int non_zero_index = 0;
    while (non_zero_index < result_str.length() && result_str[non_zero_index] == '0') {
        non_zero_index++;
    }

    if (non_zero_index == result_str.length()) {
        result_str = "0";
    }

    else {
        result_str = result_str.substr(non_zero_index);
    }

    CNumber result(result_str);
    result.is_negative = (is_negative != other.is_negative);

    if (result.num_as_str == "0") {
        result.is_negative = false;
    }
    
    return result;
}

string CNumber::toStr() const {
    return is_negative ? "-" + num_as_str : num_as_str;
}