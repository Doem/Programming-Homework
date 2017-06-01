#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H
#define ReAlloc(ptr, size) delete[] ptr; ptr = new T[size]();

// VecIterator class template definition
template< typename T >
class VecIterator {
	//template< typename T > friend class vector;
	public:
	VecIterator(T *p = 0) // default constructor
		: ptr(p) {
	}

	VecIterator(const VecIterator &iteratorToCopy) // copy constructor
		: ptr(iteratorToCopy.ptr) {
	}

	~VecIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const VecIterator &operator=(const VecIterator &right) {
		if (&right != this) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	T& operator*() const // dereferencing operator
	{
		return *ptr;
	}

	T* operator->() const // class member access operator
	{
		return ptr;
	}

	VecIterator& operator++() // prefix increment operator
	{
		++ptr;
		return *this;
	}

	VecIterator& operator--() // predecrement an iterator
	{
		--ptr;
		return *this;
	}

	bool operator==(const VecIterator &right) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=(const VecIterator &right) const // not equal to
	{
		return ptr != right.ptr;
	}

	bool operator<=(const VecIterator &right) const // not equal to
	{
		return ptr <= right.ptr;
	}

	private:
	T *ptr; // keep a pointer to vector
}; // end class template VecIterator

#endif


#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector {
	public:
	//   using iterator = VecIterator< T >;
	typedef VecIterator< T > iterator;

	vector(unsigned int n = 0); // Constructor; Constructs a zero vector with size n

	// Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
	vector(const vector &vectorToCopy);

	~vector(); // Destroys the vector.

	const vector &operator=(const vector &right); // assignment operator

	bool operator==(const vector &right) const;   // equal to

	bool operator!=(const vector &right) const;   // not equal to
	// subscript operator for non-const objects returns modifiable lvalue
	T &operator[](unsigned int subscript);

	// subscript operator for const objects returns rvalue
	T operator[](unsigned int subscript) const;

	iterator begin() const; // Returns a pointer pointing to the first element in the vector.
	// If the vector is empty, the returned pointer shall not be dereferenced.

	// Returns an pointer pointing to the past-the-end element in the vector.
	// The past-the-end element is the theoretical element that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	iterator end() const;

	// Returns the number of elements in the vector.
	// This is the number of actual objects held in the vector,
	// which is not necessarily equal to its storage capacity.
	unsigned int size() const;

	// Returns the size of the storage space currently allocated for the vector,
	// expressed in terms of elements.
	unsigned int capacity() const;

	// Adds a new element at the end of the vector, after its current last element.
	// The content of val is copied to the new element.
	// This effectively increases the vector size by one,
	// which causes an automatic reallocation of the allocated storage space
	// if and only if the new vector size surpasses the current vector capacity.
	void push_back(const T val);

	// Removes the last element in the vector,
	// effectively reducing the container size by one.
	void pop_back();

	private:
	T *myFirst = nullptr;
	T *myLast = nullptr;
	T *myEnd = nullptr;
}; // end class template vector


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector(unsigned int n)
	: myFirst(n == 0 ? nullptr : new T[n]()),
	myLast(n == 0 ? nullptr : myFirst + n),
	myEnd(n == 0 ? nullptr : myLast) {
} // end vector default constructor

template<typename T>
vector<T>::vector(const vector<T> &vectorToCopy) {
	ReAlloc(myFirst, vectorToCopy.size());
	for (int i = 0; i < vectorToCopy.size(); ++i)
		myFirst[i] = vectorToCopy.myFirst[i];
	myLast = myEnd = myFirst + vectorToCopy.size();
}

// destructor; destroys the vector
template< typename T >
vector< T >::~vector() {
	if (myFirst != nullptr)
		delete[] myFirst;
} // end destructor

template<typename T>
const vector<T> &vector<T>::operator=(const vector<T> &right) {
	ReAlloc(myFirst, right.size());
	for (int i = 0; i < right.size(); ++i)
		myFirst[i] = right.myFirst[i];
	myLast = myEnd = myFirst + right.size();
	return *this;
}

template<typename T>
bool vector<T>::operator==(const vector<T> &right) const {
	if (size() != right.size())	return false;
	for (int i = 0; i < size(); ++i)
		if (myFirst[i] != right.myFirst[i])	return false;
	return true;
}

// inequality operator; returns opposite of == operator
template< typename T >
bool vector< T >::operator!=(const vector< T > &right) const {
	return !(*this == right); // invokes vector::operator==
}

template<typename T>
T &vector<T>::operator[](unsigned int subscript) {
	return myFirst[subscript];
}

template<typename T>
T vector<T>::operator[](unsigned int subscript) const {
	return myFirst[subscript];
}

template< typename T >
VecIterator< T > vector< T >::begin() const {
	return iterator(myFirst);
}

template< typename T >
VecIterator< T > vector< T >::end() const {
	return iterator(myLast);
}

template< typename T >
unsigned int vector< T >::size() const {
	return (myLast - myFirst);
}

template< typename T >
unsigned int vector< T >::capacity() const {
	return (myEnd - myFirst);
}


template <typename T>
void vector<T>::push_back(const T val) {
	if (size() == capacity()) {
		vector temp(*this);

		ReAlloc(myFirst, temp.size() + 1);
		for (int i = 0; i < temp.size(); ++i)
			myFirst[i] = temp.myFirst[i];
		myFirst[temp.size()] = val;
		myLast = myEnd = myFirst + temp.size() + 1;
	}
	else
		*myLast++ = val;
}

template <typename T>
void vector<T>::pop_back() {
	if (size() > 0)
		--myLast;
}
#endif