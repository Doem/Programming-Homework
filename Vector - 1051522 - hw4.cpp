// Member-function definitions for class Vector
#include <iostream>
using namespace std;
#include "Vector.h" // include definition of class Vector
#define ReAlloc(ptr, size) delete[] ptr; ptr = new int[size]();

// constructor; constructs a zero vector with size n
Vector::Vector(unsigned int n)
	: myFirst(new int[n]()),
	myLast(myFirst + n),
	myEnd(myLast) {
} // end Vector default constructor

Vector::Vector(const Vector &vectorToCopy) {
	ReAlloc(myFirst, vectorToCopy.capacity());
	for (unsigned int i = 0; i < vectorToCopy.size(); ++i)
		myFirst[i] = vectorToCopy.myFirst[i];
	myLast = myFirst + vectorToCopy.size();
	myEnd = myFirst + vectorToCopy.capacity();
}

// destructor; destroys the Vector
Vector::~Vector() {
	delete[] myFirst;
} // end destructor

const Vector &Vector::operator = (const Vector &right) {
	ReAlloc(myFirst, right.capacity());
	for (unsigned int i = 0; i < right.size(); ++i)
		myFirst[i] = right.myFirst[i];
	myLast = myFirst + right.size();
	myEnd = myFirst + right.capacity();
	return *this;
}

bool Vector::operator==(const Vector &right) const {
	if (size() != right.size())	return false;

	for (unsigned int i = 0; i < size(); ++i)
		if (myFirst[i] != right.myFirst[i])	return false;
	return true;
}

// inequality operator; returns opposite of == operator
bool Vector::operator!=(const Vector &right) const {
	return !(*this == right); // invokes Vector::operator==
}

int &Vector::operator[](unsigned int subscript) {
	return myFirst[subscript];
}

int Vector::operator[](unsigned int subscript) const {
	return myFirst[subscript];
}

unsigned int Vector::size() const {
	return (myLast - myFirst);
}

unsigned int Vector::capacity() const {
	return (myEnd - myFirst);
}

void Vector::resize(unsigned int n) {
	if (n > capacity()) {
		Vector temp(*this);
		ReAlloc(myFirst, n);
		for (unsigned int i = 0; i < temp.size(); ++i)
			myFirst[i] = temp.myFirst[i];
		myLast = myEnd = myFirst + n;
	}
	else
		myLast = myFirst + n;
	return;
}

void Vector::push_back(const int val) {
	if (size() == capacity()) {
		resize(capacity() + 1);
		*(myLast - 1) = val;
	}
	else 
		*myLast++ = val;
	return;
}