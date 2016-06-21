#pragma once
#define LINKEDLIST_H
#ifdef LINKEDLIST_H

#include <string>
#include <conio.h>
#include <iostream>

using std::string;
using std::to_string;
using std::cout;
using std::endl;


template <typename T>
class LinkedList {

private:
	class Node {
		friend class LinkedList<T>;
	private:
		T dataT;
		Node* pNext;
		Node* pPrev;
	public:
		Node(T d, Node *n = NULL, Node *p = NULL) : dataT(d), pNext(n), pPrev(p){}
	};

public:
	Node* pFirst;
	Node* pLast;

	LinkedList();
	LinkedList(const LinkedList<T>& src);
	~LinkedList();

	void sort();
	bool isEmpty();
	void insertFirst(T);
	void insertLast(T);
	void removeFirst();
	void removeLast();
	bool removeElement(T);
	bool insertAfter(T, T);
	void displayForward();
	void displayBackward();
	Node* search(T);

private:
	void setTail();
	void swapNodes(T*, T*);
	Node* partition(Node*, Node*);
	void quickSort(Node*, Node*);

};

template<typename T>
inline Node::Node(T _data) : dataT(_data), pNext(NULL), pPrev(NULL) {
}


template <typename T>
inline void Node::getDisplay() {
	//this seems like a terrible idea atm
	cout << to_string(dataT) << " ";
}

template<typename T>
LinkedList<T>::LinkedList() : pFirst(NULL), pLast(NULL) {} //constructor

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& src) : pFirst(NULL), pLast(NULL){
	Node * curr = src.pFirst;
	while (curr != NULL){
		this->insertLast(curr->data);
		curr = curr->pNext;
	}
}

template<typename T>
LinkedList<T>::~LinkedList() {
	Node* pCurrent = pFirst;
	while (pCurrent != NULL) {
		Node* pOldCurr = pCurrent;
		pCurrent = pCurrent->pNext;
		delete pOldCurr;
	}
}

template<typename T>
inline bool LinkedList<T> ::isEmpty() {
	return pFirst == NULL;
}

template<typename T>
inline void LinkedList<T>::insertFirst(T data) {
	Node* pNewNode = new Node(data);
	if (isEmpty())
		pLast = pNewNode;
	else
		pFirst->pPrev = pNewNode;
	pNewNode->pNext = pFirst;
	pFirst = pNewNode;
}

template<typename T>
inline void LinkedList<T>::insertLast(T data) {
	Node* pNewNode = new Node(data);
	if (isEmpty())
		pFirst = pNewNode;
	else {
		pLast->pNext = pNewNode;
		pNewNode->pPrev = pLast;
	}
	pLast = pNewNode;
}
template<typename T>
inline void LinkedList<T>::removeFirst() {
	Node* pTemp = pFirst;
	if (pFirst->pNext == NULL)
		pLast = NULL;
	else
		pFirst->pNext->pPrev = NULL;
	pFirst = pFirst->pNext;
	delete pTemp;
}
template<typename T>
inline void LinkedList<T>::removeLast() {
	Node* pTemp = pLast;
	if (pFirst->pNext == NULL)
		pFirst = NULL;
	else
		pLast->pPrev->pNext = NULL;
	pLast = pLast->pPrev;
	delete pTemp;
}

template<typename T>
inline bool LinkedList<T>::removeElement(T data) {
	Node* pTemp2, *pTemp = pFirst;
	if (pFirst->dataT == data) { //value is first in list
		pFirst = pFirst->pNext;
		pFirst->pPrev = NULL;
		delete pTemp;
		return true;
	}

	while (pTemp->data != data) {
		pTemp = pTemp->pNext;
		if (pTemp == NULL)
			return false;
	}
	if (pTemp->pNext == NULL) {//value is last in list
		pLast = pTemp->pPrev;
		pLast->pNext = NULL;
		delete pTemp;
		return true;
	}
	else {
		pTemp2 = pTemp->pPrev; //value is in between first and last in list
		pTemp2->pNext = pTemp->pNext;
		pTemp->pNext->pPrev = pTemp2;
		delete pTemp;
		return true;
	}
}

template<typename T>
inline bool LinkedList<T>::insertAfter(T key, T data) {
	Node* pCurrent = pFirst;
	while (pCurrent->dataT != key) {
		pCurrent = pCurrent->pNext;
		if (pCurrent == NULL)
			return false;
	}

	Node* pNewNode = new Node(data);

	if (pCurrent == pLast) {
		pNewNode->pNext = NULL;
		pLast = pNewNode;
	}
	else {
		pNewNode->pNext = pCurrent->pNext;
		pCurrent->pNext->pPrev = pNewNode;
	}
	pNewNode->pPrev = pCurrent;
	pCurrent->pNext = pNewNode;
	return true;
}

template<typename T>
inline void LinkedList<T>::displayForward() {
	cout << "List (first-->last): ";
	Node* pCurrent = pFirst;
	while (pCurrent != NULL) {
		pCurrent->getDisplay();
		pCurrent = pCurrent->pNext;
	}
	cout << endl;
}

template<typename T>
inline void LinkedList<T>::displayBackward() {
	cout << "List (last-->first): ";
	Node* pCurrent = pLast;
	while (pCurrent != NULL) {
		pCurrent->getDisplay();
		pCurrent = pCurrent->pPrev;
	}
	cout << endl;
}

template<typename T>
inline Node* LinkedList<T>::search(T data) {
	Node *pTemp = pFirst;
	if (!isEmpty()) {
		while (pTemp->dataT != data) {
			pTemp = pTemp->pNext;
			if (pTemp->pNext == NULL) {
				return NULL;
			}//key isn't in list
		}
		return pTemp;
	}
	else
		return NULL;
}

template<typename T>
inline void LinkedList<T>::sort() {
	setTail();
	quickSort(pFirst, pLast);
}

template<typename T>
inline void LinkedList<T>::setTail() {
	Node *temp = pFirst;
	while (temp && temp->pNext) {
		temp = temp->pNext;
	}
	pLast = temp;
}

template<typename T>
inline void LinkedList<T>::quickSort(Node* low, Node* high) {
	if (high != NULL && low != high && low != high->pNext) {
		Node* p = partition(low, high);
		quickSort(low, p->pPrev);
		quickSort(p->pNext, high);
	}
}

template<typename T>
inline Node* LinkedList<T>::partition(Node* low, Node* high) {
	T pivot = high->dataT;
	Node *A = low->pPrev;

	for (Node *B = low; B != high; B = B->pNext) {
		if (B->dataT <= pivot) {
			A = (A == NULL) ? low : A->pNext;
			swapNodes(&(A->dataT), &(B->dataT));
		}
	}
	A = (A == NULL) ? low : A->pNext;
	swapNodes(&(A->dataT), &(high->dataT));
	return A;
}

template<typename T>
inline void LinkedList<T>::swapNodes(T *A, T *B) {
	T temp = *A;
	*A = *B;
	*B = temp;
}

template<typename T>
inline bool lessThan(const T& a, const T& b){
	return a < b;
}

template<typename T>
inline bool greaterThan(const T& a, const T& b){
	return a < b;
}

template<typename T>
inline bool equals(const T& a, const T& b){
	return !(a < b || b < a);
}


#endif // LINKEDLIST_H
