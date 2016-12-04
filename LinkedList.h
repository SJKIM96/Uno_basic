#pragma once
#include <assert.h>
template <class T>
class LinkedList   //singly-linked 
{
public:
	class Node { // singly-linked nodes (basic containers of a linked list)  
	public:
		Node(T val, Node * nx = nullptr) : value(val), next(nx) { }
		T  value;
		Node * next;
	};

public:
	LinkedList(); // construct an empty linked list
	LinkedList(const LinkedList &other);//copy constructor

	~LinkedList();     // destroy a linked list
	unsigned int size() const;  // return number of items in the list
	bool isEmpty() const; // true if list is empty, false otherwise
	void addHead(T item);  // adds item to front of list
	T removeHead();  // remove front node, and return the data T found in it;
	// PRECONDITION: list must not be empty already
	T retrieveHead() const; // returns the data T in front node; 
	// PRECONDITION: list must not be empty already
	void addTail(T item); // add item to end of list
	T removeTail(); // remove last node, and return the data T found in it;
	// PRECONDITION: list must not be empty already
	T retrieveTail() const; // return data T in last node; 
	// PRECONDITION: list must not be empty already
	void add(unsigned int n, T item); // Add a new node containing an item in position n on the list
	// PRECONDITION: n must be a valid list position (1<=n<=(size+1))
	T replace(unsigned int n, T item); // Replace the data stored in position n of the list with
	// item, and return the replaced item; 
	// PRECONDITION: n must be a valid list position (1<=n<=size)  
	T remove(unsigned int n); // Remove the node at position n from the list, and return the
	// item it contained; PRECONDITION: n must be a valid list position (1<=n<=size)
	T retrieve(unsigned int n) const; // Return the item value from the node in position n; 
	// PRECONDITION: n must be a valid list position (1<=n<=size)

	// WARNING: ONLY FOR TESTING IN LAB 8 !!!
	// The function below gives direct access to the Nodes 
	// Once a user gets direct access to list nodes,
	// internal list structure (e.g. linking) can be messed up.
	inline Node* getHead() const { return m_head; }

private:
	Node * m_head;
	Node * m_tail;
	unsigned int m_size;

public:
	class Iterator {// iterators are used for efficient traversal of linked lists
	private:
		Node* m_ptr;    // an iterator hides a pointer to node
	public:
		Iterator(Node* ptr) { m_ptr = ptr; }
		void operator++ () { m_ptr = m_ptr->next; } // for forward traversing, e,g, Iterator i=begin(); ... ++i;
		bool operator != (const Iterator& b) { return m_ptr != b.m_ptr; }
		T operator *() { return m_ptr->value; }
		T getValue() { return m_ptr->value; }
		void setValue(T val) { m_ptr->value = val; }
	};

	// linked list objects create forward-traversal iterators using the two functions below
	Iterator begin() { return Iterator(m_head); }
	Iterator end() { return Iterator(nullptr); }
};
// An implementation of templated class "LinkedList"


template <class T>
LinkedList<T> ::LinkedList()
: m_head(nullptr)
, m_tail(nullptr)
, m_size(0)
{}
// a quickly made copy constructor
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {

	if (other.m_size == 0) {
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
	else {
		m_size = other.m_size;
		m_head = new Node(other.m_head->value, nullptr);
		if (other.m_tail == nullptr) {
			m_tail = m_head;
		}
		else {
			Node * copyFrom = other.m_head->next;
			Node *nextNode = m_head;

			while (copyFrom != nullptr) {
				nextNode->next = new Node(copyFrom->value);
				copyFrom = copyFrom->next;
				nextNode = nextNode->next;
			}
			m_tail = nextNode;
		}

	}
}





template <class T>
LinkedList<T> :: ~LinkedList()
{
	Node * here = m_head, *nextNode;
	while (here != nullptr)
	{
		nextNode = here->next;
		delete here;
		here = nextNode;
	}
}

template <class T>
unsigned int LinkedList<T> ::size() const
{
	return m_size;
}

template <class T>
bool LinkedList<T> ::isEmpty() const
{
	return (m_size == 0);
}

template <class T>
void LinkedList<T> ::addHead(T item)
{
	m_head = new Node(item, m_head);
	if (m_tail == nullptr) m_tail = m_head;
	m_size++;
}

template <class T>
T LinkedList<T> ::removeHead()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeHead)"));
	Node * oldNode = m_head;
	T returnVal = m_head->value;
	m_head = m_head->next;
	if (m_head == nullptr) m_tail = nullptr;
	m_size--;
	delete oldNode;
	return returnVal;
}

template <class T>
T LinkedList<T>::retrieveHead() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveHead)"));
	return m_head->value;
}

template <class T>
void LinkedList<T> ::addTail(T item)
{
	if (isEmpty()) addHead(item);
	else
	{
		m_tail = m_tail->next = new Node(item);
		m_size++;
	}
}

template <class T>
T LinkedList<T> ::removeTail()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeTail)"));
	if (m_head == m_tail) return removeHead();
	T returnVal = m_tail->value;
	Node * preTail = m_head;
	while (preTail->next != m_tail)
		preTail = preTail->next;
	preTail->next = nullptr;
	delete m_tail;
	m_tail = preTail;
	m_size--;
	return returnVal;
}

template <class T>
T LinkedList<T> ::retrieveTail() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveTail)"));
	return m_tail->value;
}

template <class T>
void LinkedList<T> ::add(unsigned int n, T item)
{
	// PRECONDITION: n should be a valid position in the list
	assert(((n >= 1) && (n <= size() + 1) && "LinkedList index is out of bounds (in add)"));
	if (n == 1)          addHead(item);
	else if (n == (size() + 1)) addTail(item);
	else
	{
		Node * here = m_head;
		for (unsigned int k = 1; k < n - 1; k++)
			here = here->next;
		here->next = new Node(item, here->next);
		m_size++;
	}
}

template <class T>
T LinkedList<T> ::replace(unsigned int n, T item)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in replace)"));
	T returnValue;
	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++)
		here = here->next;
	returnValue = here->value;
	here->value = item;
	return returnValue;
}

template <class T>
T LinkedList<T> ::remove(unsigned int n)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in remove)"));
	if (n == 1) return removeHead();
	if (n == size()) return removeTail();

	Node * here = m_head;
	for (unsigned int k = 1; k < n - 1; k++)
		here = here->next;
	Node * kill = here->next;
	T returnVal = kill->value;
	here->next = kill->next;
	delete kill;
	m_size--;
	return returnVal;
}

template <class T>
T LinkedList<T> ::retrieve(unsigned int n) const
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in retrieve)"));
	if (n == 1) return retrieveHead();
	if (n == size()) return retrieveTail();
	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++) here = here->next;
	return here->value;
}