#include <map>
#include <iostream>

#include "Passenger.h"
#include "Controller.h"

const int PASSENGER_NUM = 800;

map<int, Passenger*> makePassengers();
map<int, vector<pair<int, int>>> getSchedule();

int main() {
	map<int, Passenger*> passengers = makePassengers();
	map<int, vector<pair<int, int>>> schedule = getSchedule();

	Controller controller = Controller(passengers, schedule, 1, 6, 12, 0, 0);
	//int t = 0;
	while (controller.updateSim()) {
		//cout << "Time: " << t++ << endl;
	}
	cout << "Passengers Served: " << controller.getPassengersServed();

	/*for (int i = 0; i < PASSENGER_NUM; i++) {
		cout << passengers[i]->PID;
		cout << " " << passengers[i]->location;
		cout << " " << passengers[i]->weight << endl;
	}*/
}

map<int, vector<pair<int, int>>> getSchedule() {
	map<int, vector<pair<int, int>>> schedule; // map<seconds, <PID, destinationFloor>>
	srand(0);
	for (int i = 0; i < PASSENGER_NUM; i++) {
		double r = ((double)rand() / (RAND_MAX));
		int seconds = (r * 43200);
		int currentFloor = -1;
		if (i < 100) {
			currentFloor = 2;
		}
		else if (i < 300) {
			currentFloor = 3;
		}
		else if (i < 600) {
			currentFloor = 4;
		}
		else if (i < 800) {
			currentFloor = 5;
		}
		int destinationFloor = currentFloor;
		while (destinationFloor == currentFloor) {
			destinationFloor = ((double)rand() / (RAND_MAX)) * 6;
		}
		schedule[seconds].push_back(make_pair(i, destinationFloor));
	}
	return schedule;
}

map<int, Passenger*> makePassengers() {
	map<int, Passenger*> result;
	Passenger* passenger;
	int floor;
	double weight;

	for (int i = 0; i < PASSENGER_NUM; i++) {
		if (i < 100) {
			floor = 2;
			weight = 130;
		}
		else if (i < 300) {
			floor = 3;
			weight = 140;
		}
		else if (i < 600) {
			floor = 4;
			weight = 150;
		}
		else if (i < 800) {
			floor = 5;
			weight = 160;
		}
		passenger = new Passenger{ i, floor, 0, weight, };
		result[i] = passenger;
	}
	return result;
}