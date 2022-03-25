// CSP: Declaration for the DigiArr class
// @file DigiArr.h
// @author Ethan Rudy
// @version 1.0 3.24.2022

#pragma once
#include <string>

/*
	Allows for the storage and basic manipulation of large integers
*/
class DigiArr
{
private:
	int* n;			// Dynamic array to hold the digits for the number
	int len;		// The length of the stored number
	bool negative;	// Boolean for if the number is positive or negative


	/*
		Fills the data from the passed string

		@param "n" of type STD::STRING to be converted
	*/
	void fill(std::string n);

public:
	/*
		Default Constructor	
	*/
	DigiArr();

	/*
		Integer Constructor

		@param "n" of type INT to be converted
	*/
	DigiArr(int n);

	/*
		Double Constructor

		@param "n" of type DOUBLE to be converted
	*/
	DigiArr(double n);

	/*
		Float Constructor

		@param "n" of type FLOAT to be converted
	*/
	DigiArr(float n);

	/*
		String Constructor

		@param "n" of type STD::STRING to be converted
	*/
	DigiArr(std::string n);


	/*
		Gets the array of digits of the called DigiArr

		@return the dynamic array of type INT of the called DigiArr
	*/
	int* get_arr();

	/*
		Gets the length of the called DigiArr

		@return the length of type INT of the called DigiArr
	*/
	int length();

	/*
		Gets whether the called DigiArr is negative or not

		@return the negative value of type BOOLEAN
	*/
	bool is_negative();
};
