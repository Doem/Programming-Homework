#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H
#define ReAlloc(ptr, size) delete[] ptr; ptr = new T[size]();
// VecIterator class template definition
template< typename T >
class VecIterator {
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

	private:
	T *ptr; // keep a pointer to vector
}; // end class template VecIterator

#endif


#ifndef REVERSE_VEC_ITERATOR_H
#define REVERSE_VEC_ITERATOR_H

// ReverseVecIterator class template definition
template< typename T >
class ReverseVecIterator {
	public:
	ReverseVecIterator(T *p = 0) // default constructor
		: ptr(p) {
	}

	ReverseVecIterator(const ReverseVecIterator &iteratorToCopy) // copy constructor
		: ptr(iteratorToCopy.ptr) {
	}

	~ReverseVecIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const ReverseVecIterator &operator=(const ReverseVecIterator &right) {
		if (&right != this) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	T& operator*() const // dereferencing operator
	{
		return *ptr;
	}

	ReverseVecIterator& operator++() // prefix increment operator
	{
		--ptr;
		return *this;
	}

	ReverseVecIterator& operator--() // predecrement an iterator
	{
		++ptr;
		return *this;
	}

	bool operator==(const ReverseVecIterator &right) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ReverseVecIterator &right) const // not equal to
	{
		return ptr != right.ptr;
	}

	private:
	T *ptr; // keep a pointer to vector
}; // end class template ReverseVecIterator

#endif


#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector {
	public:
	using iterator = VecIterator< T >;
	using reverse_iterator = ReverseVecIterator< T >;
	//   typedef VecIterator< T > iterator;
	//   typedef ReverseVecIterator< T > reverse_iterator;

	vector(unsigned int n = 0); // Constructor; Constructs a zero vector with size n

	// Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
	vector(const vector &vectorToCopy);

	~vector(); // Destroys the vector.

	const vector &operator=(const vector &right); // assignment operator

	bool operator==(const vector &right) const;   // equal to

	bool operator!=(const vector &right) const;   // not equal to

	iterator begin() const; // Returns a pointer pointing to the first element in the vector.
	// If the vector is empty, the returned pointer shall not be dereferenced.

	// Returns an pointer pointing to the past-the-end element in the vector.
	// The past-the-end element is the theoretical element that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	iterator end() const;

	reverse_iterator rbegin() const; // Returns a iterator pointing to the last element in the vector.

	// Returns a iterator pointing to the theoretical element preceding the first element in the vector.
	reverse_iterator rend() const;

	// Returns the number of elements in the vector.
	// This is the number of actual objects held in the vector,
	// which is not necessarily equal to its storage capacity.
	unsigned int size() const;

	// Returns the size of the storage space currently allocated for the vector,
	// expressed in terms of elements.
	unsigned int capacity() const;

	// Resizes the vector so that it contains n elements.
	// If n is smaller than the current vector size,
	// the content is reduced to its first n elements, removing those beyond.
	// If n is greater than the current vector size,
	// the content is expanded by inserting at the end as many elements as needed to reach a size of n.
	// The new elements are initialized as 0.
	// If n is also greater than the current vector capacity,
	// an automatic reallocation of the allocated storage space takes place.
	void resize(unsigned int n);

	// Adds a new element at the end of the vector, after its current last element.
	// The content of val is copied to the new element.
	// This effectively increases the vector size by one,
	// which causes an automatic reallocation of the allocated storage space
	// if and only if the new vector size surpasses the current vector capacity.
	void push_back(const T val);

	private:
	T *myFirst = nullptr;
	T *myLast = nullptr;
	T *myEnd = nullptr;
}; // end class template vector

#endif


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector(unsigned int n)
	: myFirst(n == 0 ? nullptr : new T[n]()),
	myLast(n == 0 ? nullptr : myFirst + n),
	myEnd(n == 0 ? nullptr : myLast) {
} // end vector default constructor

template<typename T>
vector<T>::vector(const vector<T> &vectorToCopy) {
	resize(vectorToCopy.size());
	for (unsigned int i = 0; i < vectorToCopy.size(); ++i)
		myFirst[i] = vectorToCopy.myFirst[i];
}

// destructor; destroys the vector
template< typename T >
vector< T >::~vector() {
	if (myFirst != nullptr)
		delete[] myFirst;
} // end destructor

template<typename T>
const vector<T> &vector<T>::operator=(const vector<T> &right) {
	resize(right.size());
	for (unsigned int i = 0; i < right.size(); ++i)
		myFirst[i] = right.myFirst[i];
	return *this;
}

template<typename T>
bool vector<T>::operator==(const vector<T> &right) const {
	if (size() != right.size())	return false;
	for (unsigned int i = 0; i < size(); ++i)
		if (myFirst[i] != right.myFirst[i])	return false;
	return true;
}

// inequality operator; returns opposite of == operator
template< typename T >
bool vector< T >::operator!=(const vector< T > &right) const {
	return !(*this == right); // invokes vector::operator==
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
ReverseVecIterator< T > vector< T >::rbegin() const {
	return reverse_iterator(myLast - 1);
}

template< typename T >
ReverseVecIterator< T > vector< T >::rend() const {
	return reverse_iterator(myFirst - 1);
}

template< typename T >
unsigned int vector< T >::size() const {
	return (myLast - myFirst);
}

template< typename T >
unsigned int vector< T >::capacity() const {
	return (myEnd - myFirst);
}

template<typename T>
void vector<T>::resize(unsigned int n) {
	if (n > capacity()) {
		vector temp(*this);
		ReAlloc(myFirst, n);
		for (unsigned int i = 0; i < temp.size(); ++i)
			myFirst[i] = temp.myFirst[i];
		myLast = myEnd = myFirst + n;
	}
	else {
		for (unsigned int i = size(); i < n; ++i)
			myFirst[i] = 0;
		myLast = myFirst + n;
	}
	return;
}

template<typename T>
void vector<T>::push_back(const T val) {
	if (size() == capacity()) {
		resize(capacity() + 1);
		*(myLast - 1) = val;
	}
	else
		*myLast++ = val;
	return;
}