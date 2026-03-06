#include "long_number.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

using rwh::LongNumber;

LongNumber::LongNumber() {
    length = 1;
    sign = 1;

    numbers = new int[length];
    numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) {
    this->length = length;
    this->sign = sign;

    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = 0;
    }
}

LongNumber::LongNumber(const char* const str) {
    int start = 0;

    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else {
        sign = 1;
    }

    length = get_length(str + start);

    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = str[start + i] - '0';
    }

    if (length == 1 && numbers[0] == 0) {
        sign = 1;
    }
}

LongNumber::LongNumber(const LongNumber& other) {
    length = other.length;
    sign = other.sign;

    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = other.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& other) {
    numbers = other.numbers;
    length = other.length;
    sign = other.sign;

    other.numbers = nullptr;
    other.length = 0;
    other.sign = 1;
}

LongNumber::~LongNumber() {
    delete[] numbers;
    numbers = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
    delete[] numbers;

    int start = 0;

    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else {
        sign = 1;
    }

    length = get_length(str + start);

    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = str[start + i] - '0';
    }

    if (length == 1 && numbers[0] == 0) {
        sign = 1;
    }

    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& other) {
    if (this == &other) {
        return *this;
    }

    delete[] numbers;

    length = other.length;
    sign = other.sign;

    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = other.numbers[i];
    }

    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& other) {
   if (this == &other) {
        return *this;
    }

    delete[] numbers;

    numbers = other.numbers;
    length = other.length;
    sign = other.sign;

    other.numbers = nullptr;
    other.length = 0;
    other.sign = 1;

    return *this;
}

bool LongNumber::operator == (const LongNumber& other) const {
    if (sign != other.sign) {
        return false;
    }

    if (length != other.length) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (numbers[i] != other.numbers[i]) {
            return false;
        }
    }
    return true;
}

bool LongNumber::operator != (const LongNumber& other) const {
    return !(*this == other);
}

bool LongNumber::operator > (const LongNumber& other) const {
	if (sign > other.sign) {
        return true;
    }
    if (sign < other.sign) {
        return false;
    }

    if (sign == 1) {
        if (length > other.length) {
            return true;
        }

        if (length < other.length) {
            return false;
        }
    } else {
        if (length > other.length) {
            return false;
        }

        if (length < other.length) {
            return true;
        }
    }

    for (int i = 0; i < length; i++) {
        if (numbers[i] > other.numbers[i]) {
            return sign == 1;
        }

        if (numbers[i] < other.numbers[i]) {
            return sign == -1;
        }
    }
    return false;
}

bool LongNumber::operator < (const LongNumber& other) const {
    return (other > *this) && !(*this == other);
}

bool LongNumber::operator >= (const LongNumber& other) const {
    return (*this > other) || (*this == other);
}

bool LongNumber::operator <= (const LongNumber& other) const {
    return (*this < other) || (*this == other);
}

LongNumber LongNumber::operator + (const LongNumber& other) const {
    if (sign != other.sign) {
        LongNumber a = *this;
        LongNumber b = other;

        a.sign = 1;
        b.sign = 1;

        bool a_is_bigger = (a > b);
        bool result_negative = false;

        if (!a_is_bigger) {
            LongNumber temp = a;
            a = b;
            b = temp;
            result_negative = true;
        }

        int* result_array = new int[a.length]();

        for (int i = 0; i < a.length; i++) {
            result_array[i] = a.numbers[i];
        }

        int borrow = 0;
        int position_a = a.length - 1;
        int position_b = b.length - 1;

        while (position_a >= 0) {
            int digit_a = result_array[position_a];
            int digit_b = (position_b >= 0) ? b.numbers[position_b] : 0;

            int substract = digit_a - digit_b - borrow;

            if (substract < 0) {
                substract += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result_array[position_a] = substract;

            position_a--;
            position_b--;
        }

        int start = 0;
        while (start < a.length - 1 && result_array[start] == 0) {
            start++;
        }

        LongNumber result(a.length - start, 1);

        for (int i = 0; i < result.length; i++) {
            result.numbers[i] = result_array[start + i];
        }

        if (result.length == 1 && result.numbers[0] == 0) {
            result.sign = 1;
        } else {
            if (sign == -1) {
                result_negative = !result_negative;
            }
            result.sign = result_negative ? -1 : 1;
        }

        delete[] result_array;

        return result;
    }

    int max_length = std::max(length, other.length) + 1;
    int* result_array = new int[max_length]();

    int carry = 0;

    int position_a = length - 1;
    int position_b = other.length - 1;
    int position_res = max_length - 1;

    while (position_a >= 0 || position_b >= 0 || carry > 0) {
        int sum = carry;
        if (position_a >= 0) {
            sum += numbers[position_a];
            position_a--;
        }
        if (position_b >= 0) {
            sum += other.numbers[position_b];
            position_b--;
        }

        result_array[position_res] = sum % 10;
        carry = sum / 10;

        position_res--;
    }

    int start = 0;

    while (start < max_length && result_array[start] == 0) {
        start++;
    }

    if (start == max_length) {
        delete[] result_array;
        return LongNumber();
    }

    LongNumber result(max_length - start, sign);

    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = result_array[start + i];
    }

    delete[] result_array;

    return result;
}

LongNumber LongNumber::operator - (const LongNumber& other) const {
    LongNumber negative_other = other;
    negative_other.sign = -negative_other.sign;
	
    return *this + negative_other;
}

LongNumber LongNumber::operator * (const LongNumber& other) const {
    int result_length = length + other.length;
    int* result_array = new int[result_length]();
    
    for (int i = length - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = other.length - 1; j >= 0; j--) {
            int sum = numbers[i] * other.numbers[j] + result_array[i + j + 1] + carry;
            result_array[i + j + 1] = sum % 10;
            carry = sum / 10;
        }
        result_array[i] += carry;
    }

    int start = 0;
    while (start < result_length - 1 && result_array[start] == 0) start++;

    LongNumber result(result_length - start, sign * other.sign);
    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = result_array[start + i];
    }

    delete[] result_array;
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& other) const {
 if (this->is_zero() || other.is_zero()) {
        throw std::runtime_error("Error: division by zero");
    }

    LongNumber dividend = *this;
    LongNumber divisor = other;

    dividend.sign = 1;
    divisor.sign = 1;

    if (dividend < divisor) return LongNumber("0");

    LongNumber quotient(dividend.length, 1);
    LongNumber remainder("0");

    for (int i = 0; i < dividend.length; i++) {
        remainder = remainder * LongNumber("10");

        LongNumber digit(1, 1);
        digit.numbers[0] = dividend.numbers[i];
        remainder = remainder + digit;

        int q_digit = 0;
        for (int q = 0; q <= 9; q++) {
            LongNumber product = divisor * LongNumber(std::to_string(q).c_str());
            if (product <= remainder) {
                q_digit = q;
            } else {
                break;
            }
        }

        quotient.numbers[i] = q_digit;
        LongNumber product = divisor * LongNumber(std::to_string(q_digit).c_str());
        remainder = remainder - product;
    }

    int start = 0;
    while (start < quotient.length - 1 && quotient.numbers[start] == 0) start++;

    LongNumber result(quotient.length - start, this->sign * other.sign);
    for (int i = 0; i < result.length; i++) {
        result.numbers[i] = quotient.numbers[start + i];
    }

    if (result.length == 1 && result.numbers[0] == 0)
        result.sign = 1;

    return result;
}

LongNumber LongNumber::operator % (const LongNumber& other) const {
    return *this - (*this / other) * other;
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
}

bool LongNumber::is_zero() const noexcept {
    return (length == 1) && (numbers[0] == 0);
}

int LongNumber::get_length(const char* const str) const noexcept {
    int len = 0;
    while (str[len] != '\0') len++;

    int start = 0;
    while (start < len - 1 && str[start] == '0') start++;

    return len - start;
}

namespace rwh {
	std::ostream& operator << (std::ostream &os, const LongNumber& other) {
        if (other.sign == -1) os << '-';
        for (int i = 0; i < other.length; i++) {
            os << other.numbers[i];
        }
        return os;
	}
	
	std::string getNumberString(const LongNumber& number) {
    std::string result = "";

    if (number.sign == -1) result += "-";

    for (int i = 0; i < number.length; i++) {
        result += std::to_string(number.numbers[i]);
    }

    return result;
}
}