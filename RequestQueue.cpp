#include "RequestQueue.h"

void RequestQueue::insertRequest(std::string carDirection, int carLocation, std::string requestDirection, int floor) {
	Request* request = new Request(requestDirection, floor);
	bool carIdle = carDirection == "idle";
	bool onTheWay = (carDirection == "up" && floor > carLocation) || (carDirection == "down" && floor < carLocation);
	bool otherWay = carDirection != requestDirection;
	bool missedYa = !otherWay && !onTheWay;


	if (onTheWay || carIdle) {
		this->current.insertInOrder(request);
	}

	else if (otherWay) {
		this->next.insertInOrder(request);
	}

	else if (missedYa) {
		this->future.insertInOrder(request);
	}
}

void RequestQueue::deleteRequest(int location) {
	if (*this->current.top() != location) {
		// throw exception, should only be stopping at the next location in queue
	}
	Request* temp = current.pop();
	if (temp != nullptr) {
		delete temp;
	}

	// in case there's two requests at this location, a stop call and a car call from the floor
	if (this->current.top() && *this->current.top() == location) {
		temp = current.pop();
		if (temp != nullptr) {
			delete temp;
		}
	}

	// If there's a passenger waiting on this floor going the opposite way from the car's direction this trip, the car will still try to load them,
	// so we have to check the next trip to see if there's a request there that needs to be deleted.
	// Stopping at a floor should delete ALL requests from that floor, up/down/stop or any combination of the three.
	// If there are still passengers waiting but can't board because of the weight limit, they'll re-request.
	// performance bottleneck here from searching linear list, could change RequestQueue to use a tree instead.
	Request dummy = Request("", location);
	this->next.delIfInList(&dummy);
	
}

int RequestQueue::nextStop() {
	return this->current.top()->floor;
}

bool RequestQueue::isTripOver() {
	return this->current.isEmpty();
}

void RequestQueue::endTrip() {
	if (!this->current.isEmpty()) {
		// throw exception, the trip is only done when the current trip queue is empty
	}

	LinkedList<Request> temp = current;
	this->current = next;
	this->next = future;
	this->future = temp;
}

bool Request::operator > (Request* other) {
	if (other->direction != this->direction) {
		// throw exception, unlike requests should not be stored in the same request queue
	}
	else if (this->direction == "up") {
		return this->floor > other->floor;
	}

	else if (this->direction == "down") {
		return this->floor < other->floor;
	}
}


bool Request::operator >= (Request* other) {
	if (other->direction != this->direction) {
		// throw exception, unlike requests should not be stored in the same request queue
	}
	else if (this->direction == "up") {
		return this->floor >= other->floor;
	}

	else if (this->direction == "down") {
		return this->floor <= other->floor;
	}
}

bool Request::operator < (Request* other) {
	return !(this >= other);
}

bool Request::operator <= (Request* other) {
	return !(this > other);
}

bool Request::operator == (Request* other) {
	return this->floor == other->floor;
}

bool Request::operator != (Request* other) {
	return !(this == other);
}

bool Request::operator == (int location) {
	return this->floor == location;
}

bool Request::operator != (int location) {
	return this->floor == location;
}
