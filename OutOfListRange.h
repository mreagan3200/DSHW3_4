#ifndef OUTOFLISTRANGE_H
#define OUTOFLISTRANGE_H

#include <exception>

class OutOfListRange : public std::exception {
public:
	const char* what() const throw() override {
		return "Error: out of linked list range";
	}
};

#endif