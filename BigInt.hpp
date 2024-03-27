// -*- LSST-C++ -*-

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// BIG namespace
namespace big {

	// Custom exception class
	class IntegerException : std::exception {
	public:

		// Constructor (primary)
		IntegerException(const std::string& msg) : _msg(msg) { }

		// what() overload
		virtual const char* what() const noexcept override {
			return _msg.c_str();
		}
	protected:
	private:
		std::string _msg;	// Error message
	};

	typedef int BLOCK;
	typedef long long BLOCK_PRODUCT;

	const BLOCK MIN = 0, MAX = 999999999;	// 0 to 1 billion
	const BLOCK BASE = 1000000000;		// Base (used for calculating blocks)
	const int DIGITS = 9;

	class Integer {
	public:

		//////////////////
		// CONSTRUCTORS //
		//////////////////

		/**
		* Default Constructor
		*/
		Integer();

		/**
		* Integer Constructor
		*
		* @param n integer to be used when creating the big::Integer object
		*/
		Integer(int n);

		/**
		* Long Constructor
		*
		* @param n long to be used when creating the big::Integer object
		*/
		Integer(long n);

		/**
		* LLong Constructor
		*
		* @param n long long to be used when creating the big::Integer object
		*/
		Integer(long long n);

		/**
		* uInt Constructor
		*
		* @param n unsigned integer to be used when creating the big::Integer object
		*/
		Integer(unsigned int n);

		/**
		* uLong Constructor
		*
		* @param n unsigned long to be used when creating the big::Integer object
		*/
		Integer(unsigned long n);

		/**
		* uLLong Constructor
		*
		* @param n unsigned long long to be used when creating the big::Integer object
		*/
		Integer(unsigned long long n);

		/**
		* Char Array Constructor
		*
		* @param str char array to be used when creating the big::Integer object
		*/
		Integer(const char* str);

		/**
		* std::string Constructor
		*
		* @param str std::string object to be used when creating the big::Integer object
		*/
		Integer(const std::string& str);

		/**
		* Deconstructor
		*/
		~Integer();

		/**
		* Copy Constructor
		*
		* @param o (Other) big::Integer object to be copied
		*/
		Integer(const Integer& o);

		/////////////////
		// ASSIGNMENTS //
		/////////////////

		/**
		* Integer Object Assignment
		*
		* @param o (Other) Integer object to be copied
		*/
		Integer& operator=(const Integer& o);

		/**
		* Int Assignment
		*
		* @param n integer to be used when copying
		*/
		Integer& operator=(int n);

		/**
		* Long Assignment
		*
		* @param n long to be used when copying
		*/
		Integer& operator=(long n);

		/**
		* LLong Assignment
		*
		* @param long long integer to be used when copying
		*/
		Integer& operator=(long long n);

		/**
		* uInt Assignment
		*
		* @param n unsigned integer to be used when copying
		*/
		Integer& operator=(unsigned int n);

		/**
		* uLong Assignment
		*
		* @param n unsigned long to be used when copying
		*/
		Integer& operator=(unsigned long n);

		/**
		* uLLong Assignment
		*
		* @param n unsigned long long to be used when copying
		*/
		Integer& operator=(unsigned long long n);

		/**
		* Char Array Assignment
		*
		* @param str const char* to be used when copying
		*/
		Integer& operator=(const char* str);

		/**
		* std::string Assignment
		*
		* @param str std::string to be used when copying
		*/
		Integer& operator=(const std::string& str);

		//////////////
		// IOSTREAM //
		//////////////

		/**
		* Ostream Operator Overload
		*/
		friend std::ostream& operator<<(std::ostream& os, const Integer& o);

		//////////////////
		// INEQUALITIES //
		//////////////////

		/**
		* Equivalence Operator Overload
		*
		* @param o (Other) Integer object being compared against
		*/
		bool operator==(const Integer& o) const;

		/**
		* Not-Equivalence Operator Overload
		*
		* @param o (Other) Integer object being compared against
		*/
		bool operator!=(const Integer& o) const;

		/**
		* Less-Than Operator Overload
		*
		* @param o (Other) Integer object being compared against
		*/
		bool operator<(const Integer& o) const;

		/**
		* Greater-Than Operator Overload
		*
		* @param o (Other) Integer object being compared against
		*/
		bool operator>(const Integer& o) const;

		/**
		* Less-Than or Equal-To Operator Overload
		*
		* @param o (Other) Integer object being compared against
		*/
		bool operator<=(const Integer& o) const;

		/**
		* Greater-Than or Equal-To Operator Overload
		*
		* @param o (Other) Integer object being compared against
		*/
		bool operator>=(const Integer& o) const;

		////////////////
		// ARITHMETIC //
		////////////////

		/**
		* Addition Overload
		*
		* @param o (Other) Integer object to be used when adding
		*/
		Integer operator+(const Integer& o) const;

		/**
		* Subtraction Overload
		*
		* @param o (Other) Integer object to be used when subtracting
		*/
		Integer operator-(const Integer& o) const;

		/**
		* Multiplication Overload (Object)
		*
		* @param o (Other) Integer object to be used when multiplying
		*/
		Integer operator*(const Integer& o) const;

		/**
		* Multiplication Overload (Block)
		*
		* @param n integer to be used when multiplying
		*/
		Integer operator*(BLOCK n);

		/**
		* Division Overload
		*
		* @param o (Other) Integer object to be used when dividing
		*/
		Integer operator/(const Integer& o) const;

		/**
		* Modulo Overload
		*
		* @param o (Other) Integer object to be used when finding remainder
		*/
		Integer operator%(const Integer& o) const;

		/**
		* Addition & Assignment Overload
		*
		* @param o (Other) Integer object to be used when adding
		*/
		const Integer& operator+=(const Integer& o);

		/**
		* Subtraction & Assignment Overload
		*
		* @param o (Other) Integer object to be used when subtracting
		*/
		const Integer& operator-=(const Integer& o);

		/**
		*  Multiplication & Assignment Overload (Object)
		*
		* @param o (Other) Integer object to be used when multiplying
		*/
		const Integer& operator*=(const Integer& o);

		/**
		*  Multiplication & Assignment Overload (Block)
		*
		* @param n integer to be used when multiplying
		*/
		const Integer& operator*=(BLOCK n);

		/**
		* Division & Assignment Overload
		*
		* @param o (Other) Integer object to be used when dividing
		*/
		const Integer& operator/=(const Integer& o);

		/**
		* Modulo & Assignment Overload
		*
		* @param o (Other) Integer object to be used when finding remainder
		*/
		const Integer& operator%=(const Integer& o);

		///////////
		// UNARY //
		///////////

		/**
		* Unary Negative
		*
		* @return A negative *this
		*/
		Integer operator-() const;

		/**
		* Pre-increment
		*/
		Integer operator++(int);

		/**
		* Pre-decrement
		*/
		Integer operator--(int);

		/**
		* Post-increment
		*/
		const Integer& operator++();

		/**
		* Post-decrement
		*/
		const Integer& operator--();

		/////////////
		// BITWISE //
		/////////////

		/**
		* Bitwise And Overload
		*
		* @param o (Other) Integer object to be used when performing the AND operation
		*/
		Integer operator&(Integer& o);

		/*
		* Bitwise Or Overload
		*
		* @param o (Other) Integer object to be used when performing the OR operation
		*/
		Integer operator|(Integer& o);

		/*
		* Bitwise Xor Overload
		*
		* @param o (Other) Integer object to be used when performing the XOR operation
		*/
		Integer operator^(Integer& o);

		/**
		* Shift Left Overload
		*
		* @param n Number of shifts
		*/
		Integer operator<<(int n);

		/**
		* Shift Right Overload
		*
		* @param n Number of shifts
		*/
		Integer operator>>(int n);

		//////////
		// MISC //
		//////////

		/**
		* Get Length (Chunk)
		* 
		* @returns the length of the num vector
		*/
		unsigned int getLength();

		/**
		* Get Length (Digits)
		* 
		* @returns the number of digits in the num vector
		*/
		unsigned int getDigitLength();

		/**
		* Get Chunk
		* 
		* @returns the chunk at a specified index
		*/
		unsigned int getChunk(unsigned int n);

	protected:
	private:
		std::vector<BLOCK> num;
		bool sign;

		/**
		* Construct From String
		* Sets big::Integer object data based on passed std::string or const char*
		*/
		void construct_from_string(std::string str);

		/**
		* Tweak Blocks
		*
		* Fixes any (over/under)flowing Block
		*/
		void tweak_blocks();

		/**
		* Trim Leading (zeros)
		*
		* Trims any leading zeros that are taking up unnecessary space
		*/
		void trim_leading();

		/**
		* Denominator In Remainder
		*
		* @param rem Remainder
		* @param den Denominator
		*/
		static BLOCK denominator_in_remainder(const Integer& rem, const Integer& den);

		/**
		* Get Binary
		*
		* @return bin Binary representation in string form
		*/
		std::string get_binary();

		/**
		* From Binary
		*
		* @return num Integer representation
		*/
		Integer from_binary(const std::string& str);
	};


	// Default Constructor
	Integer::Integer() {
		num = { 0 };	// Set default value to 0
		sign = false;
	}


	// Integer Constructor
	Integer::Integer(int n) {
		// If n == 0, sign is 0
		// If n  > 0, sign is 0
		// If n  < 0, sign is 1
		if (n == 0) { sign = 0; }
		else if (n > 0) { sign = 0; }
		else { sign = 1, n = -n; }

		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
	}


	// Long Constructor
	Integer::Integer(long n) {
		if (n == 0) { sign = 0; }
		else if (n > 0) { sign = 0; }
		else { sign = 1, n = -n; }

		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
	}


	// LLong Constructor
	Integer::Integer(long long n) {
		if (n == 0) { sign = 0; }
		else if (n > 0) { sign = 0; }
		else { sign = 1, n = -n; }

		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
	}


	// uInt Constructor
	Integer::Integer(unsigned int n) {
		sign = 0;
		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
	}


	// uLong Constructor
	Integer::Integer(unsigned long n) {
		sign = 0;
		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
	}


	// uLLong Constructor
	Integer::Integer(unsigned long long n) {
		sign = 0;
		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
	}


	// Char Array Constructor
	Integer::Integer(const char* str) {
		construct_from_string(str);
	}


	// std::string Constructor
	Integer::Integer(const std::string& str) {
		construct_from_string(str);
	}

	// Deconstructor
	Integer::~Integer() {
		num.clear();
	}


	// Copy Constructor
	Integer::Integer(const Integer& o) {
		num.clear();

		sign = o.sign;
		for (BLOCK i : o.num) {
			num.push_back(i);
		}
	}


	// Integer Object Assignment
	Integer& Integer::operator=(const Integer& o) {
		num.clear();

		sign = o.sign;
		for (BLOCK i : o.num) {
			num.push_back(i);
		}

		return *this;
	}


	// Int Assignment
	Integer& Integer::operator=(int n) {
		num.clear();

		if (n == 0) { sign = 0; }
		else if (n > 0) { sign = 0; }
		else { sign = 1, n = -n; }

		while (n > 0) {
			num.push_back(n % BASE);
			n /= BASE;
		}

		return *this;
	}


	// Long Assignment
	Integer& Integer::operator=(long n) {
		num.clear();

		if (n == 0) { sign = 0; }
		else if (n > 0) { sign = 0; }
		else { sign = 1, n = -n; }

		while (n > 0) {
			num.push_back(n % BASE);
			n /= BASE;
		}

		return *this;
	}


	// LLong Assignment
	Integer& Integer::operator=(long long n) {
		num.clear();

		if (n == 0) { sign = 0; }
		else if (n > 0) { sign = 0; }
		else { sign = 1, n = -n; }

		while (n > 0) {
			num.push_back(n % BASE);
			n /= BASE;
		}

		return *this;
	}


	// uInt Assignment
	Integer& Integer::operator=(unsigned int n) {
		num.clear();

		sign = 0;

		while (n > 0) {
			num.push_back(n % BASE);
			n /= BASE;
		}

		return *this;
	}


	// uLong Assignment
	Integer& Integer::operator=(unsigned long n) {
		num.clear();

		sign = 0;

		while (n > 0) {
			num.push_back(n % BASE);
			n /= BASE;
		}

		return *this;
	}


	// uLLong Assignment
	Integer& Integer::operator=(unsigned long long n) {
		num.clear();

		sign = 0;

		while (n > 0) {
			num.push_back(n % BASE);
			n /= BASE;
		}

		return *this;
	}


	// Char Array Assignment
	Integer& Integer::operator=(const char* c) {
		num.clear();

		construct_from_string(c);

		return *this;
	}


	// std::string Constructor
	Integer& Integer::operator=(const std::string& c) {
		num.clear();

		construct_from_string(c);

		return *this;
	}


	// Ostream Operator Overload
	std::ostream& operator<<(std::ostream& os, const Integer& o) {
		if (o.sign) { os << '-'; }	// Append negative sign

		bool first = true;
		for (int i = o.num.size() - 1; i > -1; --i) {
			// [1][000000001] == { 1, 1 }
			// Need to append leading zeros if this isn't the first block
			if (first) {
				os << o.num[i];
				first = false;
			}
			else {
				os << std::setfill('0') << std::setw(DIGITS) << o.num[i];
			}
		}

		return os;
	}


	// to_string()
	std::string to_string(const Integer& n) {
		std::ostringstream ss;
		ss << n;
		return ss.str();
	}


	// Equivalence Operator Overload
	bool Integer::operator==(const Integer& o) const {
		if (sign != o.sign) { return false; }
		if (num.size() != o.num.size()) { return false; }

		for (int i = 0; i < num.size(); ++i) {
			if (num[i] != o.num[i]) { return false; }
		}

		return true;
	}


	// Not-Equivalence Operator Overload
	bool Integer::operator!=(const Integer& o) const {
		if (sign != o.sign) { return true; }
		if (num.size() != o.num.size()) { return true; }

		for (int i = 0; i < num.size(); ++i) {
			if (num[i] != o.num[i]) { return true; }
		}

		return false;
	}


	// Less-Than Operator Overload
	bool Integer::operator<(const Integer& o) const {
		if (sign && !o.sign) { return true; }		// Negative vs Positive
		else if (!sign && o.sign) { return false; }	// Positive vs Negative

		if (num.size() < o.num.size()) { return sign ? false : true; }	// +Short < +Long
		if (num.size() > o.num.size()) { return sign ? true : false; }	// -Long < -Short

		for (int i = num.size() - 1; i > -1; --i) {
			if (num[i] < o.num[i]) { return sign ? false : true; }
			if (num[i] > o.num[i]) { return sign ? true : false; }
		}

		return false;	// ==
	}


	// Greater-Than Operator Overload
	bool Integer::operator>(const Integer& o) const {
		if (sign && !o.sign) { return false; }		// Negative vs Positive
		else if (!sign && o.sign) { return true; }	// Positive vs Negative

		if (num.size() < o.num.size()) { return sign ? true : false; }	// +Short !> +Long
		if (num.size() > o.num.size()) { return sign ? false : true; }	// -Long !> -Short

		for (int i = num.size() - 1; i > -1; --i) {
			if (num[i] < o.num[i]) { return sign ? true : false; }
			if (num[i] > o.num[i]) { return sign ? false : true; }
		}

		return false;	// ==
	}


	// Less-Than or Equal-To Operator Overload
	bool Integer::operator<=(const Integer& o) const {
		if (sign && !o.sign) { return true; }		// Negative vs Positive
		else if (!sign && o.sign) { return false; }	// Positive vs Negative

		if (num.size() < o.num.size()) { return sign ? false : true; }	// +Short < +Long
		if (num.size() > o.num.size()) { return sign ? true : false; }	// -Long < -Short

		for (int i = num.size() - 1; i > -1; --i) {
			if (num[i] < o.num[i]) { return sign ? false : true; }
			if (num[i] > o.num[i]) { return sign ? true : false; }
		}

		return true;	// ==
	}


	// Greater-Than or Equal-To Operator Overload
	bool Integer::operator>=(const Integer& o) const {
		if (sign && !o.sign) { return false; }		// Negative vs Positive
		else if (!sign && o.sign) { return true; }	// Positive vs Negative

		if (num.size() < o.num.size()) { return sign ? true : false; }	// +Short !> +Long
		if (num.size() > o.num.size()) { return sign ? false : true; }	// -Long !> -Short

		for (int i = num.size() - 1; i > -1; --i) {
			if (num[i] < o.num[i]) { return sign ? true : false; }
			if (num[i] > o.num[i]) { return sign ? false : true; }
		}

		return true;	// ==
	}


	// Addition Overload
	Integer Integer::operator+(const Integer& o) const {
		Integer result;

		size_t len = (num.size() > o.num.size() ? num.size() : o.num.size());
		result.num.resize(len, 0);

		for (int i = 0; i < len; ++i) {
			result.num[i] = (i < num.size() ? (sign ? -num[i] : num[i]) : 0) + (i < o.num.size() ? (o.sign ? -o.num[i] : o.num[i]) : 0);
		}

		result.tweak_blocks();

		return result;
	}


	// Subtraction Overload
	Integer Integer::operator-(const Integer& o) const {
		Integer result;

		size_t len = (num.size() > o.num.size() ? num.size() : o.num.size());
		result.num.resize(len, 0);

		for (int i = 0; i < len; ++i) {
			result.num[i] = (i < num.size() ? (sign ? -num[i] : num[i]) : 0) - (i < o.num.size() ? (o.sign ? -o.num[i] : o.num[i]) : 0);
		}

		result.tweak_blocks();

		return result;
	}


	// Multiplication Overload (Object)
	Integer Integer::operator*(const Integer& o) const {
		Integer result;
		result.num.resize(num.size() + o.num.size(), 0);
		BLOCK_PRODUCT carry = 0;
		int digi = 0;

		for (;; ++digi) {
			// Set signifigance of the carry
			result.num[digi] = carry % BASE;
			carry /= BASE;


			// Continually loop across the blocks
			bool found = false;
			for (int i = digi < o.num.size() ? 0 : digi - o.num.size() + 1; i < num.size() && i <= digi; ++i) {
				// Find block product
				BLOCK_PRODUCT prod = result.num[digi] + num[i] * (BLOCK_PRODUCT)o.num[digi - i];

				// Correct overflows
				if (prod > MAX || prod < -MAX) {
					carry += prod / BASE;
					prod %= BASE;
				}

				// Modify vector
				result.num[digi] = prod;
				found = true;
			}

			// Result found, do no more math
			if (!found) { break; }
		}

		// Handle any remaining carry blocks
		for (; carry > 0; ++digi) {
			result.num[digi] = carry % BASE;
			carry /= BASE;
		}

		result.tweak_blocks();

		// Calculated sign
		result.sign = (result.num.size() == 1 && result.num[0] == 0) ? false : (sign != o.sign);

		return result;
	}


	// Multiplication Overload (Block)
	Integer Integer::operator*(BLOCK n) {
		Integer result;

		BLOCK factor = abs(n);	// Factor to be multiplied (scale)
		BLOCK carry = 0;		// Carry block

		size_t len = num.size();
		result.num.resize(len, 0);

		for (int i = 0; i < len; ++i) {
			BLOCK_PRODUCT prod = num[i] * (BLOCK_PRODUCT)n + carry;

			if (prod > MAX || prod < -MAX) {	// Overflow fix
				carry = prod / BASE;
				prod %= BASE;
			}
			else { carry = 0; }

			result.num[i] = prod;
		}

		if (carry > 0) { result.num.push_back(carry); }	// Append any hanging carry

		result.tweak_blocks();
		result.sign = (result.num.size() == 1 && result.num[0] == 0) ? false : (sign != n < 0);

		return result;
	}


	// Division overload
	Integer Integer::operator/(const Integer& o) const {

		// Division by zero exception
		if (o.num.size() == 1 && o.num[0] == 0) {
			throw IntegerException("Division by zero");
		}


		// Declare the denominator(+), numerator(+), quotient, and remainder
		Integer denom = (o.sign ? -o : o), numer = (sign ? -*this : *this), quotient, remain;

		quotient.num.resize(numer.num.size(), 0);

		for (int i = numer.num.size() - 1; i > -1; --i) {
			remain.num.insert(remain.num.begin(), numer.num[i]);
			remain.tweak_blocks();
			BLOCK count = denominator_in_remainder(remain, denom);
			remain -= denom * count;
			quotient.num[i] += count;
		}

		quotient.tweak_blocks();

		quotient.sign = (quotient.num.size() == 1 && quotient.num[0] == 0) ? false : (sign != o.sign);

		return quotient;
	}


	// Modulo overload
	Integer Integer::operator%(const Integer& o) const {

		// Division by zero exception
		if (o.num.size() == 1 && o.num[0] == 0) {
			throw IntegerException("Division by zero");
		}

		// Declare the denominator(+), numerator(+), and remainder
		Integer denom = (o.sign ? -o : o), numer = (sign ? -*this : *this), remain;

		for (int i = numer.num.size() - 1; i > -1; --i) {
			remain.num.insert(remain.num.begin(), numer.num[i]);
			remain.tweak_blocks();
			BLOCK count = denominator_in_remainder(remain, denom);
			remain -= denom * count;
		}

		remain.tweak_blocks();

		remain.sign = (remain.num.size() == 1 && remain.num[0] == 0) ? false : (sign != o.sign);

		return remain;
	}


	// Addition & Assignment Overload
	const Integer& Integer::operator+=(const Integer& o) {
		size_t len = num.size();
		if (o.num.size() > len) {
			len = o.num.size();
			num.resize(len, 0);
		}

		for (int i = 0; i < len; ++i) {
			num[i] = (i < num.size() ? (sign ? -num[i] : num[i]) : 0) + (i < o.num.size() ? (o.sign ? -o.num[i] : o.num[i]) : 0);
		}

		tweak_blocks();

		return *this;
	}


	// Subtraction & Assignment Overload
	const Integer& Integer::operator-=(const Integer& o) {
		size_t len = num.size();
		if (o.num.size() > len) {
			len = o.num.size();
			num.resize(len, 0);
		}

		for (int i = 0; i < len; ++i) {
			num[i] = (i < num.size() ? (sign ? -num[i] : num[i]) : 0) - (i < o.num.size() ? (o.sign ? -o.num[i] : o.num[i]) : 0);
		}

		tweak_blocks();

		return *this;
	}


	// Multiplication & Assignment Overload (Object)
	const Integer& Integer::operator*=(const Integer& o) {
		// Cant think of an encompassing method of in place multiplication

		*this = *this * o;

		return *this;
	}


	// Multiplication & Assignment Overload (Block)
	const Integer& Integer::operator*=(BLOCK n) {
		// Cant think of an encompassing method of in place multiplication

		*this = *this * n;

		return *this;

	}


	// Division & Assignment Overload
	const Integer& Integer::operator/=(const Integer& o) {
		// Cant think of an encompassing method of in place division

		*this = *this / o;

		return *this;

	}


	// Modulo & Assignment Overload
	const Integer& Integer::operator%=(const Integer& o) {
		// Cant think of an encompassing method of in place modulo

		*this = *this % o;

		return *this;

	}


	// Unary Negative
	Integer Integer::operator-() const {
		Integer result = *this;
		result.sign = !sign;

		return result;
	}


	// Pre-increment
	Integer Integer::operator++(int) {
		Integer result = *this;
		result.num[0] += (sign ? -1 : 1);

		result.tweak_blocks();

		return result;
	}

	// Pre-decrement
	Integer Integer::operator--(int) {
		Integer result = *this;
		result.num[0] -= (sign ? -1 : 1);

		result.tweak_blocks();

		return result;
	}

	// Post-increment
	const Integer& Integer::operator++() {
		num[0] += (sign ? -1 : 1);
		tweak_blocks();

		return *this;
	}

	// Post-decrement
	const Integer& Integer::operator--() {
		num[0] -= (sign ? -1 : 1);
		tweak_blocks();

		return *this;
	}


	// Bitwise And Overload
	Integer Integer::operator&(Integer& o) {
		std::string result = "";
		std::string bin = get_binary();
		std::string o_bin = o.get_binary();

		while (bin.length() < o_bin.length()) {
			bin = "0" + bin;
		}
		while (o_bin.length() < bin.length()) {
			o_bin = "0" + o_bin;
		}

		for (int i = 0; i < bin.length(); ++i) {
			if (bin[i] == '1' && o_bin[i] == '1') {
				result += "1";
			}
			else {
				result += "0";
			}
		}

		return from_binary(result);
	}

	// Bitwise Or Overload
	Integer Integer::operator|(Integer& o) {
		std::string result = "";
		std::string bin = get_binary();
		std::string o_bin = o.get_binary();

		while (bin.length() < o_bin.length()) {
			bin = "0" + bin;
		}
		while (o_bin.length() < bin.length()) {
			o_bin = "0" + o_bin;
		}

		for (int i = 0; i < bin.length(); ++i) {
			if (bin[i] == '1' || o_bin[i] == '1') {
				result += "1";
			}
			else {
				result += "0";
			}
		}

		return from_binary(result);
	}


	// Bitwise Xor Overload
	Integer Integer::operator^(Integer& o) {
		std::string result = "";
		std::string bin = get_binary();
		std::string o_bin = o.get_binary();

		while (bin.length() < o_bin.length()) {
			bin = "0" + bin;
		}
		while (o_bin.length() < bin.length()) {
			o_bin = "0" + o_bin;
		}

		for (int i = 0; i < bin.length(); ++i) {
			if (bin[i] == '1' != o_bin[i] == '1') {
				result += "1";
			}
			else {
				result += "0";
			}
		}

		return from_binary(result);
	}


	// Shift Left Overload
	Integer Integer::operator<<(int n) {
		Integer result = *this;

		while (n > 0) {
			result /= 2;
			--n;
		}

		return result;
	}


	// Shift Right Overload
	Integer Integer::operator>>(int n) {
		Integer result = *this;

		while (n > 0) {
			result *= 2;
			--n;
		}

		return result;
	}


	//  Get Length (Chunk)
	unsigned int Integer::getLength() {
		return num.size();
	}


	// Get Length (Digits)
	unsigned int Integer::getDigitLength() {
		int digits = 0;
		for (int i = 0; i < num.size() - 1; ++i) {
			digits += 9;
		}

		int n = num[num.size() - 1];
		while (n > 0) {
			n %= 10;
			++digits;
		}

		return digits;
	}

	// Get Chunk
	unsigned int Integer::getChunk(unsigned int n) {
		return num[n];
	}





	// Construct From String
	void Integer::construct_from_string(std::string str) {
		if (str[0] == '-') {
			sign = 1;			// Negative check
			str = str.substr(1);
		}
		else { sign = 0; }

		// Remove leading zeros
		while (str[0] == '0') { str = str.substr(1); }
		if (str == "") { str = "0"; }	// Zero fix


		// No overhangs
		int i = str.length() - DIGITS;
		if (i > 0) {
			while (i >= 0) {
				num.push_back(std::stoi(str.substr(i, 9)));
				str = str.substr(0, i);
				i -= DIGITS;
			}
		}
		else {
			num.push_back(std::stoi(str));
			str = "";
		}


		// Remaining overhangs
		if (str.length() > 0) {
			num.push_back(std::stoi(str.substr(0, i + DIGITS)));
		}
	}


	// Tweak Blocks
	void Integer::tweak_blocks() {


		/**
		* Borrow / Carry
		*/
		for (int i = 0; i < num.size(); ++i) {
			if (num[i] > MAX || num[i] < -MAX) {
				if (i + 1 >= num.size()) {
					// Push back the carried block
					num.push_back(num[i] / BASE);
				}
				else {
					// Add the carry to the next index
					num[i + 1] += num[i] / BASE;
				}

				// Truncate the overflowed chunk
				num[i] %= BASE;
			}
		}


		/**
		* Fix any mismatched chunks
		* Depending on what operation preceded the execution of this function
		* many or all of the chunks may be negative and that breaks the storage
		* norm and all functionality
		*/
		bool is_signed = false;
		int i = num.size() - 1;
		while (i > -1) {
			if (num[i] != 0) {	// Set precedent for which side of the fix
				is_signed = num[i--] < 0;
				break;
			}
			--i;
		}

		// Yes I tried to ternary this, no I don't want to talk about it

		if (is_signed) {			// Negtative fix
			while (i > -1) {		// Loop across remaining blocks (less signifigant)
				if (num[i] > 0) {
					int ii = i + 1, iii = 0;	// Next index and offset

					while (ii < num.size() && num[ii] == 0) {	// Loop across remaining (more signifigant)

						++num[ii];
						num[i] -= BASE;

						while (iii > 0) {			// Flip sign
							num[i + iii] = -MAX;
							--iii;
						}

						++ii, ++iii;
					}
				}
				--i;
			}
		}
		else {	// Positive fix
			while (i > -1) {		// Loop across remaining blocks (less signifigant)
				if (num[i] < 0) {
					int ii = i + 1, iii = 0;	// Next index and offset

					while (ii < num.size() && num[ii] == 0) {	// Loop acros remaining (more signifigant)

						--num[ii];
						num[i] += BASE;

						while (iii > 0) {			// Flip sign
							num[i + iii] = MAX;
							--iii;
						}

						++ii, ++iii;
					}
				}
				--i;
			}
		}


		if (is_signed) {
			sign = !sign;
			for (int i = 0; i < num.size(); ++i) {
				num[i] = abs(num[i]);
			}
		}
		else {
			sign = sign;	// Doesnt change
		}


		trim_leading();	// Trim any remaining leading zeros
	}


	// Trim Leading (zeros)
	void Integer::trim_leading() {
		int i = num.size() - 1;
		while (i > 0) {
			if (num[i] == 0) {
				num.erase(num.begin() + i);
			}
			else { return; } // Skip the rest
			--i;
		}
	}

	// Small helper for the division/modulo helper
	div_t quot_and_rem(int num, int den) {
		div_t result;
		result.quot = num / den;
		result.rem = num % den;
		return result;
	}

	// Denominator In Remainder
	BLOCK Integer::denominator_in_remainder(const Integer& rem, const Integer& den) {
		BLOCK min = 0, max = MAX;

		while (max > min) {
			div_t test = quot_and_rem(min + max, 2);
			BLOCK avg = (test.rem) ? (test.quot + 1) : test.quot;

			// Hanging on max = (min + 1)

			Integer product = den * avg;

			if (rem == product) { return avg; }
			else if (rem > product) { min = avg; }
			else { max = avg - 1; }

		}

		return min;
	}


	// Get Binary
	std::string Integer::get_binary() {
		std::string bin = "";
		Integer num = *this;

		Integer power = 1;
		while (power <= num) {
			power *= 2;
		}

		while (power > 0) {
			if (power <= num) {
				num -= power;
				bin += "1";
			}
			else {
				bin += "0";
			}
			power /= 2;
		}

		// Trim any leading zeros
		int offset = bin.find('1');
		return bin.substr(offset);
	}


	// From Binary
	Integer Integer::from_binary(const std::string& str) {
		Integer num = 0;
		Integer power = 1;

		for (int i = str.length() - 1; i > -1; --i) {
			if (str[i] == '1') {
				num += power;

			}
			power *= 2;
		}

		return num;
	}

	////////////////
	// Non Member //
	////////////////

	// Power (Primitive)
	Integer pow(int base, int exp) {
		if (exp < 0) {
			throw IntegerException("Cannot raise base to a negative number");
		}
		else if (exp == 0 || base == 1) { return Integer(1); }
		Integer result = 1;

		while (exp > 0) {
			result *= base;
			--exp;
		}

		return result;
	}


	// Power (Object)
	Integer pow(const Integer& base, int exp) {
		if (exp < 0) {
			throw IntegerException("Cannot raise base to a negative number");
		}
		else if (exp == 0 || base == 1) { return Integer(1); }
		Integer result = 1;

		while (exp > 0) {
			result *= base;
			--exp;
		}

		return result;
	}

	// Random (range)
	Integer random(big::Integer min, big::Integer max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 1000000000);

		int minSize = min.getLength(), maxSize = max.getLength();
		int size;
		if (minSize == maxSize) { size = minSize; }
		else {
			size = rand() % (maxSize - minSize) + minSize;
		}

		int minChunk = min.getChunk(minSize - 1), maxChunk = max.getChunk(maxSize - 1);
		int diff = maxChunk - minChunk;
		if (diff == 0) { diff = 1; }

		Integer num;
		big::Integer newChunk;
		for (int i = 0; i < size - 1; ++i) {
			newChunk = dist(gen);
			if (i != 0) {
				newChunk *= BASE * i;
			}

			num += newChunk;
		}

		if (minSize == maxSize) {
			if (minChunk == maxChunk) { newChunk = minChunk; }
			else {
				newChunk = dist(gen) % (diff)+minChunk;
			}
		}
		else if (size < maxSize) {
			newChunk = dist(gen) % BASE;
		}

		if (size == 1) {
			num = newChunk;
		}
		else {
			num += (newChunk * (BASE * size));
		}

		//std::cout << "\n" << min << " " << num << " " << max << "\n";

		return num;
	}
}



#endif // BIGINT_HPP
