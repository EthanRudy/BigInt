#pragma once

#include "DynArr.h"
#include "CustExcep.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class BigInt {
private:

	/**
	* Dynamic Array object for binary storage
	* Starts off with 32 bits, for compatability with passed integers
	* Store in little endian
	*/
	DynArr<bool> bin;

	/**
	* Value that stores if a BigInteger stores a positive (1), negative (-1),
	* or zero(0) for easy shortcuts in arithmetic and output
	*/
	int8_t signum = 0;

	/**
	* Length counter for ease of access and resizing
	* When resizing, 4 bits are added for a compromise of space and speed
	*/
	int len = 32;

	/**
	* Karatsuba threshold
	*/
	const int KARATSUBA_THRESHOLD = 80;

	
	/**
	* Generates the binary representation of a number
	* 
	* Only ran when constructing a new BigInt object
	* 
	* @param n Number being converted
	*/
	void generate_binary(int n);


	/**
	* Trim
	* 
	* Trims all the non-relevant leading zeros
	* bits are store in 4-long "relevant" chunks for BCD conversion
	* when outputting
	*/
	void trim();

	/**
	* Trim All
	* 
	* Trims ALL the leading zeros
	* 
	* @param bin The binary array being modified
	* 
	* @return The modified array
	*/
	DynArr<bool> trim_a(DynArr<bool> bin);

	/**
	* Extend Binary
	* 
	* Adds another 4 bits to a binary array
	* Only called when absolutely necessary when carrying
	* If done improperly, BCD output will be incorrect
	* 
	* @param arr Binary array being extended
	*/
	void extend_binary(DynArr<bool> &arr);
	

	/**
	* Add (Dynamic Arrays)
	* 
	* Adds two binary Dynamic Arrays
	* 
	* @param a The first Dynamic Array
	* @param b The second Dynamic Array
	* @param k Used in Karatsuba
	* 
	* @return res The sum of Dynamic Arrays a and b
	*/
	DynArr<bool> add(DynArr<bool> a, DynArr<bool> b, bool k);

	/**
	* Subtract (Dynamic Arrays)
	* 
	* Subtracts two binary Dynamic Arrays
	* 
	* @param a The first Dynamic Array
	* @param b The second Dynamic Array
	* 
	* @return res The difference of Dynamic Arrays a and b
	*/
	DynArr<bool> sub(DynArr<bool> a, DynArr<bool> b);
	
	/**
	* Multiplication hub
	* 
	* Acts as a hub for the different methods of multiplication
	*/
	DynArr<bool> mult(DynArr<bool> a, DynArr<bool> b);



	/**
	* Long Multiplication (Dynamic Arrays)
	* 
	* Multiplies two binary Dynamic Arrays using long multiplication
	* 
	* @param a The first Dynamic Array
	* @param b The second Dynamic Array
	* 
	* @return res The product of Dynamic Arrays a and b
	*/
	DynArr<bool> longMult(DynArr<bool> a, DynArr<bool> b);

	/**
	* Karatsuba Multiplication
	* 
	* Multiplies two binary Dynamic Arrays using the Karatsuba method
	* 
	* @param a The first Dynamic Array
	* @param b The second Dynamic Array
	* 
	* @return res The product of Dynamic Arrays a and b
	*/
	DynArr<bool> karatsuba(DynArr<bool> a, DynArr<bool> b, int amount);


	/**
	* Fits Inside
	* 
	* Less than but with Dynamic Array objects
	* Only used in long division
	* 
	* @param a "Larger" Dynamic Array object
	* @param b "Smaller" Dynamic Array object
	* 
	* @return if b will "fit" into a
	*/
	bool fits(DynArr<bool> a, DynArr<bool> b);

	/**
	* Insert Bit
	* 
	* Inserts a bit into a position
	* 
	* @param arr DynArr being modified
	* @param p Position
	* @param v Bit
	*/
	void insert(DynArr<bool> &arr, int p, bool v);

public:

	/**
	* Integer Constructor
	* 
	* Generates a new BigInteger with the given integer
	* 
	* @param n The integer being stored
	*/
	BigInt(int n);

	/**
	* Byte array Constructor
	* 
	* @param b The byte array
	* @param l The length of the byte array
	* @param s The signum of the byte array
	*/
	BigInt(bool* b, int l, int8_t s);

	/**
	* Dynamic Array Constructor
	* 
	* @param b The Dynamic Array
	* @oaram s The signum of the Dynamic Array
	*/
	BigInt(DynArr<bool> b, int8_t s);

	/**
	* Copy Constructor
	* 
	* @param o The BigInteger to be hard copied
	*/
	BigInt(const BigInt& o);

	/**
	* Assignment Operator Overload
	*/
	BigInt operator=(const BigInt& o);

	/**
	* Deconstructor
	*/
	~BigInt();
	

	/**
	* Sign function
	* 
	* Returns the value stored in signum
	* 
	* @return signum
	*/
	uint8_t sign();

	/**
	* Size function
	* 
	* Returns the size of the object
	* 
	* @return size
	*/
	int size();

	/**
	* To String
	*
	* Only used to call the overload
	*/
	std::string to_string();

	/**
	* To String with Percentage
	* 
	* Only used to call the overload
	*/
	std::string to_string_p();

	/**
	* Compare opeator overload
	* 
	* Compares this against another BigInteger and returns if they store the
	* same value
	* 
	* @param o The other BigInteger
	* 
	* @return If the two BigIntegers store the same value
	*/
	bool operator==(const BigInt& o);

	/**
	* Inverse Comparare operator overload
	* 
	* Inverselt compares this against another BigInteger and returns if they
	* store the same value
	* 
	* @param o The other BigInteger
	* @return If the two BigIntegers store the same value
	*/
	bool operator!=(const BigInt& o);

	/**
	* Less-Than operator overload
	* 
	* Compares this against another BigInteger and returns if this stores
	* a lesser value
	* 
	* @param o The other BigInt
	* 
	* @return If this stores a lesser value than the other BigInteger
	*/
	bool operator<(const BigInt& o);

	/**
	* Greater-Than operator overload
	* 
	* Compares this against another BigInteger and returns if this sotres
	* a greater value
	* 
	* @param o The other BigInteger
	* 
	* @return If this stores a greater value than the other BigInteger
	*/
	bool operator>(const BigInt& o);

	/**
	* Less-Than or Equal-To overload
	* 
	* Compares this against another BigInteger and returns if this stores 
	* a lesser or equal value
	* 
	* @param o The other BigInteger
	* 
	* @return if this stores a lesser or equal value compared to the 
	* other BigInteger
	*/
	bool operator<=(const BigInt& o);

	/**
	* Greater-Than or Equal-To overload
	* 
	* Compares this afainst another BigInteger and returns if this stores
	* a greater or equal value
	* 
	* @param o The other BigInteger
	* 
	* @return If this stores a greater or equal value compared to the 
	* other BigInteger
	*/
	bool operator>=(const BigInt& o);

	/**
	* Addition
	* 
	* Adds the values of two BigIntegers
	* 
	* @param o The other BigInteger
	* 
	* @return The sum of the BigIntegers
	*/
	BigInt add(BigInt o);

	/**
	* Subtraction
	* 
	* Subtracts the values of two BigIntegers
	* 
	* @param o The other BigInteger
	* 
	* @return The difference of the BigIntegers
	*/
	BigInt sub(BigInt o);

	/**
	* Multiplication
	* 
	* Multiplies the values of two BigIntegers
	* 
	* @param o The other BigInteger
	* 
	* @return The product of the BigIntegers
	*/
	BigInt mult(BigInt o);

	/**
	* Division
	* 
	* Divides the values of two BigIntegers
	* 
	* @param o The other BigInteger
	* 
	* @return The quotient of the BigIntegers
	*/
	BigInt div(BigInt o);
	
	/**
	* Power
	* 
	* @param n Exponent
	* 
	* @return The resulting product
	*/
	BigInt pow(int n);

	// For ostream overload
	friend std::ostream& operator<<(std::ostream& os, const BigInt& n);
};


namespace std {
	/**
	* To String overload
	*
	* Generates a string representation of a BigInteger using
	* BCD and the double dabble method
	*
	* @return res The resulting string
	*/
	std::string to_string(BigInt n);

	/**
	* To String with percentage
	* 
	* Generates a string representation of a BigInteger using
	* BCD and the double dabble method
	* 
	* @return res The resulting string
	*/
	std::string to_string_p(BigInt n);
}
