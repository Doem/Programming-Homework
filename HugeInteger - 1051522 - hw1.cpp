// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger 

// default constructor
HugeInteger::HugeInteger() {
} // end HugeInteger default constructor

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n) {
	size = (n <= capacity) ? n : capacity;
} // end HugeInteger constructor

bool HugeInteger::equal(HugeInteger right) {
	if (size != right.size)	return false;

	for (int i = size - 1; i >= 0; i--)
		if (elems[i] != right.elems[i])	return false;
	return true;
}

// function that tests if two HugeIntegers are not equal
bool HugeInteger::notEqual(HugeInteger right) {
	return (!equal(right));
} // end function notEqual

bool HugeInteger::less(HugeInteger right) {
	if (size < right.size)	return true;
	if (size > right.size)	return false;

	for (int i = size - 1; i >= 0; i--) {
		if (elems[i] < right.elems[i])	return true;
		if (elems[i] > right.elems[i])	return false;
	}
	return false;
}

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual(HugeInteger right) {
	return (equal(right) || less(right));
} // end function lessEqual

// function to test if one HugeInteger is greater than another
bool HugeInteger::greater(HugeInteger right) {
	return (!lessEqual(right));
} // end function greater

// function that tests if one HugeInteger is greater than or equal to another
bool HugeInteger::greaterEqual(HugeInteger right) {
	return (!less(right));
} // end function greaterEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(HugeInteger op2) {
	unsigned int sumSize = (size >= op2.size) ? size + 1 : op2.size + 1;
	HugeInteger sum(sumSize);

	for (unsigned int i = 0; i < size; i++)
		sum.elems[i] = elems[i];

	for (unsigned int i = 0; i < op2.size; i++)
		sum.elems[i] += op2.elems[i];

	for (unsigned int i = 0; i < sum.size - 1; i++)
		if (sum.elems[i] > 9) // determine whether to carry a 1
		{
			sum.elems[i] -= 10; // reduce to 0-9
			sum.elems[i + 1]++;
		}

	if (sum.elems[sum.size - 1] == 0 && sum.size > 1)
		sum.size--;

	return sum;
} // end function add

HugeInteger HugeInteger::subtract(HugeInteger op2) {
	unsigned int subSize = (size >= op2.size) ? size : op2.size;
	HugeInteger sub(subSize);

	for (unsigned int i = 0; i < subSize; i++) {
		sub.elems[i] += elems[i] - op2.elems[i];

		if (sub.elems[i] < 0) {
			sub.elems[i] += 10;
			sub.elems[i + 1]--;
		}
	}

	while (sub.elems[sub.size - 1] == 0 && sub.size > 1)
		sub.size--;

	return sub;
}

HugeInteger HugeInteger::multiply(HugeInteger op2) {
	HugeInteger mul(size + op2.size + 5);

	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < op2.size; j++)
			mul.elems[i + j] += elems[i] * op2.elems[j];
	}

	for (unsigned int i = 0; i < mul.size; i++) {
		if (mul.elems[i] > 9) {
			mul.elems[i + 1] += mul.elems[i] / 10;
			mul.elems[i] %= 10;
		}
	}

	while (mul.elems[mul.size - 1] == 0 && mul.size > 1)
		mul.size--;

	return mul;
}

HugeInteger HugeInteger::divide(HugeInteger op2) {
	HugeInteger div(size);

	if (equal(op2)) {
		div.size = 1;
		div.convert("1");
	}
	else if (less(op2)) {
		div.size = 1;
		div.convert("0");
	}
	else {
		int k = size - op2.size;
		HugeInteger buff(size), remainder(size);

		for (int i = 0; i < size; i++)
			remainder.elems[i] = elems[i];
		for (int i = 0; i < op2.size; i++)
			buff.elems[k + i] = op2.elems[i];

		if (remainder.less(buff))
			buff.divideByTen();
		else
			k++;

		while (k--) {
			while (remainder.greaterEqual(buff)) {
				remainder = remainder.subtract(buff);
				div.elems[k]++;
			}
			buff.divideByTen();
		}

		while (div.elems[div.size - 1] == 0 && div.size > 1)
			div.size--;
	}
	return div;
}

HugeInteger HugeInteger::modulus(HugeInteger op2) {
	return subtract(op2.multiply(divide(op2)));
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert(char numericString[]) {
	size = strlen(numericString);
	for (unsigned int i = 0; i < size; i++)
		elems[size - i - 1] = numericString[i] - '0';
} // end function convert

// test if a HugeInteger is zero
bool HugeInteger::isZero() {
	for (unsigned int i = 0; i < size; i++)
		if (elems[i] != 0)
			return false;
	return true;
} // end function isZero

// HugeInteger /= 10
void HugeInteger::divideByTen() {
	for (unsigned int i = 1; i < size; i++)
		elems[i - 1] = elems[i];
	elems[size - 1] = 0;
	size--;
} // end function divideByTen

// overloaded output operator
void HugeInteger::output(ostream &outFile) {
	for (int i = size - 1; i >= 0; i--)
		outFile << elems[i];
	outFile << endl;
} // end function output