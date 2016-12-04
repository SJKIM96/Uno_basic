#pragma once
#include <assert.h>
const int DEFAULT_LIST = 200;

template <class T>
class List {
public:
	List(unsigned int capacity = DEFAULT_LIST); // constructor for an empty list of specified capacity; 
	// if capacity is not supplied, the default size is used 
	~List(); // destructor

	bool isEmpty() const; // returns true if the list is empty, and false otherwise  
	bool isFull() const; // returns true if the list is full, and false otherwise 
	unsigned int getLength() const; // returns the number of Ts currently in the list

	void insert(unsigned int pos, T item); // inserts T into the list at location pos; 
	// PRECONDITION: pos is between 1 and getLength()+1
	T remove(unsigned int pos); // removes the element at location pos from the list, and returns it;
	// PRECONDITION: the list is not empty, and pos is between 1 and getLength();
	T retrieve(unsigned int pos) const; // find the element stored at location pos in the list and return it; 
	// PRECONDITION: the list is not empty, and pos is between 1 and getLength();
	T replace(unsigned int pos, T item); // replace the element at location pos in the list with T,
	// and return the element that was displaced; 
	// PRECONDITION: the list is not empty, and pos is between 1 and getLength();
	void append(T item) { return insert(getLength() + 1, item); } // adds an T at the back of the list
	T back() const { return retrieve(getLength()); } // retrieves an T from the back of the list
	T popBack() { return remove(getLength()); } // removes an T from the back of the list
	void swap(unsigned int i, unsigned int j); // swaps two Ts located in positions i and j

	template <class Equality> // "find" uses linear search to return position of the first T identical to "key",
	int find(T key) const; // returns -1 if no identical T is found. Extra template argument <class Equality> 
	// must be a functor like "IsEqual" or "IsEqualDeref" defined in StandardFunctors.h. 
	// EXAMPLE: call lst.find<IsEqual>(4) returns location of integer 4 inside List<int> lst;  
	template <class Order> // these two functions sort (via either "selection" or "insertion" sorting algorithms)
	void selectionSort();  // content of the list based on specified "Order". Additional template argument <class Order> 
	// should be a comparison functor like "IsLess" or "IsGreaterDeref" from StandardFunctors.h             
	template <class Order> // EXAMPLE: can be called in main() as     a.selectionSort<IsLess>();
	void insertionSort();  // to sort integers in List<int> a; in increasing order


private:
	T * m_container; // pointer to array to hold the list
	unsigned int m_max_capacity; // maximum capacity of the list
	unsigned int m_size;    // number of Ts currently in the list
	unsigned int translate(unsigned int pos) const; // converts a list position to the corresponding array index
	void replaceContainer(); // private function replaces the underlying array with one that holds
	// the same values as the original, but has double the capacity

public:
	class Iterator {
	private:
		T* _ptr;

	public:
		Iterator(T* ptr) :_ptr(ptr){}
		Iterator operator++() { Iterator i = *this; _ptr++; return i; } // for forward traversing, e,g, Iterator i=begin(); ... ++i;
		bool operator != (const Iterator& b) { return _ptr != b._ptr; }
		T operator *() { return *_ptr; }
		T getValue() { return *_ptr; }
		void setValue(T val) { *_ptr = val; }
	};

	// linked list objects create forward-traversal iterators using the two functions below
	Iterator begin() { return Iterator(&m_container[0]); }
	Iterator end() { return Iterator(&m_container[m_size]); }
};
template <class T>
List<T> ::List(unsigned int capacity) {
	m_max_capacity = capacity;
	m_container = new T[m_max_capacity];
	m_size = 0;
}

template <class T>
List<T> :: ~List() {
	delete[] m_container;
}

template <class T>
bool List<T> ::isEmpty() const {
	return (m_size == 0);
}

template <class T>
bool List<T> ::isFull() const {
	return false;
}

template <class T>
unsigned int List<T> ::getLength() const {
	return m_size;
}

template <class T>
void List<T> ::insert(unsigned int pos, T item) {
	// PRECONDITION: pos is between 1 and m_size+1
	assert((pos >= 1) && (pos <= m_size + 1) && "List index is out of bounds (in insert)");
	if (m_size == m_max_capacity) replaceContainer();
	for (unsigned int k = m_size; k >= pos; k--)
		m_container[translate(k + 1)] = m_container[translate(k)];
	m_container[translate(pos)] = item;
	m_size++;
}

template <class T>
T List<T> ::remove(unsigned int pos) {
	// PRECONDITION: the list is not empty, and pos is between 1 and m_size
	assert((pos >= 1) && (pos <= m_size) && "List index is out of bounds (in remove)");
	T returnValue = m_container[translate(pos)];
	for (unsigned int k = pos + 1; k <= m_size; k++)
		m_container[translate(k - 1)] = m_container[translate(k)];
	m_size--;
	return returnValue;
}

template <class T>
T List<T> ::retrieve(unsigned int pos) const {
	// PRECONDITION: the list is not empty, and pos is between 1 and m_size
	assert((pos >= 1) && (pos <= m_size) && "List index is out of bounds (in retrieve)");
	return m_container[translate(pos)];
}

template <class T>
T List<T> ::replace(unsigned int pos, T item) {
	// PRECONDITION: the list is not empty, and pos is between 1 and m_size
	assert((pos >= 1) && (pos <= m_size) && "List index is out of bounds (in replace)");
	T returnVal = m_container[translate(pos)];
	m_container[translate(pos)] = item;
	return returnVal;
}

template <class T>
void List<T> ::swap(unsigned i, unsigned j) {
	// PRECONDITION: indexes iand j should be within the range of the list
	assert((i >= 1) && (i <= m_size) && (j >= 1) && (j <= m_size) && "List index is out of bounds (in swap)");
	if (i == j) return;
	T temp = m_container[translate(i)];
	m_container[translate(i)] = m_container[translate(j)];
	m_container[translate(j)] = temp;
}

template <class T>
unsigned int List<T> ::translate(unsigned int pos) const {
	return pos - 1;
}

template <class T>
void List<T> ::replaceContainer() {
	T * newList;
	newList = new T[2 * m_max_capacity];
	for (unsigned int k = 0; k < m_size; k++)
		newList[k] = m_container[k];
	m_max_capacity = 2 * m_max_capacity;
	delete[] m_container;
	m_container = newList;
}

template <class T> template <class Equality>
int List<T> ::find(T key) const
{
	for (unsigned int i = 1; i <= getLength(); i++) if (Equality::compare(retrieve(i), key)) return i;
	return -1;
}

template <class T> template <class Order>
void List<T> ::selectionSort() {
	unsigned minSoFar, i, k;
	for (i = 1; i < getLength(); i++) { // unsorted part starts at  i
		minSoFar = i;
		for (k = i + 1; k <= getLength(); k++) { //searching for minimum T in the unsorted part
			if (Order::compare(retrieve(k), retrieve(minSoFar)))
				minSoFar = k;
		}
		swap(i, minSoFar);    // moving min T into the end of the sorted part
	}
}

template <class T> template <class Order>
void List<T>::insertionSort() {
	unsigned i, k;
	for (i = 2; i <= getLength(); i++) { // moving i-th T into the sorted part of container
		for (k = i - 1; k > 0; k--) {
			if (Order::compare(retrieve(k), retrieve(k + 1)))   break;
			else swap(k, k + 1);         // NOTE: i-th T is shifted "down" until the right spot
		}                              // inside sorted part [1 <= k <= (i-1)] is found
	}
}

