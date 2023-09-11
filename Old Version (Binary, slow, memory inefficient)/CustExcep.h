#pragma once

#include <string>

class CustExcep : public std::exception {
private:
	std::string message;
public:
	CustExcep(std::string msg) : message(msg) {}
	std::string what() {
		return message;
	}
};
