// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "vector.h" // include definition of class template vector
#include "list.h" // include definition of class template list

//#include <vector> // include definition of class template vector
//#include <list> // include definition of class template list
//using std::vector;
//using std::list;

template< typename T >
class HugeInteger {
	template< typename T >
	friend ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger);
	public:
	HugeInteger(); // default constructor; construct a HugeInteger with mySize 0

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger &integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=(const HugeInteger &right); // assignment operator

	bool operator==(HugeInteger &right); // less than or equal to
	bool operator!=(HugeInteger &right); // greater than or equal to
	bool operator<(HugeInteger &right);  // less than
	bool operator>(HugeInteger &right);  // greater than
	bool operator<=(HugeInteger &right); // less than or equal to
	bool operator>=(HugeInteger &right); // greater than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(HugeInteger &op2);

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(HugeInteger &op2);

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(HugeInteger &op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger &op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger &op2);

	HugeInteger &operator++(); // prefix increment operator

	HugeInteger operator++(int); // postfix increment operator

	HugeInteger &operator--(); // prefix decrement operator

	HugeInteger operator--(int); // postfix decrement operator

	void convert(vector< unsigned int > v); // convert a vector of decimal digits into a HugeInteger
	bool isZero(); // return true if and only if all digits are zero

	private:
	T integer;

	HugeInteger(unsigned int n); // constructor; construct a zero HugeInteger with mySize n
	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// default constructor; construct a HugeInteger with mySize 0
template< typename T >
HugeInteger< T >::HugeInteger()
	: integer(1) {
}

// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n > 0) ? n : 1) {
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T > &integerToCopy)
	: integer(integerToCopy.integer) {
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger() {
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=(const HugeInteger< T > &right) {
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger< T > &right) {
	return (integer == right.integer);
} // end function operator==

// function that tests if two HugeIntegers are not equal
template< typename T >
bool HugeInteger< T >::operator!=(HugeInteger< T > &right) {
	return (integer != right.integer);
} // end function operator!=

template<typename T>
bool HugeInteger<T>::operator<(HugeInteger<T> &right) {
	if (integer.size() != right.integer.size())	return (integer.size() < right.integer.size());
	for (auto it1 = integer.rbegin(), it2 = right.integer.rbegin(); it1 != integer.rend(); ++it1, ++it2)
		if (*it1 != *it2)	return (*it1 < *it2);
	return false;
}

// function to test if one HugeInteger< T > is greater than another
template< typename T >
bool HugeInteger< T >::operator>(HugeInteger< T > &right) {
	return (right < *this);
}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T > &right) {
	return (*this == right || *this < right);
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=(HugeInteger< T > &right) {
	return (!(*this < right));
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger< T > &op2) {
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);
	T::iterator it1 = integer.begin();
	T::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	T::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	T::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
		if (*it3 > 9) {
			(*it3) -= 10;
			(*it4)++;
		}

	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

template<typename T>
HugeInteger<T> HugeInteger<T>::operator-(HugeInteger<T> &op2) {
	HugeInteger sub(*this);

	for (auto it1 = sub.integer.begin(), it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it1, ++it2) {
		if (*it1 < *it2) {
			auto temp = ++it1;
			for (; *temp == 0 && temp != sub.integer.end(); ++temp)
				*temp = 9;
			(*temp)--;
			*(--it1) += 10 - *it2;
		}
		else
			*it1 -= *it2;
	}

	while (*sub.integer.rbegin() == 0 && sub.integer.size() > 1)
		sub.integer.resize(sub.integer.size() - 1);
	return sub;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator*(HugeInteger<T> &op2) {
	HugeInteger mul(integer.size() + op2.integer.size() + 5);

	for (auto it1 = integer.begin(), it2 = mul.integer.begin(); it1 != integer.end(); ++it1, ++it2)
		for (auto it3 = op2.integer.begin(), it4 = it2; it3 != op2.integer.end(); ++it3, ++it4)
			*it4 += *it1 * *it3;
	for (auto it1 = mul.integer.begin(); it1 != mul.integer.end(); ++it1) {
		if (*it1 >= 10) {
			auto it2 = ++it1;
			*it2 += *(--it1) / 10;
			*it1 %= 10;
		}
	}

	while (*mul.integer.rbegin() == 0 && mul.integer.size() > 1)
		mul.integer.resize(mul.integer.size() - 1);
	return mul;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator/(HugeInteger<T> &op2) {
	HugeInteger div(1);

	if (*this < op2 || isZero())
		*div.integer.begin() = 0;
	else if (*this == op2)
		*div.integer.begin() = 1;
	else {
		int k = integer.size() - op2.integer.size();
		HugeInteger buffer(integer.size()), remainder(*this);
		auto it1 = buffer.integer.begin(), it2 = op2.integer.begin();

		for (int i = 0; i < k; ++i)
			++it1;
		for (; it2 != op2.integer.end(); ++it1, ++it2)
			*it1 = *it2;

		if (remainder < buffer)
			buffer.divideByTen();
		else
			k++;

		div.integer.resize(k);
		for (auto it1 = div.integer.rbegin(); --k >= 0; ++it1) {
			while (remainder >= buffer) {
				remainder = remainder - buffer;
				(*it1)++;
			}
			buffer.divideByTen();
		}
	}
	return div;
}

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > &op2) {
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
void HugeInteger< T >::convert(vector< unsigned int > v) {
	integer.resize(v.size());
	T::reverse_iterator it1 = integer.rbegin();
	vector< unsigned int >::iterator it2 = v.begin();
	for (; it2 != v.end(); ++it2, ++it1)
		*it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() {
	for (T::iterator it = integer.begin(); it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen() {
	T::iterator it1 = integer.begin();
	T::iterator it2 = it1;
	for (++it2; it2 != integer.end(); ++it1, ++it2)
		*it1 = *it2;
	integer.resize(integer.size() - 1);
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement() {
	T::iterator it = integer.begin();
	(*it)++;
	T::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		if (*it == 10) {
			*it = 0;
			(*it2)++;
		}

	if ((*it) == 10) {
		*it = 0;
		integer.resize(integer.size() + 1);
		it = integer.end();
		--it;
		*it = 1;
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement() {
	T::iterator it = integer.begin();
	for (; *it == 0; ++it)
		*it = 9;

	(*it)--;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger) {
	T::reverse_iterator it = hugeInteger.integer.rbegin();
	for (; it != hugeInteger.integer.rend(); ++it)
		output << *it;

	return output; // enables cout << x << y;
}