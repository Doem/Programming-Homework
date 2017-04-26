// ListNode class template definition
template< typename T >
struct ListNode {
	ListNode *next;
	T myVal;
	ListNode *prev;
}; // end class template ListNode

#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

// ListIterator class template definition
template< typename T >
class ListIterator {
	public:
	ListIterator(ListNode< T > *p = nullptr) // default constructor
		: ptr(p) {
	}

	ListIterator(const ListIterator &iteratorToCopy) // copy constructor
		: ptr(iteratorToCopy.ptr) {
	}

	~ListIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const ListIterator &operator=(const ListIterator &right) {
		if (&right != this) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	T& operator*() const // dereferencing operator
	{
		return ptr->myVal;
	}

	ListIterator& operator++() // prefix increment operator
	{
		ptr = ptr->next;
		return *this;
	}

	ListIterator& operator--() // prefix decrement operator
	{
		ptr = ptr->prev;
		return *this;
	}

	bool operator==(const ListIterator &right) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ListIterator &right) const // not equal to
	{
		return ptr != right.ptr;
	}

	private:
	ListNode< T > *ptr; // keep a pointer to list
}; // end class template ListIterator

#endif


#ifndef REVERSE_LIST_ITERATOR_H
#define REVERSE_LIST_ITERATOR_H

// ReverseListIterator class template definition
template< typename T >
class ReverseListIterator : public ListIterator< T > {
	public:
	ReverseListIterator(ListNode< T > *p = nullptr) // default constructor
		: ListIterator(p) {
	}

	ReverseListIterator(const ReverseListIterator &iteratorToCopy) // copy constructor
		: ListIterator(iteratorToCopy) {
	}

	~ReverseListIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const ReverseListIterator &operator=(const ReverseListIterator &right) {
		if (&right != this) // avoid self-assignment
			ListIterator< T >::operator=(right);
		return *this; // enables x = y = z, for example
	}

	ReverseListIterator& operator++() // prefix increment operator
	{
		ListIterator< T >::operator--();
		return *this;
	}

	ReverseListIterator& operator--() // prefix decrement operator
	{
		ListIterator< T >::operator++();
		return *this;
	}
}; // end class template ReverseListIterator

#endif


#ifndef LIST_H
#define LIST_H

// list class template definition
template< typename T >
class list {
	public:
	using iterator = ListIterator< T >;
	using reverse_iterator = ReverseListIterator< T >;
	//   typedef ListIterator< T > iterator;
	//   typedef ReverseListIterator< T > reverse_iterator;

	list(unsigned int n = 0); // Constructs an empty list container, with no elements.

	// Constructs a list container with a copy of each of the elements in listToCopy.
	list(const list &listToCopy);

	// Destroys all linked list elements, and deallocates all the storage allocated by the list container.
	~list();

	// Copies all the elements from "right" into the list container 
	const list &operator=(const list &right);

	bool operator==(const list &right) const;

	bool operator!=(const list &right) const;

	// Returns a pointer pointing to the first element in the list container.
	iterator begin() const;

	// Returns an pointer referring to the past-the-end element in the list container.
	iterator end() const;

	// Returns a pointer pointing to the last element in the list container
	// (i.e., its reverse beginning).
	reverse_iterator rbegin() const;

	// Returns a pointer pointing to the theoretical element preceding
	// the first element in the list container (which is considered its reverse end).
	reverse_iterator rend() const;

	void clear(); // Removes all elements from the list container (which are destroyed).

	unsigned int size() const; // Returns the number of elements in the list container.

	// Resizes the list container so that it contains n elements.
	// If n is smaller than the current list container mySize,
	// the content is reduced to its first n elements, removing those beyond.
	// If n is greater than the current list container mySize,
	// the content is expanded by inserting at the end as many elements as needed to reach a mySize of n.
	void resize(unsigned int n);

	// Inserts a new element at the beginning of the list, right before its current first element.
	// The content of val is copied (or moved) to the inserted element.
	// This effectively increases the list size by one.
	void push_front(const T val);

	// Removes the last element in the list,
	// effectively reducing the container size by one.
	void pop_back();

	private:
	unsigned int mySize = 0;         // the number of elements in the list container
	ListNode< T > *myHead = nullptr; // pointing to the past-the-end element in the list container
}; // end class template list

#endif


// Constructs an empty list container, with no elements.
template< typename T >
list< T >::list(unsigned int n)
	: mySize(n) {
	myHead = new ListNode< T >;
	myHead->myVal = T();
	myHead->prev = myHead->next = myHead;

	ListNode< T > *newNode = nullptr;
	if (n > 0) {
		for (unsigned int i = 0; i < n; i++) {
			newNode = new ListNode< T >;
			newNode->myVal = T();
			newNode->prev = myHead->prev;
			myHead->prev->next = newNode;
			myHead->prev = newNode;
		}
		newNode->next = myHead;
	}
}

template<typename T>
list<T>::list(const list<T> &listToCopy) {
	*this = listToCopy;
}

// Destroys all list container elements, and deallocates all the storage allocated by the list container.
template< typename T >
list< T >::~list() {
	clear();
	delete myHead;
}

template<typename T>
const list<T> &list<T>::operator=(const list<T> &right) {
	resize(right.mySize);
	for (auto it1 = begin(), it2 = right.begin(); it2 != right.end(); ++it1, ++it2)
		*it1 = *it2;
	return *this;
}

template<typename T>
bool list<T>::operator==(const list<T> &right) const {
	if (mySize != right.mySize)	return false;
	for (auto it1 = begin(), it2 = right.begin(); it1 != end(); ++it1, ++it2)
		if (*it1 != *it2)	return false;
	return true;
}

template< typename T >
bool list< T >::operator!=(const list< T > &right) const {
	return !(*this == right);
}

template< typename T >
ListIterator< T > list< T >::begin() const {
	return iterator(myHead->next);
}

template< typename T >
ListIterator< T > list< T >::end() const {
	return iterator(myHead);
}

template< typename T >
ReverseListIterator< T > list< T >::rbegin() const {
	return reverse_iterator(myHead->prev);
}

template< typename T >
ReverseListIterator< T > list< T >::rend() const {
	return reverse_iterator(myHead);
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void list< T >::clear() {
	if (mySize != 0) // the list is not empty
	{
		while (myHead->next != myHead) {
			myHead->next = myHead->next->next;
			delete myHead->next->prev;
		}

		myHead->prev = myHead;
		mySize = 0;
	}
}

template< typename T >
unsigned int list< T >::size() const {
	return mySize;
}

template<typename T>
void list<T>::resize(unsigned int n) {
	if (myHead == nullptr) {
		myHead = new ListNode<T>;
		myHead->myVal = T();
		myHead->next = myHead->prev = myHead;
	}

	if (n > mySize) {
		ListNode<T> *newNode = nullptr;
		for (unsigned int i = mySize; i < n; ++i) {
			newNode = new ListNode<T>;
			newNode->myVal = T();
			newNode->prev = myHead->prev;
			myHead->prev = myHead->prev->next = newNode;
		}
		newNode->next = myHead;
		mySize = n;
	}
	else {
		for (int i = (mySize - n); i > 0; --i)
			pop_back();
	}
	return;
}

template<typename T>
void list<T>::push_front(const T val) {
	auto *newNode = new ListNode<T>;
	newNode->myVal = val;
	newNode->next = myHead->next;
	newNode->prev = myHead;
	myHead->next = myHead->next->prev = newNode;
	++mySize;
	return;
}

template<typename T>
void list<T>::pop_back() {
	myHead->prev = myHead->prev->prev;
	delete myHead->prev->next;
	myHead->prev->next = myHead;
	--mySize;
	return;
}