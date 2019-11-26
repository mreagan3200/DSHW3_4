#ifndef EMPTYLIST_H
#define EMPTYLIST_H

#include <exception>

class EmptyList : public std::exception {
public:
	const char* what() const throw() override {
		return "Error: the list is emtpy.";
	}
};

#endif
