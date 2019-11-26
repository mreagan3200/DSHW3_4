#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <map>
#include <utility>
#include <vector>

#include "LinkedList.h"
#include "Car.h"
#include "Floor.h"
#include "Passenger.h"
#include "Clock.h"
#include "RequestQueue.h"

const int DEFAULT_CAR_NUM = 1;
const int DEFAULT_FLOOR_NUM = 6;
const int DEFAULT_HRS = 12;


class Controller
{
private:
	int numCars;
	int numFloors;
	Car* cars;
	Floor* floors;
	Clock clock;
	RequestQueue requests;
	vector<std::string> states;
	map<int, Passenger*> passengers;
	map<int, vector<pair<int, int>>> schedule;
	int passengersServed;


public:
	Controller(map<int, Passenger*> passengers, map<int, vector<pair<int, int>>> schedule, int numCars = DEFAULT_CAR_NUM, int numFloors = DEFAULT_FLOOR_NUM, int hrsInDay = DEFAULT_HRS, int minsInDay = 0, int secsInDay = 0);
	bool updateSim();
	void calculateCarState(int car);
	void loadPassenger(Passenger* passenger, int car);
	void callCar(int floor, std::string direction);
	void pressButton(int floor);
	int getPassengersServed() { return passengersServed;  }
};

#endif

