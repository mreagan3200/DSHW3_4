#include "Floor.h"

Floor::Floor() {
}

Passenger* Floor::dequeuePassenger() {
	if (this->queue.isEmpty()) {
		return nullptr;
	}

	return this->queue.dequeue();
}

void Floor::queuePassenger(Passenger* passenger) {
	this->queue.enqueue(passenger);
}