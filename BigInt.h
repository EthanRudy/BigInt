// Declaration file for the BigInt class
// @file BigInt.h
// @author Ethan Rudy
// @version 0.1

#pragma once
#include <iostream>
#include <string>
#include <vector>

class BigInt
{
private:
	/**
	* Dynamic array for binary
	* Starts off with 32 bits, most compatable with passed integers
	* Stored in reverse for ease of access
	* Index 31 being the most significant bit when full
	*/
	bool bin[32];

	/**
	* Dynamic array for 2's complement
	* Starts off with 32 bits, most compatable with passed integers
	* Stored in revers for ease of access
	* Index 31 bing the most sifnificant bit when full
	*/
	bool com[32];

	/**
	* Boolean value that stores if a BigInteger stores a negative value
	* Used as a flag for output and deciding where 2's complement is applicable
	*/
	bool neg = false;

	/**
	* Length counter for ease of access and resizing
	* When resizing, 4 bits are added for a compromize of space and speed
	*/
	int len = 32;

	/**
	* Starting point of the left most segment of 4 bits for BCD generation
	* Starts at index 0, meaning 0000|...
	*/
	int lsegs = 0;

	/**
	* Generates the binary representation of a number
	* 
	* Only ran when constructing a new BigInt object
	* 
	* @param n Number being converted
	*/
	void generate_binary(int n);


	/**
	* Generates the 2's complement representation from binary
	* 
	* Only ran when this form is needed in arithmetic
	*/
	void generate_2scomp();

public:

	/**
	* Integer constructor
	* 
	* Generates a new BigInteger with the given integer
	* 
	* @param n The integer being stored
	*/
	BigInt(int n);


	/**
	* To string
	* 
	* Generates a string representation of a BigInteger using
	* BCD and the double dabble method: https://en.wikipedia.org/wiki/Double_dabble
	* 
	* @return res The resulting string
	*/
	std::string to_string();
};
