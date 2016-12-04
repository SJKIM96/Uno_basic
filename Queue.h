#pragma once
#include "LinkedList.h"


template <class T>

class Queue {
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	int size()const { return m_container.size(); }
	void enqueue(T k);
	T dequeue();
	T peek()const;
private:
	LinkedList<T> m_container;

};
template <class T>
Queue<T>::Queue() {}

template <class T>
Queue<T>::~Queue() {}

template <class T>
bool Queue<T>::isEmpty() const {
	return m_container.isEmpty();
}
template <class T>
void Queue<T>::enqueue(T  k) {
	m_container.addTail(k);
}

template <class T>
T Queue<T>::dequeue() {
	return m_container.removeHead();
}

template <class T>
T Queue<T>::peek() const {
	return m_container.retrieveHead();
}