
#pragma once
#ifndef _LinkedList_H_
#define _LinkedList_H_

template<typename T>
class LinkedList{
protected:
	class Node{
		friend class LinkedList<T>;

	private:
		T data;
		Node* next;
		Node* prev;

	public:
		Node(T d, Node *n = NULL, Node *p = NULL) : data(d), next(n), prev(p){}
	};

	Node *head;
	Node *tail;
	int count;

private:
	void swapNodes(T*, T*);
	void quickSort(Node*, Node*);
	void setTail();

	Node* LinkedList<T>::partition(Node* low, Node* high){
		T pivot = high->data;
		Node *A = low->prev;

		for (Node *B = low; B != high; B = B->next){
			if (B->data <= pivot){
				A = (A == NULL) ? low : A->next;
				swapNodes(&(A->data), &(B->data));
			}
		}
		A = (A == NULL) ? low : A->next;
		swapNodes(&(A->data), &(high->data));
		return A;
	}

public:

	LinkedList(const LinkedList<T>&srac);
	~LinkedList();
	LinkedList() : head(NULL), tail(NULL) {}

	T& firstNode(void){
		if (head!= NULL)
			return head->data;
	}

	T& lastNode(void){
		if (tail!= NULL)
			return tail->data;
	}

	void sort();
	bool isEmpty();
	void insertFirst(T*);
	void insertFirst(T);
	void insertLast(T*);
	void insertLast(T);
	void removeFirst(T);
	void removeLast(T);
	Node* search(T);
	bool contains(T, int&);
	void printForward();
	T peek();
	T* elementAt(int);

	int size(){
		Node *t = head;
		int c = 0;
		while (t){
			t = t->next;
			c++;
		}
		return c;
	}

};

//template<typename T>
//inline Node::Node(T _data) : data(_data_), next(NULL), prev(NULL){}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& src) : head(NULL), tail(NULL){
	Node* curr = src.head;
	while (curr != NULL){
		this->insertFirst(curr->data);
		curr = curr->next;
	}
}

template<typename T>
inline LinkedList<T>::~LinkedList() {
	Node* curr = head;
	while (curr != NULL) {
		Node* old = curr;
		curr = curr->next;
		delete old;
	}
}

template<typename T>
inline bool LinkedList<T>::isEmpty(){
	if (head == NULL)
		return true;
	else
		return false;
}

template<typename T>
inline void LinkedList<T>::insertFirst(T* data){
	Node* n = new Node(*data);
	if (isEmpty())
		tail = n;
	else
		head->prev = n;
	n->next = head;
	head = n;
}

template<typename T>
inline void LinkedList<T>::insertFirst(T data){
	Node* n = new Node(data);
	if (isEmpty())
		tail = n;
	else
		head->prev = n;
	n->next = head;
	head = n;
}

template<typename T>
inline void LinkedList<T>::insertLast(T* data){
	Node *n = new Node(*data);
	if (isEmpty())
		head = n;
	else{
		tail->next = n;
		n->prev = tail;
	}
	tail = n;
}

template<typename T>
inline void LinkedList<T>::insertLast(T data){
	Node *n = new Node(data);
	if (isEmpty())
		head = n;
	else{
		tail->next = n;
		n->prev = tail;
	}
	tail = n;
}

template<typename T>
inline void LinkedList<T>::sort(){
	setTail();
	quickSort(head, tail);
}

template<typename T>
inline void LinkedList<T>::setTail(){
	Node *temp = head;
	while (temp && temp->next){
		temp = temp->next;
	}
	tail = temp;
}

template<typename T>
inline void LinkedList<T>::quickSort(Node* low, Node* high){
	if (high != NULL && low != high && low != high->next) {
		Node* p = partition(low, high);
		quickSort(low, p->prev);
		quickSort(p->next, high);
	}
}

template<typename T>
inline T* LinkedList<T>::elementAt(int index){
	int counter = 0;
	Node *temp = head;
	while (counter != index && temp != NULL){
		counter++;
		temp = temp->next;
	}
	return &(temp->data);
}

/*
template<typename T>
inline LinkedList<T>::Node* LinkedList<T>::partition(Node* low, Node* high){
	T pivot = high->data;
	Node *A = low->prev;

	for (Node *B = low; B != high; B = B->next){
		if (B->data <= pivot){
			A = (A == NULL) ? low : A-> next;
			swapNodes(&(A->data), &(B->data));
		}
	}
	A = (A == NULL) ? low : A->next;
	swap(&(A->data), &(high->data));
	return A;
}
*/

template<typename T>
inline void LinkedList<T>::swapNodes(T* A, T* B){
	T temp = *A;
	*A = *B;
	*B = temp;
}

template<typename T>
inline void LinkedList<T>::printForward(){
	static int count = 0;
	Node *t = head;
	while (t){
		std::cout << t->data << " ";
		t = t->next;
	}
}

template<typename T>
inline T LinkedList<T>::peek(){
	Node *t = head;
	return t->data;
}

template<typename T>
inline bool LinkedList<T>::contains(T dataT, int &i){
	Node *t = head;
	int count = 0;
	while (t){
		if (t->data == dataT){
			i = count;
			return true;
		}
		else{
			t = t->next;
			count++;
		}
	}
	return false;
}

#endif