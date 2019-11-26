#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <map>

#include "Queue.h"
#include "Passenger.h"


class Floor
{
private:
	Queue<Passenger*> queue;

public:
	Floor();
	Passenger* dequeuePassenger();
	void queuePassenger(Passenger* passenger);
};

#endif
