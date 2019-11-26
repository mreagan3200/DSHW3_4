#include "Clock.h"

Clock::Clock() {
	this->time = 1;
	this->endTime = 1;
}

Clock::Clock(int startTime, int hrs, int mins, int secs) {
	this->time = startTime;
	this->endTime = secs + (60 * mins) + (3600 * hrs);
}

void Clock::addTime(int add) {
	this->time += add;
}

void Clock::reset() {
	this->time = 0;
}

void Clock::tick() {
	this->time++;
}

int Clock::read() {
	return this->time;
}

int Clock::getEndTime() {
	return this->endTime;
}