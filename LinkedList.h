#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <fstream>
#include <string>
#include "OutOfListRange.h"
#include "EmptyList.h"

//using namespace std;

template <typename T>
struct Node {
	T* data = nullptr;
	Node<T>* next = nullptr;
};

// holds the floor layout in a singly-linked linked list structure
// each node contains a pointer to a room object and a pointer to the next node
template <typename T>
class LinkedList {
protected:
	Node<T>* list;
	Node<T>* next;
	int length;

public:
	LinkedList() {
		this->list = nullptr;
		this->next = nullptr;
		this->length = 0;
	}

	LinkedList(T* data) {
		this->list = new Node<T>{data, nullptr};
		this->next = this->list;
		this->length = 0;
	}

	~LinkedList() {
		Node<T>* curr = this->list;
		Node<T>* temp = nullptr;

		while (curr){
			temp = curr->next;
			delete curr->data;
			delete curr;
			curr = temp;
		}
	}

	T* pop() {
		this->length--;

		if (!this->list) {
			throw EmptyList();
		}

		T* tempT = this->list->data;
		Node<T>* tempN = this->list;

		this->list = this->list->next;
		
		delete tempN;
		return tempT;
	}

	void append(T* data) {
		this->length++;
		Node<T>* curr = this->list;
		Node<T>* newNode = new Node<T>{data, nullptr};

		if (!curr) {
			this->list = newNode;
			this->next = list;
			return;
		}

		while (curr->next) {
			curr = curr->next;
		}
		curr->next = newNode;
	}

	void prepend(T* data) {
		Node<T>* node = new Node<T>{ data, this->list };
		this->list = node;
	}


	void insertInOrder(T* data) {
		this->length++;
		Node<T>* curr = this->list;
		Node<T>* prev = curr;
		Node<T>* newNode = new Node<T>{ data, nullptr };

		if (!curr) {
			this->list = newNode;
			return;
		}

		while (curr && *data <= curr->data) {
			prev = curr;
			curr = curr->next;
		}

		prev->next = newNode;
		newNode->next = curr;
	}

	void delIfInList(T* data) {
		Node<T>* curr = this->list;
		Node<T>* prev = curr;

		if (*curr->data == data) {
			this->list = nullptr;
			delete curr->data;
			delete curr;
			return;
		}

		while (curr) {
			if (*curr->data == data) {
				prev->next = curr->next;
				delete curr->data;
				delete curr;
			}
			prev = curr;
			curr = curr->next;
		}
	}

	T* top() {
		if (!this->list) {
			return nullptr;
		}
		return this->list->data;
	}

	void makeCircuit() {
		Node<T>* curr = this->list;

		if (!curr) {
			// TODO: throw exception
		}

		while (curr->next) {
			curr = curr->next;
		}
		curr->next = this->list;
	}

	T* seeNext() {
		if (this->isEmpty()) {
			throw EmptyList();
		}

		if (!this->next) {
			return nullptr;
		}

		T* result = this->next->data;
		this->next = this->next->next;
		
		return result;
	}

	// assuming the list is zero-based
	T* seeAt(int i){
		Node<T>* curr = this->list;

		if (i >= this->length) {
			throw OutOfListRange();
		}

		while (i > 0) {
			curr = curr->next;
			this->next = curr->next;
			i--;
		}
		return curr->data;
	}

	void reset() {
		this->next = this->list;
	}

	bool isEmpty() {
		return this->length == 0;
	}

	// operator overloads
	bool operator > (int num) {
		return this->length > num;
	}

	bool operator >= (int num) {
		return this->length >= num;
	}

	bool operator < (int num) {
		return this->length < num;
	}

	bool operator <= (int num) {
		return this->length <= num;
	}

	bool operator == (int num) {
		return this->length == num;
	}
};

#endif
