// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
	: integer(1) {
}

HugeInteger::HugeInteger(unsigned int n) {
	integer.resize(n);
}

HugeInteger::HugeInteger(const HugeInteger &integerToCopy) {
	integer.resize(integerToCopy.integer.size());
	for (Vector::iterator it1 = integer.begin(), it2 = integerToCopy.integer.begin(); it2 != integerToCopy.integer.end(); ++it1, ++it2)
		*it1 = *it2;
}

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger() {
} // end HugeInteger destructor

const HugeInteger &HugeInteger::assign(const HugeInteger &right) {
	integer.resize(right.integer.size());
	for (Vector::iterator it1 = integer.begin(), it2 = right.integer.begin(); it2 != right.integer.end(); it1++, it2++)
		*it1 = *it2;
	return *this;
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal(const HugeInteger &right) const {
	return (integer.equal(right.integer));
} // end function equal

// function that tests if two HugeIntegers are not equal
bool HugeInteger::notEqual(const HugeInteger &right) const {
	return (integer.notEqual(right.integer));
} // end function notEqual

bool HugeInteger::less(const HugeInteger &right) const {
	if (integer.size() > right.integer.size())	return false;
	if (integer.size() < right.integer.size())	return true;

	for (Vector::iterator it1 = integer.end() - 1, it2 = right.integer.end() - 1; it1 != integer.begin() - 1; --it1, --it2) {
		if (*it1 > *it2)	return false;
		if (*it1 < *it2)	return true;
	}
	return false;
}

// function to test if one HugeInteger is greater than another
bool HugeInteger::greater(const HugeInteger &right) const {
	return (right.less(*this));
} // end function greater

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual(const HugeInteger &right) const {
	return (equal(right) || less(right));
} // end function lessEqual

// function that tests if one HugeInteger is greater than or equal to another
bool HugeInteger::greaterEqual(const HugeInteger &right) const {
	return (!less(right));
} // end function greaterEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(const HugeInteger &op2) const {
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	Vector::iterator it1 = integer.begin();
	Vector::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	Vector::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	for (; it3 != sum.integer.end() - 1; ++it3)
		if (*it3 > 9) {
			(*it3) -= 10;
			(*(it3 + 1))++;
		}

	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function add

HugeInteger HugeInteger::subtract(const HugeInteger &op2) const {
	HugeInteger sub(*this);

	for (Vector::iterator it1 = sub.integer.begin(), it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it1, ++it2)
		*it1 -= *it2;
	for (Vector::iterator it = sub.integer.begin(); it != sub.integer.end(); ++it) {
		if (*it < 0) {
			(*(it + 1))--;
			*it += 10;
		}
	}

	for (Vector::iterator it = sub.integer.end() - 1; *it == 0 && sub.integer.size() > 1; --it)
		sub.integer.resize(sub.integer.size() - 1);
	return sub;
}

HugeInteger HugeInteger::multiply(const  HugeInteger &op2) const {
	unsigned int mulSize = integer.size() + op2.integer.size() + 5;
	HugeInteger mul(mulSize);
	Vector::iterator it3 = mul.integer.begin();

	for (Vector::iterator it1 = integer.begin(); it1 != integer.end(); ++it1) {
		for (Vector::iterator it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it2) {
			*(it3 + (it1 - integer.begin()) + (it2 - op2.integer.begin())) += *it1 * *it2;
		}
	}

	for (; it3 != mul.integer.end(); ++it3) {
		if (*it3 >= 10) {
			*(it3 + 1) += *it3 / 10;
			*it3 %= 10;
		}
	}

	for (it3 = mul.integer.end() - 1; *it3 == 0 && mul.integer.size() > 1; --it3)
		mul.integer.resize(mul.integer.size() - 1);
	return mul;
}

HugeInteger HugeInteger::divide(const HugeInteger &op2) const {
	HugeInteger div(integer.size());

	if (equal(op2)) {
		div.integer.resize(1);
		*div.integer.begin() = 1;
	}
	else if (less(op2)) {
		div.integer.resize(1);
		*div.integer.begin() = 0;
	}
	else {
		int k = integer.size() - op2.integer.size();
		HugeInteger buffur(integer.size()), remainder(integer.size());

		for (Vector::iterator it1 = integer.begin(), it2 = remainder.integer.begin(); it1 != integer.end(); ++it1, ++it2)
			*it2 = *it1;
		for (Vector::iterator it1 = op2.integer.begin(), it2 = buffur.integer.begin(); it1 != op2.integer.end(); ++it1, ++it2)
			*(it2 + k) = *it1;

		if (remainder.less(buffur))
			buffur.divideByTen();
		else
			k++;

		Vector::iterator it = div.integer.begin();
		while (k--) {
			while (remainder.greaterEqual(buffur)) {
				remainder.assign(remainder.subtract(buffur));
				(*(it + k))++;
			}
			buffur.divideByTen();
		}

		for (it = div.integer.end() - 1; *it == 0 && div.integer.size() > 1; --it)
			div.integer.resize(div.integer.size() - 1);
	}
	return div;
}

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus(const HugeInteger &op2) const {
	HugeInteger quotient = divide(op2);
	HugeInteger product = quotient.multiply(op2);
	HugeInteger remainder = subtract(product);
	return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert(Vector vector) {
	integer.resize(vector.size());
	Vector::iterator it1 = integer.end() - 1;
	Vector::iterator it2 = vector.begin();
	for (; it2 != vector.end(); --it1, ++it2)
		*it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const {
	for (Vector::iterator it = integer.begin(); it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen() {
	Vector::iterator it = integer.begin();
	Vector::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		*it = *it2;
	integer.resize(integer.size() - 1);
}

// overloaded output operator
void HugeInteger::output(ostream &outFile) {
	Vector::iterator it = integer.end() - 1;
	for (; it != integer.begin() - 1; --it)
		outFile << *it;
	outFile << endl;
} // end function output