// Declaration for the BigInt class
// @file BigInt.h
// @author Ethan Rudy
// @version 1.0

#pragma once
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

class BigInt
{
private:
	std::string num = "";	// Holds the digits
	int len;				// Length of the number
	bool negative = false;	// Whether the number is negative

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                           PRIVATE FUNCTIONS                           //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

	/*
		Fills the data for a BigInt

		@param "n" of type STD::STRING
	*/
	void fill(std::string n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                              HELPERS                              //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		String constructor with negative override with reverse switch

		@param "n" of type STD::STRING
		@param "neg" of type BOOL
		@param "r" of type bool (True is already reversed)
	*/
	BigInt(const std::string& n, const bool& neg, const bool& r);

	/*
		Finds the sum of the the two passed strings

		@param "n1" of type STD::STRING
		@param "n2" of type STD::STRING

		@return the sum of the two passed strings
	*/
	std::string add(std::string n1, std::string n2);

	/*
		Finds the difference of the the two passed strings

		@param "n1" of type STD::STRING
		@param "n2" of type STD::STRING

		@return the difference of the two passed strings
	*/
	std::string subtract(std::string n1, std::string n2);

	/*
		Recursively finds the product of the two passed strings

		@param "n1" of type STD::STRING
		@param "n2" of type STD::STRING

		@return the product of the two passed strings
	*/
	std::string karatsuba(std::string n1, std::string n2);

	/*
		Shifts the number to the right by inserting (filler) zeros

		@param "n" of type STD::STRING
		@param "amount" of type INT

		@return the shifted value of "n";
	*/
	std::string shift(std::string n, int amount);

	/*
		Shifts the number to the left by inserting (x10) zeros

		@param "n" of type STD::STRING
		@param "amount" of type INT

		@return the shifted value of "n";
	*/
	std::string pow10(std::string n, int amount);

	/*
		Trims the leading zeros of a number

		@param "n" of type STD::STRING

		@return the trimmed value of "n"l
	*/
	std::string trim0(std::string n);


public:

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                              CONSTRUCTORS                             //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

	/*
		Default Constructor
	*/
	BigInt();

	/*
		Integer Constructor

		@param "n" of type INT
	*/
	BigInt(const int& n);

	/*
		Long Cosntructor

		@param "n" of type LONG
	*/
	BigInt(const long& n);

	/*
		Float Constructor

		@param "n" of type FLOAT
	*/
	BigInt(const float& n);

	/*
		Double Constructor

		@param "n" of type DOUBLE
	*/
	BigInt(const double& n);

	/*
		String Constructor

		@param "n" of type STD::STRING
	*/
	BigInt(const std::string& n);


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                           ACCESOR FUNCTIONS                           //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

	/*
		Gets the string of digits of the called BigInt

		@return "num"
	*/
	std::string get_str();

	/*
		Gets the length of the called BigInt

		@return "len"
	*/
	int length();

	/*
		Gets whether the called BigInt is negative

		@return "negative"
	*/
	bool is_negative();


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                           BOOLEAN OPERATORS                           //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                              EQUAL TO                             //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Checks if the passed BigInt is equal in value to the called BigInt

		@param "n" of type BIGINT

		@return if the passed BigInt is equal in value to the called BigInt
	*/
	bool operator==(const BigInt& n);

	/*
		Checks if the passed integer is equal in value to the called BigInt

		@param "n" of type INT

		@return if the passed integer is equal in value to the called BigInt
	*/
	bool operator==(const int& n);

	/*
		Checks if the passed long is equal in value to the called BigInt

		@param "n" of type LONG

		@return if the passed long is equal in value to the called BigInt
	*/
	bool operator==(const long& n);

	/*
		Checks if the passed float is equal in value to the called BigInt

		@param "n" of type FLOAT

		@return if the passed float is equal in value to the called BigInt
	*/
	bool operator==(const float& n);

	/*
		Checks if the passed double is equal in value to the called BigInt

		@param "n" of type DOUBLE

		@return if the passed double is equal in value to the called BigInt
	*/
	bool operator==(const double& n);

	/*
		Checks if the passed string is equal in value to the called BigInt

		@param "n" of type STD::STRING

		@return if the passed string is equal in value to the called BigInt
	*/
	bool operator==(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                            GREATER THAN                           //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Checks if the passed BigInt is greater than in value to the
			called BigInt

		@param "n" of type BIGINT

		@return if the passed BigInt is greater than in value to the
			called BigInt
	*/
	bool operator>(const BigInt& n);

	/*
		Checks if the passed integer is greater than in value to the
			called BigInt

		@param "n" of type INT

		@return if the passed integer is greater than in value to the
			called BigInt
	*/
	bool operator>(const int& n);

	/*
		Checks if the passed long is greater than in value to the
			called BigInt

		@param "n" of type LONG

		@return if the passed long is greater than in value to the
			called BigInt
	*/
	bool operator>(const long& n);

	/*
		Checks if the passed float is greater than in value to the
			called BigInt

		@param "n" of type FLOAT

		@return if the passed float is greater than in value to the
			called BigInt
	*/
	bool operator>(const float& n);

	/*
		Checks if the passed ___ is greater than in value to the
			called BigInt

		@param "n" of type ___

		@return if the passed ___ is greater than in value to the
			called BigInt
	*/
	bool operator>(const double& n);

	/*
		Checks if the passed string is greater than in value to the
			called BigInt

		@param "n" of type STD::STRING

		@return if the passed string is greater than in value to the
			called BigInt
	*/
	bool operator>(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                             LESS THAN                             //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Checks if the passed BigInt is less than in value to the
			called BigInt

		@param "n" of type BIGINT

		@return if the passed BigInt is less than in value to the
			called BigInt
	*/
	bool operator<(const BigInt& n);

	/*
		Checks if the passed integer is less than in value to the
			called BigInt

		@param "n" of type INT

		@return if the passed integer is less than in value to the
			called BigInt
	*/
	bool operator<(const int& n);

	/*
		Checks if the passed long is less than in value to the
			called BigInt

		@param "n" of type LONG

		@return if the passed long is less than in value to the
			called BigInt
	*/
	bool operator<(const long& n);

	/*
		Checks if the passed float is less than in value to the
			called BigInt

		@param "n" of type FLOAT

		@return if the passed float is less than in value to the
			called BigInt
	*/
	bool operator<(const float& n);

	/*
		Checks if the passed double is less than in value to the
			called BigInt

		@param "n" of type DOUBLE

		@return if the passed double is less than in value to the
			called BigInt
	*/
	bool operator<(const double& n);

	/*
		Checks if the passed string is less than in value to the
			called BigInt

		@param "n" of type STD::STRING

		@return if the passed string is less than in value to the
			called BigInt
	*/
	bool operator<(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                            NOT EQUAL TO                           //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Checks if the passed BigInt is not equal in value to the called BigInt

		@param "n" of type BIGINT

		@return if the passed BigInt is not equal in value to the called BigInt
	*/
	bool operator!=(const BigInt& n);

	/*
		Checks if the passed integer is not equal in value to the
			called BigInt

		@param "n" of type INT

		@return if the passed integer is not equal in value to the
			called BigInt
	*/
	bool operator!=(const int& n);

	/*
		Checks if the passed long is not equal in value to the called BigInt

		@param "n" of type LONG

		@return if the passed long is not equal in value to the called BigInt
	*/
	bool operator!=(const long& n);

	/*
		Checks if the passed float is not equal in value to the called BigInt

		@param "n" of type FLOAT

		@return if the passed float is not equal in value to the called BigInt
	*/
	bool operator!=(const float& n);

	/*
		Checks if the passed double is not equal in value to the called BigInt

		@param "n" of type DOUBLE

		@return if the passed double is not equal in value to the called BigInt
	*/
	bool operator!=(const double& n);

	/*
		Checks if the passed string is not equal in value to the called BigInt

		@param "n" of type STD::STRING

		@return if the passed string is not equal in value to the called BigInt
	*/
	bool operator!=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                      GREATER THAN OR EQUAL TO                     //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Checks if the passed BigInt is greater than or equal in value
			to the called BigInt

		@param "n" of type BIGINT

		@return if the passed BigInt is greater than or equal in value
			to the called BigInt
	*/
	bool operator>=(const BigInt& n);

	/*
		Checks if the passed integer is greater than or equal in value
			to the called BigInt

		@param "n" of type INT

		@return if the passed integer is greater than or equal in value
			to the called BigInt
	*/
	bool operator>=(const int& n);

	/*
		Checks if the passed long is greater than or equal in value
			to the called BigInt

		@param "n" of type LONG

		@return if the passed long is greater than or equal in value
			to the called BigInt
	*/
	bool operator>=(const long& n);

	/*
		Checks if the passed float is greater than or equal in value
			to the called BigInt

		@param "n" of type FLOAT

		@return if the passed float is greater than or equal in value
			to the called BigInt
	*/
	bool operator>=(const float& n);

	/*
		Checks if the passed double is greater than or equal in value
			to the called BigInt

		@param "n" of type DOUBLE

		@return if the passed double is greater than or equal in value
			to the called BigInt
	*/
	bool operator>=(const double& n);

	/*
		Checks if the passed string is greater than or equal in value
			to the called BigInt

		@param "n" of type STD::STRING

		@return if the passed string is greater than or equal in value
			to the called BigInt
	*/
	bool operator>=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                       LESS THAN OR EQUAL TO                       //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Checks if the passed BigInt is less than or equal in value
			to the called BigInt

		@param "n" of type BIGINT

		@return if the passed BigInt is less than or equal in value
			to the called BigInt
	*/
	bool operator<=(const BigInt& n);

	/*
		Checks if the passed integer is less than or equal in value
			to the called BigInt

		@param "n" of type INT

		@return if the passed integer is less than or equal in value
			to the called BigInt
	*/
	bool operator<=(const int& n);

	/*
		Checks if the passed long is less than or equal in value
			to the called BigInt

		@param "n" of type LONG

		@return if the passed long is less than or equal in value
			to the called BigInt
	*/
	bool operator<=(const long& n);

	/*
		Checks if the passed float is less than or equal in value
			to the called BigInt

		@param "n" of type FLOAT

		@return if the passed float is less than or equal in value
			to the called BigInt
	*/
	bool operator<=(const float& n);

	/*
		Checks if the passed double is less than or equal in value
			to the called BigInt

		@param "n" of type DOUBLE

		@return if the passed double is less than or equal in value
			to the called BigInt
	*/
	bool operator<=(const double& n);

	/*
		Checks if the passed string is less than or equal in value
			to the called BigInt

		@param "n" of type STD::STRING

		@return if the passed string is less than or equal in value
			to the called BigInt
	*/
	bool operator<=(const std::string& n);


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                              ARITHMETICS                              //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                              ADDITION                             //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Finds the sum of the passed BigInt and the called BigInt

		@param "n" of type BIGINT

		@return the sum of the passed BigInt and the called BigInt
	*/
	BigInt operator+(const BigInt& n);

	/*
		Finds the sum of the passed integer and the called BigInt

		@param "n" of type INT

		@return the sum of the passed integer and the called BigInt
	*/
	BigInt operator+(const int& n);

	/*
		Finds the sum of the passed long and the called BigInt

		@param "n" of type LONG

		@return the sum of the passed long and the called BigInt
	*/
	BigInt operator+(const long& n);

	/*
		Finds the sum of the passed float and the called BigInt

		@param "n" of type FLOAT

		@return the sum of the passed float and the called BigInt
	*/
	BigInt operator+(const float& n);

	/*
		Finds the sum of the passed double and the called BigInt

		@param "n" of type DOUBLE

		@return the sum of the passed double and the called BigInt
	*/
	BigInt operator+(const double& n);

	/*
		Finds the sum of the passed string and the called BigInt

		@param "n" of type STD::STRING

		@return the sum of the passed string and the called BigInt
	*/
	BigInt operator+(const std::string& n);


	///////////////////////////////////////////////////////////////////////
	//                                                                   //
	//                            SUBTRACTION                            //
	//                                                                   //
	///////////////////////////////////////////////////////////////////////

	/*
		Finds the difference of the passed BigInt and the called BigInt

		@param "n" of type BIGINT

		@return the difference of the passed BigInt and the called BigInt
	*/
	BigInt operator-(const BigInt& n);

	/*
		Finds the difference of the passed integer and the called BigInt

		@param "n" of type INT

		@return the difference of the passed integer and the called BigInt
	*/
	BigInt operator-(const int& n);

	/*
		Finds the difference of the passed long and the called BigInt

		@param "n" of type LONG

		@return the difference of the passed long and the called BigInt
	*/
	BigInt operator-(const long& n);

	/*
		Finds the difference of the passed float and the called BigInt

		@param "n" of type FLOAT

		@return the difference of the passed float and the called BigInt
	*/
	BigInt operator-(const float& n);

	/*
		Finds the difference of the passed double and the called BigInt

		@param "n" of type DOUBLE

		@return the difference of the passed double and the called BigInt
	*/
	BigInt operator-(const double& n);

	/*
		Finds the difference of the passed string and the called BigInt

		@param "n" of type STD::STRING

		@return the difference of the passed string and the called BigInt
	*/
	BigInt operator-(const std::string& n);


	///////////////////////////////////////////////////////////////////////
	//                                                                   //
	//                           MULTIPLICATION                          //
	//                                                                   //
	///////////////////////////////////////////////////////////////////////

	/*
		Finds the product of the passed BigInt and the called BigInt

		@param "n" of type BIGINT

		@return the product of the passed BigInt and the called BigInt
	*/
	BigInt operator*(const BigInt& n);

	/*
		Finds the product of the passed integer and the called BigInt

		@param "n" of type INT

		@return the product of the passed integer and the called BigInt
	*/
	BigInt operator*(const int& n);

	/*
		Finds the product of the passed long and the called BigInt

		@param "n" of type LONG

		@return the product of the passed long and the called BigInt
	*/
	BigInt operator*(const long& n);

	/*
		Finds the product of the passed float and the called BigInt

		@param "n" of type FLOAT

		@return the product of the passed float and the called BigInt
	*/
	BigInt operator*(const float& n);

	/*
		Finds the product of the passed double and the called BigInt

		@param "n" of type DOUBLE

		@return the product of the passed double and the called BigInt
	*/
	BigInt operator*(const double& n);

	/*
		Finds the product of the passed string and the called BigInt

		@param "n" of type STD::STRING

		@return the product of the passed string and the called BigInt
	*/
	BigInt operator*(const std::string& n);


	///////////////////////////////////////////////////////////////////////
	//                                                                   //
	//                              DIVISION                             //
	//                                                                   //
	///////////////////////////////////////////////////////////////////////

	/*
		Finds the quotient of the passed BigInt and the called BigInt

		@param "n" of type BIGINT

		@return the quotient of the passed BigInt and the called BigInt
	*/
	BigInt operator/(const BigInt& n);

	/*
		Finds the quotient of the passed integer and the called BigInt

		@param "n" of type INT

		@return the quotient of the passed integer and the called BigInt
	*/
	BigInt operator/(const int& n);

	/*
		Finds the quotient of the passed long and the called BigInt

		@param "n" of type LONG

		@return the quotient of the passed long and the called BigInt
	*/
	BigInt operator/(const long& n);

	/*
		Finds the quotient of the passed float and the called BigInt

		@param "n" of type FLOAT

		@return the quotient of the passed float and the called BigInt
	*/
	BigInt operator/(const float& n);

	/*
		Finds the quotient of the passed double and the called BigInt

		@param "n" of type DOUBLE

		@return the quotient of the passed double and the called BigInt
	*/
	BigInt operator/(const double& n);

	/*
		Finds the quotient of the passed string and the called BigInt

		@param "n" of type STD::STRING

		@return the quotient of the passed string and the called BigInt
	*/
	BigInt operator/(const std::string& n);


	///////////////////////////////////////////////////////////////////////
	//                                                                   //
	//                               MODULO                              //
	//                                                                   //
	///////////////////////////////////////////////////////////////////////

	/*
		Finds the remainder of the passed BigInt and the called BigInt

		@param "n" of type BIGINT

		@return the remainder of the passed BigInt and the called BigInt
	*/
	BigInt operator%(const BigInt& n);

	/*
		Finds the remainder of the passed integer and the called BigInt

		@param "n" of type INT

		@return the remainder of the passed integer and the called BigInt
	*/
	BigInt operator%(const int& n);

	/*
		Finds the remainder of the passed long and the called BigInt

		@param "n" of type LONG

		@return the remainder of the passed long and the called BigInt
	*/
	BigInt operator%(const long& n);

	/*
		Finds the remainder of the passed float and the called BigInt

		@param "n" of type FLOAT

		@return the remainder of the passed float and the called BigInt
	*/
	BigInt operator%(const float& n);

	/*
		Finds the remainder of the passed double and the called BigInt

		@param "n" of type DOUBLE

		@return the remainder of the passed double and the called BigInt
	*/
	BigInt operator%(const double& n);

	/*
		Finds the remainder of the passed string and the called BigInt

		@param "n" of type STD::STRING

		@return the remainder of the passed string and the called BigInt
	*/
	BigInt operator%(const std::string& n);


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                       ARITHMETICS AND ASSIGNMENT                      //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                              ADDITION                             //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////  

	/*
		Finds and sets the sum of the passed BigInt and the called BigInt
			to the called BigInt

		@param "n" of type BigInt
	*/
	void operator+=(const BigInt& n);

	/*
		Finds and sets the sum of the passed integer and the called BigInt
			to the called BigInt

		@param "n" of type INT
	*/
	void operator+=(const int& n);

	/*
		Finds and sets the sum of the passed long and the called BigInt
			to the called BigInt

		@param "n" of type LONG
	*/
	void operator+=(const long& n);

	/*
		Finds and sets the sum of the passed float and the called BigInt
			to the called BigInt

		@param "n" of type FLOAT
	*/
	void operator+=(const float& n);

	/*
		Finds and sets the sum of the passed double and the called BigInt
			to the called BigInt

		@param "n" of type DOUBLE
	*/
	void operator+=(const double& n);

	/*
		Finds and sets the sum of the passed string and the called BigInt
			to the called BigInt

		@param "n" of type STD::STRING
	*/
	void operator+=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                            SUBTRACTION                            //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////  

	/*
		Finds and sets the difference of the passed BigInt and the called 
			BigInt to the called BigInt

		@param "n" of type BigInt
	*/
	void operator-=(const BigInt& n);

	/*
		Finds and sets the difference of the passed integer and the called 
			BigInt to the called BigInt

		@param "n" of type INT
	*/
	void operator-=(const int& n);

	/*
		Finds and sets the difference of the passed long and the called 
			BigInt to the called BigInt

		@param "n" of type LONG
	*/
	void operator-=(const long& n);

	/*
		Finds and sets the difference of the passed float and the called 
			BigInt to the called BigInt

		@param "n" of type FLOAT
	*/
	void operator-=(const float& n);

	/*
		Finds and sets the difference of the passed double and the called 
			BigInt to the called BigInt

		@param "n" of type DOUBLE
	*/
	void operator-=(const double& n);

	/*
		Finds and sets the difference of the passed string and the called 
			BigInt to the called BigInt

		@param "n" of type STD::STRING
	*/
	void operator-=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                           MULTIPLICATION                          //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////  

	/*
		Finds and sets the product of the passed BigInt and the called
			BigInt to the called BigInt

		@param "n" of type BigInt
	*/
	void operator*=(const BigInt& n);

	/*
		Finds and sets the product of the passed integer and the called
			BigInt to the called BigInt

		@param "n" of type INT
	*/
	void operator*=(const int& n);

	/*
		Finds and sets the product of the passed long and the called
			BigInt to the called BigInt

		@param "n" of type LONG
	*/
	void operator*=(const long& n);

	/*
		Finds and sets the product of the passed float and the called
			BigInt to the called BigInt

		@param "n" of type FLOAT
	*/
	void operator*=(const float& n);

	/*
		Finds and sets the product of the passed double and the called
			BigInt to the called BigInt

		@param "n" of type DOUBLE
	*/
	void operator*=(const double& n);

	/*
		Finds and sets the product of the passed string and the called
			BigInt to the called BigInt

		@param "n" of type STD::STRING
	*/
	void operator*=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                              DIVISION                             //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Finds and sets the quotient of the passed BigInt and the called
			BigInt to the called BigInt

		@param "n" of type BigInt
	*/
	void operator/=(const BigInt& n);

	/*
		Finds and sets the quotient of the passed integer and the called
			BigInt to the called BigInt

		@param "n" of type INT
	*/
	void operator/=(const int& n);

	/*
		Finds and sets the quotient of the passed long and the called
			BigInt to the called BigInt

		@param "n" of type LONG
	*/
	void operator/=(const long& n);

	/*
		Finds and sets the quotient of the passed float and the called
			BigInt to the called BigInt

		@param "n" of type FLOAT
	*/
	void operator/=(const float& n);

	/*
		Finds and sets the quotient of the passed double and the called
			BigInt to the called BigInt

		@param "n" of type DOUBLE
	*/
	void operator/=(const double& n);

	/*
		Finds and sets the quotient of the passed string and the called
			BigInt to the called BigInt

		@param "n" of type STD::STRING
	*/
	void operator/=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                               MODULO                              //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Finds and sets the remainder of the passed BigInt and the called
			BigInt to the called BigInt

		@param "n" of type BigInt
	*/
	void operator%=(const BigInt& n);

	/*
		Finds and sets the remainder of the passed integer and the called
			BigInt to the called BigInt

		@param "n" of type INT
	*/
	void operator%=(const int& n);

	/*
		Finds and sets the remainder of the passed long and the called
			BigInt to the called BigInt

		@param "n" of type LONG
	*/
	void operator%=(const long& n);

	/*
		Finds and sets the remainder of the passed float and the called
			BigInt to the called BigInt

		@param "n" of type FLOAT
	*/
	void operator%=(const float& n);

	/*
		Finds and sets the remainder of the passed double and the called
			BigInt to the called BigInt

		@param "n" of type DOUBLE
	*/
	void operator%=(const double& n);

	/*
		Finds and sets the remainder of the passed string and the called
			BigInt to the called BigInt

		@param "n" of type STD::STRING
	*/
	void operator%=(const std::string& n);


		///////////////////////////////////////////////////////////////////////
		//                                                                   //
		//                          INCREMENTATIONS                          //
		//                                                                   //
		///////////////////////////////////////////////////////////////////////

	/*
		Iterates the BigInt up by one
	*/
	void operator++();

	/*
		Iterates the BigInt down by one
	*/
	void operator--();
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   POWER                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/*
	Finds the solution to the equation (b) ^ (e)

	@param "b" of type INT
	@param "e" of type INT

	@param the solution to the equation (b) ^ (e)
*/
BigInt Big_pow(const int& b, const int& e);


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   OUTPUT                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

namespace std {
	/*
		Converts the passed BigInt to a string

		@param "n" of type BIGINT

		@return the string representation of "n"
	*/
	std::string to_string(BigInt n);
}

/*
	Overloading the "<<" operator

	@param "os" of type STD::OSTREAM
	@param "n of type BigInt

	@return "os" of type ostream with the string value of "obj" inserted
*/
std::ostream& operator<<(std::ostream& os, const BigInt& n);
