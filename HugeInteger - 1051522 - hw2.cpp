// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger
#define ReAlloc(ptr,size) delete[] ptr; ptr = new int[size]();
// default constructor; construct a HugeInteger with size 0
HugeInteger::HugeInteger() {
	size = 1;
	capacity = 1;
	ptr = new int[1]();
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n) {
	size = n;
	capacity = n;
	ptr = new int[n]();
}

HugeInteger::HugeInteger(const HugeInteger &integerToCopy) {
	size = integerToCopy.size;
	capacity = integerToCopy.capacity;
	ReAlloc(ptr, capacity);
	for (unsigned int i = 0; i < size; i++)
		ptr[i] = integerToCopy.ptr[i];
}

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger() {
	delete[] ptr;
}

const HugeInteger &HugeInteger::assign(const HugeInteger &right) {
	size = right.size;
	capacity = right.capacity;
	ReAlloc(ptr, capacity);
	for (unsigned int i = 0; i < size; i++)
		ptr[i] = right.ptr[i];
	return *this;
}

bool HugeInteger::equal(const HugeInteger &right) const {
	if (size != right.size)	return false;

	for (int i = size - 1; i >= 0; i--)
		if (ptr[i] != right.ptr[i])	return false;
	return true;
}

// function that tests if two HugeIntegers are not equal
bool HugeInteger::notEqual(const HugeInteger &right) const {
	return (!equal(right));
} // end function notEqual

bool HugeInteger::less(const HugeInteger &right) const {
	if (size > right.size)	return false;
	if (size < right.size)	return true;

	for (int i = size - 1; i >= 0; i--) {
		if (ptr[i] > right.ptr[i])	return false;
		if (ptr[i] < right.ptr[i])	return true;
	}
	return false;
}

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual(const HugeInteger &right) const {
	return (equal(right) || less(right));
} // end function lessEqual

// function to test if one HugeInteger is greater than another
bool HugeInteger::greater(const HugeInteger &right) const {
	return (!lessEqual(right));
} // end function greater

// function that tests if one HugeInteger is greater than or equal to another
bool HugeInteger::greaterEqual(const HugeInteger &right) const {
	return (!less(right));
} // end function greaterEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(const HugeInteger &op2) const {
	unsigned int sumSize = (size >= op2.size) ? size + 1 : op2.size + 1;

	HugeInteger sum(sumSize);

	for (unsigned int i = 0; i < size; i++)
		sum.ptr[i] = ptr[i];

	for (unsigned int i = 0; i < op2.size; i++)
		sum.ptr[i] += op2.ptr[i];

	for (unsigned int i = 0; i < sum.size - 1; i++)
		if (sum.ptr[i] > 9) // determine whether to carry a 1
		{
			sum.ptr[i] -= 10; // reduce to 0-9
			sum.ptr[i + 1]++;
		}

	if (sum.ptr[sum.size - 1] == 0)
		sum.resize(sum.size - 1);

	return sum;
} // end function add

HugeInteger HugeInteger::subtract(const HugeInteger &op2) const {
	unsigned int subSize = (size < op2.size) ? size : op2.size;
	HugeInteger sub(*this);

	for (unsigned int i = 0; i < subSize; i++)
		sub.ptr[i] -= op2.ptr[i];
	for (unsigned int i = 0; i < sub.size; i++) {
		if (sub.ptr[i] < 0) {
			sub.ptr[i + 1]--;
			sub.ptr[i] += 10;
		}
	}

	while (sub.ptr[sub.size - 1] == 0 && sub.size > 1)
		sub.resize(sub.size - 1);
	return sub;
}

HugeInteger HugeInteger::multiply(const  HugeInteger &op2) const {
	unsigned int mulSize = size + op2.size + 5;
	HugeInteger mul(mulSize);

	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < op2.size; j++)
			mul.ptr[i + j] += ptr[i] * op2.ptr[j];
	}

	for (unsigned int i = 0; i < mul.size; i++) {
		if (mul.ptr[i] > 9) {
			mul.ptr[i + 1] += mul.ptr[i] / 10;
			mul.ptr[i] %= 10;
		}
	}

	while (mul.ptr[mul.size - 1] == 0 && mul.size > 1)
		mul.resize(mul.size - 1);
	return mul;
}

HugeInteger HugeInteger::divide(const HugeInteger &op2) const {
	HugeInteger div(size);

	if (equal(op2)) {
		div.size = 1;
		div.ptr[0] = 1;
	}
	else if (isZero() || less(op2)) {
		div.size = 1;
	}
	else {
		int k = size - op2.size;
		HugeInteger buffur(size), remainder(size);

		for (unsigned int i = 0; i < size; i++)
			remainder.ptr[i] = ptr[i];
		for (unsigned int i = 0; i < op2.size; i++)
			buffur.ptr[i + k] = op2.ptr[i];

		if (remainder.less(buffur))
			buffur.divideByTen();
		else
			k++;

		while (k--) {
			while (remainder.greaterEqual(buffur)) {
				remainder.assign(remainder.subtract(buffur));
				div.ptr[k]++;
			}
			buffur.divideByTen();
		}

		while (div.ptr[div.size - 1] == 0 && div.size > 1)
			div.resize(div.size - 1);
	}
	return div;
}

// modulus operator; HugeInteger % HugeInteger provided that the divisor is not equal to 0
HugeInteger HugeInteger::modulus(const HugeInteger &op2) const {
	HugeInteger quotient = divide(op2);
	HugeInteger product = quotient.multiply(op2);
	HugeInteger remainder = subtract(product);
	return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert(vector< int > &intVector) {
	resize(intVector.size());
	for (unsigned int i = 0; i < size; i++)
		ptr[size - i - 1] = intVector[i];
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const {
	for (unsigned int i = 0; i < size; i++)
		if (ptr[i] != 0)
			return false;

	return true;
}

void HugeInteger::resize(unsigned int n) {
	if (n == 0)	return;
	if (n < capacity) 
		size = n;
	else {
		HugeInteger temp(*this);

		size = n;
		capacity = n;
		ReAlloc(ptr, n);
		for (unsigned int i = 0; i < n; i++)
			ptr[i] = temp.ptr[i];
	}
	return;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen() {
	for (unsigned int i = 1; i < size; i++)
		ptr[i - 1] = ptr[i];
	resize(size - 1);
}

// overloaded output operator
void HugeInteger::output(ostream &outFile) const {
	for (int i = size - 1; i >= 0; i--)
		outFile << ptr[i];
	outFile << endl;
} // end function output