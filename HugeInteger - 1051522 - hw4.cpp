// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a HugeInteger with size 0
HugeInteger::HugeInteger()
	: integer(1) {
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
	: integer((n > 0) ? n : 1) {
}

HugeInteger::HugeInteger(const HugeInteger &integerToCopy) {
	integer = integerToCopy.integer;
}

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger() {
}

const HugeInteger &HugeInteger::operator = (const HugeInteger &right) {
	integer = right.integer;
	return *this;
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==(const HugeInteger &right) const {
	return (integer == right.integer);
} // end function operator==

// function that tests if two HugeIntegers are not equal
bool HugeInteger::operator!=(const HugeInteger &right) const {
	return (integer != right.integer);
} // end function operator!=

bool HugeInteger::operator<(const HugeInteger &right) const {
	if (integer.size() > right.integer.size())	return false;
	if (integer.size() < right.integer.size())	return true;

	for (int i = integer.size() - 1; i >= 0; --i) {
		if (integer[i] > right.integer[i])	return false;
		if (integer[i] < right.integer[i])	return true;
	}
	return false;
}

// function to test if one HugeInteger is greater than another
bool HugeInteger::operator>(const HugeInteger &right) const {
	return (right < *this);
}

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::operator<=(const HugeInteger &right) const {
	return (*this == right || *this < right);
}

// function that tests if one HugeInteger is greater than or equal to another
bool HugeInteger::operator>=(const HugeInteger &right) const {
	return (!(*this < right));
}

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+(const HugeInteger &op2) const {
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	for (unsigned int i = 0; i < op1Size; i++)
		sum.integer[i] = integer[i];

	for (unsigned int i = 0; i < op2Size; i++)
		sum.integer[i] += op2.integer[i];

	for (unsigned int i = 0; i < sumSize - 1; i++)
		if (sum.integer[i] > 9) {
			sum.integer[i] -= 10;
			sum.integer[i + 1]++;
		}

	if (sum.integer[sumSize - 1] == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

HugeInteger HugeInteger::operator-(const HugeInteger &op2) const {
	HugeInteger sub(*this);

	for (unsigned int i = 0; i < op2.integer.size(); ++i)
		sub.integer[i] -= op2.integer[i];
	for (unsigned int i = 0; i < sub.integer.size(); ++i) {
		if (sub.integer[i] < 0) {
			sub.integer[i + 1]--;
			sub.integer[i] += 10;
		}
	}

	while (sub.integer[sub.integer.size() - 1] == 0 && sub.integer.size() > 1)
		sub.integer.resize(sub.integer.size() - 1);
	return sub;
}

HugeInteger HugeInteger::operator*(const  HugeInteger &op2) const {
	HugeInteger mul(integer.size() + op2.integer.size() + 5);

	for (unsigned int i = 0; i < integer.size(); ++i) {
		for (unsigned int j = 0; j < op2.integer.size(); ++j)
			mul.integer[i + j] += integer[i] * op2.integer[j];
	}
	for (unsigned int i = 0; i < mul.integer.size(); ++i) {
		if (mul.integer[i] >= 10) {
			mul.integer[i + 1] += mul.integer[i] / 10;
			mul.integer[i] %= 10;
		}
	}

	while (mul.integer[mul.integer.size() - 1] == 0 && mul.integer.size() > 1)
		mul.integer.resize(mul.integer.size() - 1);
	return mul;
}

HugeInteger HugeInteger::operator/(const HugeInteger &op2) const {
	HugeInteger div(1);

	if (*this == op2)
		div.integer[0] = 1;
	else if (*this < op2)
		div.integer[0] = 0;
	else {
		int k = integer.size() - op2.integer.size();
		HugeInteger buffur(integer.size()), remainder(*this);

		for (unsigned int i = 0; i < op2.integer.size(); ++i)
			buffur.integer[i + k] = op2.integer[i];
		
		if (remainder < buffur)
			buffur.divideByTen();
		else
			k++;

		div.integer.resize(k);
		while (k--) {
			while (remainder >= buffur) {
				remainder = remainder - buffur;
				div.integer[k]++;
			}
			buffur.divideByTen();
		}

		while (div.integer[div.integer.size() - 1] == 0 && div.integer.size() > 1)
			div.integer.resize(div.integer.size() - 1);
	}
	return div;
}

// modulus operator; HugeInteger % HugeInteger provided that the divisor is not equal to 0
HugeInteger HugeInteger::operator%(const HugeInteger &op2) const {
	HugeInteger quotient = (*this) / op2;
	HugeInteger remainder = (*this) - (quotient * op2);
	return remainder;
}

HugeInteger &HugeInteger::operator++() {
	helpIncrement();
	return *this;
}

HugeInteger HugeInteger::operator++(int) {
	HugeInteger temp(*this);
	helpIncrement();
	return temp;
}

HugeInteger &HugeInteger::operator--() {
	helpDecrement();
	return *this;
}

HugeInteger HugeInteger::operator--(int) {
	HugeInteger temp(*this);
	helpDecrement();
	return temp;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert(Vector vector) {
	unsigned int vectorSize = vector.size();
	integer.resize(vectorSize);
	for (unsigned int i = 0; i < vectorSize; i++)
		integer[vectorSize - i - 1] = vector[i];
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const {
	for (unsigned int i = 0; i < integer.size(); i++)
		if (integer[i] != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen() {
	for (unsigned int i = 1; i < integer.size(); i++)
		integer[i - 1] = integer[i];
	integer.resize(integer.size() - 1);
}

// function to help increment the integer
void HugeInteger::helpIncrement() {
	unsigned int integerSize = integer.size();
	integer[0]++;
	for (unsigned int i = 0; i < integerSize - 1; i++)
		if (integer[i] == 10) {
			integer[i] = 0;
			integer[i + 1]++;
		}

	if (integer[integerSize - 1] == 10) {
		integer.resize(integerSize + 1);
		integer[integerSize - 1] = 0;
		integer[integerSize]++;
	}
}

// function to help decrement the integer
void HugeInteger::helpDecrement() {
	if (isZero())
		return;

	integer[0]--;
	for (unsigned int i = 0; i < integer.size() - 1; i++) {
		if (integer[i] >= 0)
			break;

		integer[i] = 9;
		integer[i + 1]--;
	}
}

// overloaded output operator for class HugeInteger
ostream &operator<<(ostream &output, HugeInteger &hugeInteger) {
	for (int i = hugeInteger.integer.size() - 1; i >= 0; i--)
		output << hugeInteger.integer[i];

	return output; // enables cout << x << y;
}