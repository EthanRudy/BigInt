// CSP: Initialization for the DigiArr class
// @file DigiArr.cpp
// @author Ethan Rudy
// @version 1.0 3.24.2022

#include "DigiArr.h"

// Fills the data from the passed string
void DigiArr::fill(std::string n) {
	if (n[0] =='-') {
		this->negative = true;
		n = n.substr(1);
	}
	else {
		this->negative = false;
	}

	this->len = n.length();
	this->n = new int[len];

	int ind = len - 1;
	for (int i = 0; i < len; i++) {
		this->n[ind] = n[i] - '0';
		--ind;
	}

}

// Default Constructor
DigiArr::DigiArr() {
	fill("0");
}

// Integer Constructor
DigiArr::DigiArr(int n) {
	fill(std::to_string(n));
}

// Double Constructor
DigiArr::DigiArr(double n) {
	fill(std::to_string((int)n));
}

// Float Constructor
DigiArr::DigiArr(float n) {
	fill(std::to_string((int)n));
}

// String Constructor
DigiArr::DigiArr(std::string n) {
	fill(n);
}

// Gets the array of digits of the called DigiArr
int* DigiArr::get_arr() {
	return this->n;
}

// Gets the length of the called DigiArr
int DigiArr::length() {
	return this->len;
}

// Gets whether the called DigiArr is negative or not
bool DigiArr::is_negative() {
	return this->negative;
}
