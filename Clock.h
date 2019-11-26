#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
private:
	int time;
	int endTime;

public:
	Clock();
	Clock(int startTime, int hrs, int mins = 0, int secs = 0);

	void addTime(int add);
	void reset();
	void tick();
	int read();
	int getEndTime();
};

#endif