// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger 5-1.h" // include definition of class HugeInteger
#include "Vector.cpp" // include member-function definitions for class template Vector 

// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
	: integer(1) {
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n > 0) ? n : 1) {
}

template<typename T>
HugeInteger<T>::HugeInteger(const HugeInteger<T> &integerToCopy) {
	integer = integerToCopy.integer;
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger() {
}

template<typename T>
const HugeInteger<T> &HugeInteger<T>::operator=(const HugeInteger<T> &right) {
	integer = right.integer;
	return *this;
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(const HugeInteger< T > &right) const {
	return (integer == right.integer);
} // end function operator==

// function that tests if two HugeIntegers are not equal
template< typename T >
bool HugeInteger< T >::operator!=(const HugeInteger< T > &right) const {
	return (integer != right.integer);
} // end function operator!=

template<typename T>
bool HugeInteger<T>::operator<(const HugeInteger<T> &right) const {
	if (integer.size() > right.integer.size())	return false;
	if (integer.size() < right.integer.size())	return true;

	auto it1 = integer.begin(), it2 = right.integer.begin();
	for (int i = integer.size() - 1; i >= 0; --i) {
		if (it1[i] > it2[i])	return false;
		if (it1[i] < it2[i])	return true;
	}
	return false;
}

// function to test if one HugeInteger< T > is greater than another
template< typename T >
bool HugeInteger< T >::operator>(const HugeInteger< T > &right) const {
	return (right < *this);
}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger< T > &right) const {
	return (*this == right || *this < right);
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=(const HugeInteger< T > &right) const {
	return (!(*this < right));
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(const HugeInteger< T > &op2) const {
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	Vector< T >::iterator it1 = integer.begin();
	Vector< T >::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	Vector< T >::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
		if (*it3 > 9) {
			*it3 -= 10;
			(*(it3 + 1))++;
		}

	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

template<typename T>
HugeInteger<T> HugeInteger<T>::operator-(const HugeInteger<T> &op2) const {
	int *temp = new int[integer.size()]();
	HugeInteger sub(integer.size());
	auto it1 = integer.begin(), it2 = op2.integer.begin(), it3 = sub.integer.begin();

	for (unsigned int i = 0; i < integer.size(); ++i)
		temp[i] = it1[i];
	for (unsigned int i = 0; i < op2.integer.size(); ++i)
		temp[i] -= it2[i];
	for (unsigned int i = 0; i < integer.size(); ++i) {
		if (temp[i] < 0) {
			temp[i + 1]--;
			temp[i] += 10;
		}
		it3[i] = temp[i];
	}
	delete[] temp;
	for (it1 = sub.integer.end() - 1; *it1 == 0 && sub.integer.size() > 1; --it1)
		sub.integer.resize(sub.integer.size() - 1);
	return sub;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator*(const  HugeInteger<T> &op2) const {
	HugeInteger<T> mul(integer.size() + op2.integer.size() + 5);
	auto it1 = integer.begin(), it2 = op2.integer.begin(), it3 = mul.integer.begin();

	for (unsigned int i = 0; i < integer.size(); ++i)
		for (unsigned int j = 0; j < op2.integer.size(); ++j)
			it3[i + j] += it1[i] * it2[j];

	for (unsigned int i = 0; i < mul.integer.size(); ++i) {
		if (it3[i] >= 10) {
			it3[i + 1] += it3[i] / 10;
			it3[i] %= 10;
		}
	}

	for (it3 = mul.integer.end() - 1; *it3 == 0 && mul.integer.size() > 1; --it3)
		mul.integer.resize(mul.integer.size() - 1);
	return mul;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator/(const HugeInteger<T> &op2) const {
	HugeInteger div(1);

	if (isZero() || *this < op2)
		div.integer.begin()[0] = 0;
	else if (*this == op2)
		div.integer.begin()[0] = 1;
	else {
		int k = integer.size() - op2.integer.size();
		HugeInteger buffer(integer.size()), remainder(*this);
		auto it1 = buffer.integer.begin(), it2 = op2.integer.begin();

		for (unsigned int i = 0; i < op2.integer.size(); ++i)
			it1[i + k] = it2[i];

		if (remainder < buffer)
			buffer.divideByTen();
		else
			k++;

		div.integer.resize(k);
		while (k--) {
			while (buffer <= remainder) {
				remainder = remainder - buffer;
				div.integer.begin()[k]++;
			}
			buffer.divideByTen();
		}
		for (it1 = div.integer.end() - 1; *it1 == 0 && div.integer.size() > 1; --it1)
			div.integer.resize(div.integer.size() - 1);
	}
	return div;
}

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(const HugeInteger< T > &op2) const {
	HugeInteger quotient = (*this) / op2;
	HugeInteger remainder = (*this) - (quotient * op2);
	return remainder;
}

template<typename T>
HugeInteger<T> &HugeInteger<T>::operator++() {
	helpIncrement();
	return *this;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator++(int) {
	HugeInteger temp(*this);
	helpIncrement();
	return temp;
}

template<typename T>
HugeInteger<T> &HugeInteger<T>::operator--() {
	helpDecrement();
	return *this;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator--(int) {
	HugeInteger temp(*this);
	helpDecrement();
	return temp;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(Vector< T > vector) {
	integer.resize(vector.size());
	Vector< T >::iterator it1 = integer.end() - 1;
	Vector< T >::iterator it2 = vector.begin();
	for (; it2 != vector.end(); --it1, ++it2)
		*it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const {
	Vector< T >::iterator it = integer.begin();
	for (; it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen() {
	Vector< T >::iterator it = integer.begin() + 1;
	for (; it != integer.end(); ++it)
		*(it - 1) = *it;
	integer.resize(integer.size() - 1);
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement() {
	Vector< T >::iterator it = integer.begin();
	(*it)++;
	Vector< T >::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		if (*it == 10) {
			*it = 0;
			(*it2)++;
		}

	if ((*it) == 10) {
		*(it) = 0;
		integer.resize(integer.size() + 1);
		it = integer.end();
		--it;
		*it = 1;
	}
}

template<typename T>
void HugeInteger<T>::helpDecrement() {
	if (isZero())	return;
	if (integer.begin()[0] == 0) {
		for (unsigned int i = 1; i <= integer.size(); ++i) {
			if (integer.begin()[i - 1] == 0)
				integer.begin()[i - 1] = 9;
			else {
				integer.begin()[i - 1]--;
				break;
			}
		}
	}
	else
		integer.begin()[0]--;
	
	if (integer.begin()[integer.size() - 1] == 0 && integer.size() > 1)
		integer.resize(integer.size() - 1);
	return;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger) {
	Vector< T >::iterator it = hugeInteger.integer.end() - 1;
	for (; it != hugeInteger.integer.begin() - 1; --it)
		output << *it;

	return output; // enables cout << x << y;
}