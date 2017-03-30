// Member-function definitions for class Vector

#include "Vector.h" // include definition of class Vector
#define ReAlloc(ptr, size) delete[] ptr; ptr = new int[size]();
// constructor; constructs a zero vector with size n
Vector::Vector(unsigned int n)
	: mySize(n),
	myCapacity(n),
	ptr(new int[n]()) {
} // end Vector constructor

Vector::Vector(const Vector &vectorToCopy) {
	mySize = vectorToCopy.mySize;
	myCapacity = vectorToCopy.myCapacity;
	ReAlloc(ptr, myCapacity);
	for (unsigned int i = 0; i < mySize; ++i)
		ptr[i] = vectorToCopy.ptr[i];
}

// destructor; destroys the Vector
Vector::~Vector() {
	delete[] ptr;
} // end destructor

const Vector &Vector::assign(const Vector &right) {
	mySize = right.mySize;
	myCapacity = right.myCapacity;
	ReAlloc(ptr, myCapacity);
	for (unsigned int i = 0; i < mySize; ++i)
		ptr[i] = right.ptr[i];
	return *this;
}

bool Vector::equal(const Vector &right) const {
	if (mySize != right.mySize)	return false;

	for (unsigned int i = 0; i < mySize; ++i) 
		if (ptr[i] != right.ptr[i])	return false;
	return true;
}

// inequality operator; returns opposite of == operator
bool Vector::notEqual(const Vector &right) const {
	return (!equal(right));
}

int* Vector::begin() const {
	return ptr;
}

int* Vector::end() const {
	return ptr + mySize;
}

unsigned int Vector::size() const {
	return mySize;
}

void Vector::resize(unsigned int n) {
	if (n > myCapacity) {
		Vector temp(*this);
		myCapacity = mySize = n;
		ReAlloc(ptr, n);
		for (unsigned int i = 0; i < temp.mySize; ++i)
			ptr[i] = temp.ptr[i];
	}
	else
		mySize = n;
	return;
}

void Vector::push_back(const int val) {
	if (mySize == myCapacity) {
		resize(myCapacity + 1);
		ptr[mySize - 1] = val;
	}
	else
		ptr[mySize++ - 1] = val;
	return;
}