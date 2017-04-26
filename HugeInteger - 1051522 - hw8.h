// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "list.h" // include definition of class template list

//#include <list> // include definition of class template list
//using std::list;

template< typename T >
class HugeInteger : public list< T > {
	template< typename T >
	friend ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger);
	public:
	HugeInteger(); // default constructor; construct a HugeInteger with mySize 0

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger &integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=(const HugeInteger &right); // assignment operator
	const HugeInteger &operator=(const list &right); // assignment operator

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

	bool isZero(); // return true if and only if all digits are zero

	private:
	HugeInteger(unsigned int n); // constructor; construct a zero HugeInteger with mySize n
	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// default constructor; construct a HugeInteger with mySize 0
template< typename T >
HugeInteger< T >::HugeInteger()
	: list(1) {
}

// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: list((n > 0) ? n : 1) {
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T > &integerToCopy)
	: list(integerToCopy) {
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
		list< T >::operator=(right);

	return *this; // enables x = y = z, for example
} // end function operator=

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=(const list< T > &right) {
	if (&right != this) // avoid self-assignment
		list< T >::operator=(right);

	return *this; // enables x = y = z, for example
} // end function operator=

template<typename T>
bool HugeInteger<T>::operator<(HugeInteger<T> &right) {
	if (size() != right.size())	return (size() < right.size());
	for (auto it1 = rbegin(), it2 = right.rbegin(); it1 != rend(); ++it1, ++it2)
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
	unsigned int op1Size = size();
	unsigned int op2Size = op2.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);
	iterator it1 = begin();
	iterator it3 = sum.begin();
	for (; it1 != end(); ++it1, ++it3)
		*it3 = *it1;

	iterator it2 = op2.begin();
	it3 = sum.begin();
	for (; it2 != op2.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.begin();
	iterator it4 = it3;
	for (++it4; it4 != sum.end(); ++it3, ++it4)
		if (*it3 > 9) {
			(*it3) -= 10;
			(*it4)++;
		}

	if (*it3 == 0)
		sum.pop_back();

	return sum;
} // end function operator+

template<typename T>
HugeInteger<T> HugeInteger<T>::operator-(HugeInteger<T> &op2) {
	HugeInteger<T> sub(*this);

	for (auto it1 = sub.begin(), it2 = op2.begin(); it2 != op2.end(); ++it1, ++it2) {
		if (*it1 < *it2) {
			auto temp = ++it1;
			for (; *temp == 0 && temp != sub.end(); ++temp)
				*temp = 9;
			--(*temp);
			*(--it1) += 10;
		}
		*it1 -= *it2;
	}

	while (*sub.rbegin() == 0 && sub.size() > 1)
		sub.pop_back();
	return sub;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator*(HugeInteger<T> &op2) {
	HugeInteger<T> mul(size() + op2.size());

	for (auto it1 = begin(), it2 = mul.begin(); it1 != end(); ++it1, ++it2)
		for (auto it3 = op2.begin(), it4 = it2; it3 != op2.end(); ++it3, ++it4)
			*it4 += (*it1) * (*it3);
	for (auto it = mul.begin(); it != mul.end(); ++it) {
		if (*it >= 10) {
			auto temp = ++it;
			*temp += *(--it) / 10;
			*it %= 10;
		}
	}
	
	while (*mul.rbegin() == 0 && mul.size() > 1)
		mul.pop_back();
	return mul;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator/(HugeInteger<T> &op2) {
	HugeInteger<T> div(1);

	if (*this < op2)
		*div.begin() = 0;
	else if (*this == op2)
		*div.begin() = 1;
	else {
		int k = size() - op2.size();
		HugeInteger<T> buffer(size()), remainder(*this);

		for (auto it1 = buffer.rbegin(), it2 = op2.rbegin(); it2 != op2.rend(); ++it1, ++it2)
			*it1 = *it2;

		if (remainder < buffer)
			buffer.divideByTen();
		else
			k++;

		div.resize(k);
		for (auto it = div.rbegin(); it != div.rend(); ++it) {
			while (remainder >= buffer) {
				remainder = remainder - buffer;
				++(*it);
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
	HugeInteger<T> temp(*this);
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
	HugeInteger<T> temp(*this);
	helpDecrement();
	return temp;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() {
	for (iterator it = begin(); it != end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen() {
	iterator it1 = begin();
	iterator it2 = it1;
	for (++it2; it2 != end(); ++it1, ++it2)
		*it1 = *it2;
	pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement() {
	iterator it = begin();
	(*it)++;
	iterator it2 = it;
	for (++it2; it2 != end(); ++it, ++it2)
		if (*it == 10) {
			*it = 0;
			(*it2)++;
		}

	if ((*it) == 10) {
		*it = 0;
		resize(size() + 1);
		it = end();
		--it;
		*it = 1;
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement() {
	iterator it = begin();
	for (; *it == 0; ++it)
		*it = 9;

	(*it)--;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger) {
	list< T >::reverse_iterator it = hugeInteger.rbegin();
	for (; it != hugeInteger.rend(); ++it)
		if (*it < 10)
			output << *it;

	return output; // enables cout << x << y;
}