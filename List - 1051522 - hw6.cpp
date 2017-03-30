// Member-function definitions for class template List

#include "List.h" // include definition of class template List

// Constructs an empty list container, with no elements.
template< typename T >
List< T >::List(unsigned int n)
	:mySize(n) {
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
List<T>::List(const List<T> &listToCopy) {
	resize(listToCopy.mySize);
	for (auto it1 = begin(), it2 = listToCopy.begin(); it2 != listToCopy.end(); it1 = it1->next, it2 = it2->next)
		it1->myVal = it2->myVal;
}

// Destroys all list container elements, and deallocates all the storage allocated by the list container.
template< typename T >
List< T >::~List() {
	clear();
	delete myHead;
}

template<typename T>
const List<T> &List<T>::operator=(const List<T> &right) {
	resize(right.mySize);
	for (auto it1 = begin(), it2 = right.begin(); it2 != right.end(); it1 = it1->next, it2 = it2->next)
		it1->myVal = it2->myVal;
	return *this;
}

template<typename T>
bool List<T>::operator==(const List<T> &right) const {
	if (mySize != right.mySize)	return false;
	for (auto it1 = begin(), it2 = right.begin(); it1 != end(); it1 = it1->next, it2 = it2->next)
		if (it1->myVal != it2->myVal)	return false;
	return true;
}

template< typename T >
bool List< T >::operator!=(const List< T > &right) const {
	return !(*this == right);
}

template< typename T >
ListNode< T >* List< T >::begin() const {
	return myHead->next;
}

template< typename T >
ListNode< T >* List< T >::end() const {
	return myHead;
}

template< typename T >
ListNode< T >* List< T >::rbegin() const {
	return myHead->prev;
}

template< typename T >
ListNode< T >* List< T >::rend() const {
	return myHead;
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void List< T >::clear() {
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
unsigned int List< T >::size() const {
	return mySize;
}

template<typename T>
void List<T>::resize(unsigned int n) {
	if (n > mySize) {
		ListNode<T> *newNode = nullptr;
		for (unsigned int i = mySize; i < n; ++i) {
			newNode = new ListNode<T>;
			newNode->myVal = T();
			newNode->prev = myHead->prev;
			myHead->prev = myHead->prev->next = newNode;
		}
		newNode->next = myHead;
	}
	else {
		for (unsigned int i = 0; i < mySize - n; ++i) {
			myHead->prev = myHead->prev->prev;
			delete myHead->prev->next;
		}
		myHead->prev->next = myHead;
	}
	mySize = n;
	return;
}