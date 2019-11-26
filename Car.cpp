#include "Car.h"

Car::Car() {
	this->timer = 0;
	this->location = 0;
	this->position = 0;
	this->maxWeight = 0;
	this->weight = 0;
	this->state = vector<string>();
	this->stateNum = 0;
	this->direction = "idle";
}

Car::Car(int start, int maxWeight, vector<std::string> init) {
	this->timer = 0;
	this->location = start;
	this->position = 0;
	this->maxWeight = maxWeight;
	this->weight = 0;
	this->state = init;
	this->stateNum = 0;
	this->direction = "idle";
}

void Car::setTimer(int secs) {
	this->timer = secs;
}

void Car::tickTimer() {
	this->timer -= 1;
}

void Car::loadPassenger(Passenger* passenger) {
	this->passengers[passenger->destination].prepend(passenger);
	this->addWeight(passenger->weight);
}

Passenger* Car::unloadPassenger() {
	if (this->passengers[this->location].isEmpty()) {
		return nullptr;
	}

	Passenger* passenger = this->passengers[this->location].pop();
	this->addWeight(-passenger->weight);
	passenger->location = this->location;
	cout << "Passenger unloaded" << endl;
	return passenger;
}


