#ifndef QUEUEUNDERFLOW_H
#define QUEUEUNDERFLOW_H

#include <exception>

class QueueUnderflow : public std::exception
{
public:
	const char* what() const throw() override{
		return "Queue underflow error.";
	}
};

#endif

