#include "Controller.h"
#define CAR_SPEED 3


std::string LOAD = "S1";
std::string ACCELERATE = "S2";
std::string CONSTANT = "S3";
std::string DECELERATE = "S4";
std::string UNLOAD = "S5";

Controller::Controller(map<int, Passenger*> passengers, map<int, vector<pair<int, int>>> schedule, int numCars, int numFloors, int hrsInDay, int minsInDay, int secsInDay) {
	this->passengers = passengers;
	this->schedule = schedule;
	
	this->numCars = numCars;
	this->numFloors = numFloors;

	this->cars = new Car[numCars];

	this->floors = new Floor[numFloors];
	this->clock = Clock(0, hrsInDay, minsInDay, secsInDay);

	this->states = vector<std::string>();
	this->states.push_back(LOAD);
	this->states.push_back(ACCELERATE);
	this->states.push_back(CONSTANT);
	this->states.push_back(DECELERATE);
	this->states.push_back(UNLOAD);

	this->passengersServed = 0;
	//this->states.makeCircuit();
	for (int i = 0; i < numCars; i++) {
		cars[i] = Car(1, 3000, states);
	}


}

// return false if the day is over
bool Controller::updateSim() {
	int time = this->clock.read();
	vector<pair<int, int>> happening;
	Passenger* passenger;

	//if (this->schedule.count(time) == 1) {
	happening = this->schedule[time];
	for (auto pair : happening) {
		passenger = this->passengers[pair.first];
		passenger->destination = pair.second;
		this->floors[passenger->location].queuePassenger(passenger);
		string dir = passenger->location - pair.second > 0 ? "down" : "up";
		requests.insertRequest(cars[0].getDirection(), cars[0].getLocation(), dir, passenger->location);
	}
	//}

	for (int i = 0; i < this->numCars; i++) {
		calculateCarState(i);
	}

	this->clock.tick();

	if (this->clock.read() > this->clock.getEndTime()) {
		this->clock.reset();
		return false;
	}
	else {
		return true;
	}
}

void Controller::loadPassenger(Passenger* passenger, int car) {
	std::string direction = this->cars[car].getDirection();
	int destination = passenger->destination;
	int location = this->cars[car].getLocation();

	this->requests.insertRequest(direction, location, "stop", destination);
	this->cars[car].loadPassenger(passenger);
}

void Controller::calculateCarState(int carNum) {
	Car* car = &(this->cars[carNum]);
	std::string direction = car->getDirection();
	Floor* floor = &this->floors[car->getLocation()];
	Passenger* passenger;
	cout << "state: " << car->getState() << "\n";
	// car is in a cooldown period from a previous task
	if (car->readTimer() > 0) {
		car->tickTimer();
	}
	// Load/idle state
	else if (car->getState() == "S1") {

		// if there's a passenger waiting, load them
		passenger = floor->dequeuePassenger();
		if (passenger && car->getWeight() < car->getMaxWeight()) {
			this->loadPassenger(passenger, carNum);
			car->setTimer(1);
			passengersServed++;
		}

		// As long as car is idling, just check for new requests
		else if (car->getDirection() == "idle") {
			if (!this->requests.isTripOver()) {
				// if the elevator is on the same floor as request already, the controller will just load the passenger straight away
				if (this->requests.nextStop() > car->getLocation()) {
					car->setDirection("up");
				}
				else {
					car->setDirection("down");
				}
				car->nextState();
			}
		}

		// if there's no more requests, end the trip
		else if (this->requests.isTripOver()) {
			this->requests.endTrip();

			// if there are still no requests, then there are no requests in the queue at all, and the car will idle until a new request
			if (this->requests.isTripOver()) {
				car->setDirection("idle");
			}
		}

		// If there's no more passengers (or the weight limit is reached), and the car is not idle, and there are more 
		//stops in the trip, then simply continue the trip
		else {
			car->nextState();
		}
	}

	// acceleration state
	else if (car->getState() == "S2") {
		car->setTimer(1);
		car->incPosition();
		car->nextState();
	}

	// normal speed state (should only be in this state if there it's going towards a request)
	else if (car->getState() == "S3") {
		// if the car is one second away from reaching the next floor, check for a request
		cout << car->getPosition();
		if (car->getPosition() == (CAR_SPEED - 1)) {
			cout << "got here";
			if (this->requests.nextStop() == car->getLocation() + 1) {
				car->nextState();
				cout << "got here2";
			}
			// if the floor above isn't a stop, then increment the car location and position
			else {
				car->incLocation();
				car->incPosition();
			}
		}

		// if the car is not about to reach the next floor, just increment position
		else {
			car->incPosition();
		}
	}

	// deceleration state
	// just increment the location and position and move to next state
	else if (car->getState() == "S4") {
		car->incLocation();
		car->incPosition();
		car->nextState();
	}

	// unload state
	else if (car->getState() == "S5") {
		passengersServed++;
		passenger = car->unloadPassenger();
		if (passenger) {
			car->setTimer(1);
		}

		else {
			car->nextState();
		}
	}
}

void Controller::callCar(int floor, std::string direction) {
	//this->floors[floor].callCar(direction);
}

void Controller::pressButton(int floor) {
	//this->floors[floor].sendStop();
}
