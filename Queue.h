#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include "QueueUnderflow.h"

using namespace std;

template <typename T>
class Queue
{
private:
	vector<T> queue;
	int length;

public:
	Queue() {
		this->length = 0;
	}

	const int getLength() {
		return this->length;
	}

	// enqueue by inserting at beginning of vector
	void enqueue(T data) {
		this->queue.insert(this->queue.begin(), data);
		this->length++;
	}

	// dequeue by popping off end of vector, FIFO
	T dequeue() {
		if (this->length <= 0) {
			throw QueueUnderflow();
		}
		else {
			T data = this->queue.back();
			this->queue.pop_back();
			this->length--;

			return data;
		}
	}

	T peek() {
		if (this->length <= 0) {
			throw QueueUnderflow();
		}
		else {
			return this->queue.back();
		}
	}

	bool isEmpty() {
		return this->length == 0;
	}

	void clear() {
		this->queue.clear();
		this->length = 0;
	}
};
#endif

