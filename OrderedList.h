#pragma once

#include "List.h"
#include "StandardFunctors.h"

template <class T, class Order = IsLess>
class OrderedList {
public:
	OrderedList(unsigned int capacity = DEFAULT_LIST); // constructor for an empty ordered list that can hold  
	//  up to capacity Ts; default size is defined in List.h
	~OrderedList(); // destructor

	bool isEmpty() const; // returns true if the list is empty, and false otherwise  
	unsigned int getLength() const; // returns the number of Ts currently in the list

	T remove(unsigned int pos); // removes the element at location pos from the list, and returns it;
	// PRECONDITION: pos must be a valid position                                             
	T retrieve(unsigned int pos) const; // returns value at location pos without modifying it; 
	// PRECONDITION: pos must be a valid list position
	int insert(T item); // insert T at appropriate pos’n in the list and return this position

	int find(T key) const; // return pos’n of first occurrence of T, or -1 if T isn’t found
	int binarySearch(T key) const; // same as "find", but uses binary search instead of linear search

private:
	List<T> m_container;        // to hold the list of Ts
};

template <class T, class Order>
OrderedList<T, Order> ::OrderedList(unsigned int capacity) : m_container(capacity) {}

template <class T, class Order>
OrderedList<T, Order> :: ~OrderedList() {}

template <class T, class Order>
bool OrderedList<T, Order> ::isEmpty() const {
	return m_container.isEmpty();
}

template <class T, class Order>
unsigned int OrderedList<T, Order> ::getLength() const {
	return m_container.getLength();
}

template <class T, class Order>
T OrderedList<T, Order> ::remove(unsigned int pos) {
	return m_container.remove(pos);
}

template <class T, class Order>
T OrderedList<T, Order> ::retrieve(unsigned int pos) const {
	return m_container.retrieve(pos);
}

template <class T, class Order>
int OrderedList<T, Order> ::insert(T item) {
	unsigned int k;
	for (k = 1; k <= getLength(); k++)
	if (Order::compare(item, retrieve(k))) break;
	m_container.insert(k, item);
	return k;
}

template <class T, class Order>
int OrderedList<T, Order> ::find(T key) const {
	int k;
	for (k = 1; k <= getLength(); k++) {
		if (!(Order::compare(key, retrieve(k))) && !(Order::compare(retrieve(k), key)))
			return k;
	}
	return -1;
}

template <class T, class Order>
int OrderedList<T, Order> ::binarySearch(T key) const {
	int first = 1, last = m_container.getLength();
	while (first <= last) {
		int mid = (first + last) / 2;
		T val = retrieve(mid);
		if (Order::compare(key, val))   last = mid - 1;
		else if (Order::compare(val, key))  first = mid + 1;
		else                                   return  mid;
	}
	return -1;
}

