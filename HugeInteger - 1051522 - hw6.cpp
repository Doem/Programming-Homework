// Member-function definitions for class template HugeInteger

#include "HugeInteger 6-1.h" // include definition of class template HugeInteger
#include "List.cpp" // include member-function definitions for class template List 
#include "Vector.cpp" // include member-function definitions for class template Vector 

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

	for (auto it1 = integer.rbegin(), it2 = right.integer.rbegin(); it1 != integer.rend(); it1 = it1->prev, it2 = it2->prev) {
		if (it1->myVal > it2->myVal)	return false;
		if (it1->myVal < it2->myVal)	return true;
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
	unsigned int mySize = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (mySize >= op2Size) ? mySize + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);
	List< T >::iterator it1 = integer.begin();
	List< T >::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); it1 = it1->next, it3 = it3->next)
		it3->myVal = it1->myVal;

	List< T >::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); it2 = it2->next, it3 = it3->next)
		it3->myVal += it2->myVal;

	it3 = sum.integer.begin();
	for (; it3->next != sum.integer.end(); it3 = it3->next)
		if (it3->myVal > 9) {
			it3->myVal -= 10;
			(it3->next->myVal)++;
		}

	if (it3->myVal == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

template<typename T>
HugeInteger<T> HugeInteger<T>::operator-(const HugeInteger<T> &op2) const {
	HugeInteger sub(*this);

	for (auto it1 = sub.integer.begin(), it2 = op2.integer.begin(); it2 != op2.integer.end(); it1 = it1->next, it2 = it2->next) {
		if (it1->myVal < it2->myVal) {
			auto temp = it1->next;
			for (; temp->myVal == 0; temp = temp->next)
				temp->myVal = 9;
			temp->myVal--;
			it1->myVal += 10 - it2->myVal;
		}
		else
			it1->myVal -= it2->myVal;
	}

	while (sub.integer.rbegin()->myVal == 0 && sub.integer.size() > 1)
		sub.integer.resize(sub.integer.size() - 1);
	return sub;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator*(const  HugeInteger<T> &op2) const {
	HugeInteger mul(integer.size() + op2.integer.size() + 5);

	for (auto it1 = integer.begin(), it2 = mul.integer.begin(); it1 != integer.end(); it1 = it1->next, it2 = it2->next)
		for (auto it3 = op2.integer.begin(), it4 = it2; it3 != op2.integer.end(); it3 = it3->next, it4 = it4->next)
			it4->myVal += it1->myVal * it3->myVal;

	for (auto it1 = mul.integer.begin(); it1 != mul.integer.end(); it1 = it1->next) {
		if (it1->myVal >= 10) {
			it1->next->myVal += it1->myVal / 10;
			it1->myVal %= 10;
		}
	}

	while (mul.integer.rbegin()->myVal == 0 && mul.integer.size() > 1)
		mul.integer.resize(mul.integer.size() - 1);
	return mul;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator/(const HugeInteger<T> &op2) const {
	HugeInteger div(1);

	if (isZero() || *this < op2)
		div.integer.begin()->myVal = 0;
	else if (*this == op2)
		div.integer.begin()->myVal = 1;
	else {
		int k = integer.size() - op2.integer.size();
		HugeInteger buffer(integer.size()), remainder(*this);
		auto it1 = op2.integer.begin(), it2 = buffer.integer.begin(), it3 = div.integer.begin();

		for (int i = 0; i < k; ++i)
			it2 = it2->next;
		for (; it1 != op2.integer.end(); it1 = it1->next, it2 = it2->next)
			it2->myVal = it1->myVal;

		if (remainder < buffer)
			buffer.divideByTen();
		else
			k++;

		div.integer.resize(k);
		for (it3 = div.integer.rbegin(); --k >= 0; it3 = it3->prev) {
			while (buffer <= remainder) {
				remainder = remainder - buffer;
				(it3->myVal)++;
			}
			buffer.divideByTen();
		}
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

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(Vector< T > vector) {
	integer.resize(vector.size());
	List< T >::reverse_iterator it1 = integer.rbegin();
	Vector< T >::iterator it2 = vector.begin();
	for (; it2 != vector.end(); ++it2, it1 = it1->prev)
		it1->myVal = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const {
	for (List< T >::iterator it = integer.begin(); it != integer.end(); it = it->next)
		if (it->myVal != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen() {
	List< T >::iterator it = integer.begin();
	List< T >::iterator it2 = it;
	for (it2 = it2->next; it2 != integer.end(); it = it->next, it2 = it2->next)
		it->myVal = it2->myVal;
	integer.resize(integer.size() - 1);
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement() {
	List< T >::iterator it = integer.begin();
	(it->myVal)++;
	List< T >::iterator it2 = it;
	for (it2 = it2->next; it2 != integer.end(); it = it->next, it2 = it2->next)
		if (it->myVal == 10) {
			it->myVal = 0;
			(it2->myVal)++;
		}

	if (it->myVal == 10) {
		it->myVal = 0;
		integer.resize(integer.size() + 1);
		it = integer.end();
		it = it->prev;
		it->myVal = 1;
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement() {
	List< T >::iterator it = integer.begin();
	for (; it->myVal == 0; it = it->next)
		it->myVal = 9;

	(it->myVal)--;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger) {
	List< T >::reverse_iterator it = hugeInteger.integer.rbegin();
	for (; it != hugeInteger.integer.rend(); it = it->prev)
		output << it->myVal;

	return output; // enables cout << x << y;
}