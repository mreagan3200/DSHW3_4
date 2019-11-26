#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>

#include <iostream>

#include "LinkedList.h"
#include "Passenger.h"
using namespace std;

const int NUM_FLOORS = 6;
const int CAR_SPEED = 3; // assume it takes three seconds to move another floor

class Car
{
private:
	int position; // position will be an int from 0-2 as it takes 3 seconds to move to another floor.
	int timer;
	int location;
	int maxWeight;
	double weight;
	std::string direction;
	LinkedList<Passenger> passengers[NUM_FLOORS];
	vector<std::string> state;
	int stateNum;
	
public:
	Car();
	Car(int start, int maxWeight, vector<string> init);
	
	void setTimer(int secs);
	void tickTimer();

	Passenger* unloadPassenger();
	void loadPassenger(Passenger*);

	std::string getDirection() { return this->direction; }
	void setDirection(std::string direction) { this->direction = direction; }
	
	int getLocation() { return this->location; }
	void setLocation(int location) { this->location = location; }
	void incLocation() { this->location++; }

	double getWeight() { return this->weight; }
	void addWeight(double weight) { this->weight += weight; }

	double getMaxWeight() { return this->maxWeight; }
	
	string getState() { return state.at(stateNum); }
	void nextState() { stateNum = (stateNum + 1) % state.size(); }

	int getPosition() { return this->position; }
	
	int readTimer() { return this->timer; }

	void incPosition() { this->location = (location + 1) % 3; }

};

#endif

