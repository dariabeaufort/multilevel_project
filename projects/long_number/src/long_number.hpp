#pragma once

#include <iostream>

namespace rwh {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		
		public:
			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& other);
			LongNumber(LongNumber&& other);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& other);
			LongNumber& operator = (LongNumber&& other);
			
			bool operator == (const LongNumber& other) const;
			bool operator != (const LongNumber& other) const;
			bool operator > (const LongNumber& other) const;
			bool operator < (const LongNumber& other) const;
			bool operator >= (const LongNumber& other) const;
			bool operator <= (const LongNumber& other) const;
			
			LongNumber operator + (const LongNumber& other) const;
			LongNumber operator - (const LongNumber& other) const;
			LongNumber operator * (const LongNumber& other) const;
			LongNumber operator / (const LongNumber& other) const;
			LongNumber operator % (const LongNumber& other) const;
			
			bool is_negative() const noexcept;
			bool is_zero() const noexcept;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& other);
			friend std::string getNumberString(const LongNumber& number);
			
		private:
			int get_length(const char* const str) const noexcept;
	};
}