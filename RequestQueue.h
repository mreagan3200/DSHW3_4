#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <string>

#include "LinkedList.h"

class Request
{
public:
	std::string direction;
	int floor;

	Request(std::string direction, int floor) { this->direction = direction; this->floor = floor;}

	bool operator > (Request* other);
	bool operator >= (Request* other);
	bool operator < (Request* other);
	bool operator <= (Request* other);
	bool operator == (Request* other);
	bool operator == (int location);
	bool operator != (Request* other);
	bool operator != (int location);
};

class RequestQueue
{
private:
	// trip queues
	LinkedList<Request> current;
	LinkedList<Request> next;
	LinkedList<Request> future;

public:
	void insertRequest(std::string carDirection, int carLocation, std::string requestDirection, int floor);
	void deleteRequest(int location);
	void endTrip();

	bool isTripOver();
	int nextStop();
};

#endif
