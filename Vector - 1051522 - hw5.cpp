// Member-function definitions for class Vector
#include <iostream>
using namespace std;
#include "Vector.h" // include definition of class Vector
#define ReAlloc(ptr, size) delete[] ptr; ptr = new T[size]();

// constructor; constructs a zero vector with size n
template< typename T >
Vector< T >::Vector(unsigned int n)
	: myFirst(new T[n]()),
	myLast(myFirst + n),
	myEnd(myLast) {
} // end Vector default constructor

template<typename T>
Vector<T>::Vector(const Vector<T> &vectorToCopy) {
	resize(vectorToCopy.capacity());
	for (unsigned int i = 0; i < vectorToCopy.size(); ++i)
		myFirst[i] = vectorToCopy.myFirst[i];
}

// destructor; destroys the Vector
template< typename T >
Vector< T >::~Vector() {
	delete[] myFirst;
} // end destructor

template<typename T>
const Vector<T> &Vector<T>::operator=(const Vector<T> &right) {
	resize(right.capacity());
	for (unsigned int i = 0; i < right.size(); ++i)
		myFirst[i] = right.myFirst[i];
	return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &right) const {
	if (size() != right.size())	return false;

	for (unsigned int i = 0; i < size(); ++i)
		if (myFirst[i] != right.myFirst[i])	return false;
	return true;
}

// inequality operator; returns opposite of == operator
template< typename T >
bool Vector< T >::operator!=(const Vector< T > &right) const {
	return !(*this == right); // invokes Vector::operator==
}

template< typename T >
T* Vector< T >::begin() const {
	return myFirst;
}

template< typename T >
T* Vector< T >::end() const {
	return myLast;
}

template< typename T >
unsigned int Vector< T >::size() const {
	return (myLast - myFirst);
}

template< typename T >
unsigned int Vector< T >::capacity() const {
	return (myEnd - myFirst);
}

template<typename T>
void Vector<T>::resize(unsigned int n) {
	if (n > capacity()) {
		Vector<T> temp(*this);
		ReAlloc(myFirst, n);
		for (unsigned int i = 0; i < temp.size(); ++i)
			myFirst[i] = temp.myFirst[i];
		myLast = myEnd = myFirst + n;
	}
	else
		myLast = myEnd = myFirst + n; //myLast = myFirst + n;
	return;
}

template<typename T>
void Vector<T>::push_back(const T val) {
	if (size() == capacity()) {
		resize(capacity() + 1);
		*(myLast - 1) = val;
	}
	else
		*myLast++ = val;
	return;
}