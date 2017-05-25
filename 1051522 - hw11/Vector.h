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


#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector {
	public:
	using iterator = VecIterator< T >;
	//   using reverse_iterator = ReverseVecIterator< T >;
	//   typedef VecIterator< T > iterator;
	//   typedef ReverseVecIterator< T > reverse_iterator;

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
	/*
	reverse_iterator rbegin() const; // Returns a iterator pointing to the last element in the vector.

	// Returns a iterator pointing to the theoretical element preceding the first element in the vector.
	reverse_iterator rend() const;
	*/
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

	iterator erase(iterator position);
	// Removes from the Vector a single element.   
	// This effectively reduces the container size by one.   
	// Relocates all the elements after the element erased to their new positions.

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
	resize(right.size());
	for (int i = 0; i < size(); ++i)
		myFirst[i] = right.myFirst[i];
	return *this;
}

template<typename T>
bool vector<T>::operator == (const vector<T> &right) const {
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

template<typename T>
void vector<T>::resize(unsigned int n) {
	if (n > capacity()) {
		vector temp(*this);

		ReAlloc(myFirst, n);
		for (int i = 0; i < temp.size(); ++i)
			myFirst[i] = temp.myFirst[i];
		myLast = myEnd = myFirst + n;
	}
	else if (n < capacity())
		myLast = myFirst + n;
}

template<typename T>
void vector<T>::push_back(const T val) {
	if (myLast == myEnd) {
		resize(size() + 1);
		myFirst[size() - 1] = val;
	}
	else
		*myLast++ = val;
}

template<typename T>
VecIterator<T> vector<T>::erase(iterator position) {
	auto it = position;
	for (++it; it != end(); ++it, ++position)
		*position = *it;
	return iterator(--myLast);
}
#endif