// Initialization for the BigInt class
// @file BigInt.cpp
// @author Ethan Rudy
// @version 1.0

#include "BigInt.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             PRIVATE FUNCTIONS                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Fills the data for a BigInt
void BigInt::fill(std::string n) {
	if (n[0] == '-') {
		this->negative = true;
		n = n.substr(1);
	}
	this->len = n.length();
	for (int i = 0; i < len; ++i) {
		this->num = n[i] + num;
	}
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                                HELPERS                                //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// String constructor with negative override
BigInt::BigInt(const std::string& n, const bool& neg, const bool& r) {
	this->len = n.length();
	if (r) {
		this->num = n;
	}
	else {
		for (int i = this->len - 1; i > -1; --i) {
			this->num += n[i];
		}
	}
	this->negative = neg;

}

// String constructor with negative override
std::string BigInt::add(std::string n1, std::string n2) {
	int l1 = n1.length();
	int l2 = n2.length();
	if (l1 < l2) {
		return add(n2, n1);
	}
	std::string strsum = "";
	int carry = 0;
	for (int i = 0; i < l1; ++i) {
		int dSum;
		if (i < l2) {
			dSum = (n1[i] - '0') + (n2[i] - '0') + carry;
		}
		else {
			dSum = (n1[i] - '0') + carry;
		}
		if (dSum > 9) {
			carry = 1;
			dSum -= 10;
		}
		else {
			carry = 0;
		}
		strsum += std::to_string(dSum);
	}
	if (carry > 0) {
		strsum += "1";
	}
	return strsum;
}

// Finds the difference of the the two passed strings
std::string BigInt::subtract(std::string n1, std::string n2) {
	std::string strdiff = "";
	int l1 = n1.length();
	int l2 = n2.length();
	int borrow = 0;
	for (int i = 0; i < l1; ++i) {
		int dDiff;
		if (i < l2) {
			dDiff = (n1[i] - '0') - (n2[i] - '0') - borrow;
		}
		else {
			dDiff = (n1[i] - '0') - borrow;
		}
		if (dDiff < 0) {
			dDiff += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		strdiff += std::to_string(dDiff);
	}
	return trim0(strdiff);
}

// Recursively finds the product of the two passed strings
std::string BigInt::karatsuba(std::string n1, std::string n2) {
	int l1 = n1.length();
	int l2 = n2.length();
	int lenDiff = l1 - l2;

	n2 = shift(n2, lenDiff);

	if (l1 == 1) {
		std::string t = std::to_string((n1[0] - '0') * (n2[0] - '0'));
		std::reverse(t.begin(), t.end());
		return t;
	}
	int mid = ceil(l1 / 2.0);

	std::string x_L = n1.substr(0, mid);
	std::string x_H = n1.substr(mid, l1);

	std::string y_L = n2.substr(0, mid);
	std::string y_H = n2.substr(mid, l1);

	std::string a = karatsuba(x_H, y_H);
	std::string d = karatsuba(x_L, y_L);

	std::string xSum = add(x_L, x_H);
	std::string ySum = add(y_L, y_H);

	std::string e = subtract(subtract(karatsuba(xSum, ySum), a), d);

	a = pow10(a, mid * 2);
	e = pow10(e, mid);

	return trim0((add(add(a, e), d)));
}

// Shifts the number to the right by inserting (filler) zeros
std::string BigInt::shift(std::string n, int amount) {
	for (int i = 0; i < amount; ++i) {
		n += "0";
	}
	return n;
}

// Shifts the number to the left by inserting (x10) zeros
std::string BigInt::pow10(std::string n, int amount) {
	for (int i = 0; i < amount; ++i) {
		n = "0" + n;
	}
	return n;
}

// Trims the leading zeros of a number
std::string BigInt::trim0(std::string n) {
	int length = n.length();
	while (n[length - 1] == '0' && length > 1) {
		n = n.substr(0, n.length() - 1);
		length = n.length();
	}
	return n;
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTORS                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Default Constructor
BigInt::BigInt() {
	fill("0");
};

// Integer Constructor
BigInt::BigInt(const int& n) {
	fill(std::to_string(n));
}

// Long Constructor
BigInt::BigInt(const long& n) {
	fill(std::to_string(n));
}

// Float Constructor
BigInt::BigInt(const float& n) {
	fill(std::to_string((int)n));
}

// Double Constructor
BigInt::BigInt(const double& n) {
	fill(std::to_string((int)n));
}

// String Constructor
BigInt::BigInt(const std::string& n) {
	fill(n);
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             ACCESOR FUNCTIONS                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Gets the string of digits of the called BigInt
std::string BigInt::get_str() {
	return this->num;
}

// Gets the length of the called BigInt
int BigInt::length() {
	return this->len;
}

// Gets whether the called BigInt is negative
bool BigInt::is_negative() {
	return this->negative;
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             BOOLEAN OPERATORS                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                                EQUAL TO                               //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Checks if the passed BigInt is equal in value to the called BigInt
bool BigInt::operator==(const BigInt& n) {
	if (this->len != n.len) {
		return false;
	}
	if (this->negative != n.negative) {
		return false;
	}
	for (int i = 0; i < n.len; ++i) {
		if (this->num[i] != n.num[i]) {
			return false;
		}
	}
	return true;
}

// Checks if the passed integer is equal in value to the called BigInt
bool BigInt::operator==(const int& n) {
	return operator==(BigInt(n));
}

// Checks if the passed long is equal in value to the called BigInt
bool BigInt::operator==(const long& n) {
	return operator==(BigInt(n));
}

// Checks if the passed float is equal in value to the called BigInt
bool BigInt::operator==(const float& n) {
	return operator==(BigInt(n));
}

// Checks if the passed double is equal in value to the called BigInt
bool BigInt::operator==(const double& n) {
	return operator==(BigInt(n));
}

// Checks if the passed string is equal in value to the called BigInt
bool BigInt::operator==(const std::string& n) {
	return operator==(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                              GREATER THAN                             //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Checks if the passed BigInt is greater than in value to the called BigInt
bool BigInt::operator>(const BigInt& n) {
	if (this->len > n.len) return true;
	if (this->len < n.len) return false;
	for (int i = this->len - 1; i > -1; --i) {
		if (this->num[i] > n.num[i]) {
			return true;
		}
		else if (this->num[i] < n.num[i]) {
			return false;
		}
	}
	return false;
}

// Checks if the passed integer is greater than in value to the called BigInt
bool BigInt::operator>(const int& n) {
	return operator>(BigInt(n));
}

// Checks if the passed long is greater than in value to the called BigInt
bool BigInt::operator>(const long& n) {
	return operator>(BigInt(n));
}

// Checks if the passed float is greater than in value to the called BigInt
bool BigInt::operator>(const float& n) {
	return operator>(BigInt(n));
}

// Checks if the passed double is greater than in value to the called BigInt
bool BigInt::operator>(const double& n) {
	return operator>(BigInt(n));
}

// Checks if the passed string is greater than in value to the called BigInt
bool BigInt::operator>(const std::string& n) {
	return operator>(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                               LESS THAN                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Checks if the passed BigInt is less than in value to the called BigInt
bool BigInt::operator<(const BigInt& n) {
	if (this->len > n.len) return false;
	if (this->len < n.len) return true;
	for (int i = this->len - 1; i > -1; --i) {
		if (this->num[i] > n.num[i]) {
			return false;
		}
		else if (this->num[i] < n.num[i]) {
			return true;
		}
	}
	return false;
}

// Checks if the passed integer is less than in value to the called BigInt
bool BigInt::operator<(const int& n) {
	return operator<(BigInt(n));
}

// Checks if the passed long is less than in value to the called BigInt
bool BigInt::operator<(const long& n) {
	return operator<(BigInt(n));
}

// Checks if the passed float is less than in value to the called BigInt
bool BigInt::operator<(const float& n) {
	return operator<(BigInt(n));
}

// Checks if the passed double is less than in value to the called BigInt
bool BigInt::operator<(const double& n) {
	return operator<(BigInt(n));
}

// Checks if the passed string is less than in value to the called BigInt
bool BigInt::operator<(const std::string& n) {
	return operator<(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                              NOT EQUAL TO                             //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Checks if the passed BigInt is not equal in value to the called BigInt
bool BigInt::operator!=(const BigInt& n) {
	return !operator==(n);
}

// Checks if the passed integer is not equal in value to the called BigInt
bool BigInt::operator!=(const int& n) {
	return operator!=(BigInt(n));
}

// Checks if the passed long is not equal in value to the called BigInt
bool BigInt::operator!=(const long& n) {
	return operator!=(BigInt(n));
}

// Checks if the passed float is not equal in value to the called BigInt
bool BigInt::operator!=(const float& n) {
	return operator!=(BigInt(n));
}

// Checks if the passed double is not equal in value to the called BigInt
bool BigInt::operator!=(const double& n) {
	return operator!=(BigInt(n));
}

// Checks if the passed string is not equal in value to the called BigInt
bool BigInt::operator!=(const std::string& n) {
	return operator!=(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                        GREATER THAN OR EQUAL TO                       //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Checks if the passed BigInt is greater than or equal in value to the 
//	called BigInt
bool BigInt::operator>=(const BigInt& n) {
	return (operator==(n) || operator>(n));
}

// Checks if the passed integer is greater than or equal in value to the 
//	called BigInt
bool BigInt::operator>=(const int& n) {
	return operator>=(BigInt(n));
}

// Checks if the passed long is greater than or equal in value to the 
//	called BigInt
bool BigInt::operator>=(const long& n) {
	return operator>=(BigInt(n));
}

// Checks if the passed float is greater than or equal in value to the 
//	called BigInt
bool BigInt::operator>=(const float& n) {
	return operator>=(BigInt(n));
}

// Checks if the passed double is greater than or equal in value to the 
//	called BigInt
bool BigInt::operator>=(const double& n) {
	return operator>=(BigInt(n));
}

// Checks if the passed string is greater than or equal in value to the 
//	called BigInt
bool BigInt::operator>=(const std::string& n) {
	return operator>=(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                         LESS THAN OR EQUAL TO                         //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Checks if the passed BigInt is less than or equal in value to the 
// called BigInt
bool BigInt::operator<=(const BigInt& n) {
	return (operator==(n) || operator>(n));
}

// Checks if the passed integer is less than or equal in value to the 
// called BigInt
bool BigInt::operator<=(const int& n) {
	return operator<=(BigInt(n));
}

// Checks if the passed long is less than or equal in value to the 
// called BigInt
bool BigInt::operator<=(const long& n) {
	return operator<=(BigInt(n));
}

// Checks if the passed float is less than or equal in value to the 
// called BigInt
bool BigInt::operator<=(const float& n) {
	return operator<=(BigInt(n));
}

// Checks if the passed double is less than or equal in value to the 
// called BigInt
bool BigInt::operator<=(const double& n) {
	return operator<=(BigInt(n));
}

// Checks if the passed string is less than or equal in value to the 
// called BigInt
bool BigInt::operator<=(const std::string& n) {
	return operator<=(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                ARITHMETICS                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                                ADDITION                               //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Finds the sum of the passed BigInt and the called BigInt
BigInt BigInt::operator+(const BigInt& n) {
	if (n.negative != this->negative) {
		if (this->negative) {
			return BigInt(subtract(n.num, this->num), operator<(n), 1);
		}
		return BigInt(subtract(this->num, n.num), operator<(n), 1);
	}
	return BigInt(add(this->num, n.num), this->negative, 1);
}

// Finds the sum of the passed integer and the called BigInt
BigInt BigInt::operator+(const int& n) {
	return operator+(BigInt(n));
}

// Finds the sum of the passed long and the called BigInt
BigInt BigInt::operator+(const long& n) {
	return operator+(BigInt(n));
}

// Finds the sum of the passed float and the called BigInt
BigInt BigInt::operator+(const float& n) {
	return operator+(BigInt(n));
}

// Finds the sum of the passed double and the called BigInt
BigInt BigInt::operator+(const double& n) {
	return operator+(BigInt(n));
}

// Finds the sum of the passed string and the called BigInt
BigInt BigInt::operator+(const std::string& n) {
	return operator+(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                              SUBTRACTION                              //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Finds the difference of the passed BigInt and the called BigInt
BigInt BigInt::operator-(const BigInt& n) {
	if (n.negative != this->negative) {
		if (this->negative) {
			return BigInt(add(this->num, n.num), this->negative, 1);
		}
		return BigInt(add(n.num, this->num), this->negative, 1);
	}
	BigInt ans;
	if (operator<(n)) {
		ans = BigInt(subtract(n.num, this->num), !this->negative, 1);
	}
	else {
		ans = BigInt(subtract(this->num, n.num), this->negative, 1);
	}
	if (ans.num == "0") {
		ans.negative = false;
	}
	return ans;
}

// Finds the difference of the passed integer and the called BigInt
BigInt BigInt::operator-(const int& n) {
	return operator-(BigInt(n));
}

// Finds the difference of the passed long and the called BigInt
BigInt BigInt::operator-(const long& n) {
	return operator-(BigInt(n));
}

// Finds the difference of the passed float and the called BigInt
BigInt BigInt::operator-(const float& n) {
	return operator-(BigInt(n));
}

// Finds the difference of the passed double and the called BigInt
BigInt BigInt::operator-(const double& n) {
	return operator-(BigInt(n));
}

// Finds the difference of the passed string and the called BigInt
BigInt BigInt::operator-(const std::string& n) {
	return operator-(BigInt(n));
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                             MULTIPLICATION                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Finds the product of the passed BigInt and the called BigInt
BigInt BigInt::operator*(const BigInt& n) {
	if (this->negative == n.negative) {
		return BigInt(karatsuba(this->num, n.num), 0, 1);
	}
	return BigInt(karatsuba(this->num, n.num), 1, 1);
}

// Finds the product of the passed integer and the called BigInt
BigInt BigInt::operator*(const int& n) {
	return operator*(BigInt(n));
}

// Finds the product of the passed long and the called BigInt
BigInt BigInt::operator*(const long& n) {
	return operator*(BigInt(n));
}

// Finds the product of the passed float and the called BigInt
BigInt BigInt::operator*(const float& n) {
	return operator*(BigInt(n));
}

// Finds the product of the passed double and the called BigInt
BigInt BigInt::operator*(const double& n) {
	return operator*(BigInt(n));
}

// Finds the product of the passed string and the called BigInt
BigInt BigInt::operator*(const std::string& n) {
	return operator*(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                                DIVISION                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Finds the quotient of the passed BigInt and the called BigInt
BigInt BigInt::operator/(const BigInt& n) {
	if (operator<(n)) {
		return BigInt("0");
	}
	BigInt posN = n;
	posN.negative = false;
	int l1 = this->len;
	int l2 = n.len;
	std::string strQuo = "";
	int place = 1;
	std::string slice = this->num.substr(this->len - 1);
	for (int i = l1 - 1; i > -1; --i) {
		int timesIn = 0;
		while (BigInt(slice).operator>=(posN)) {
			slice = subtract(slice, n.num);
			timesIn++;
		}
		strQuo = std::to_string(timesIn) + strQuo;
		if (i != 0) {
			place++;
			slice = trim0(this->num[this->len - place] + slice);
		}
	}
	BigInt quotient = BigInt(trim0(strQuo), 0, 1);
	if (this->negative != n.negative) {
		quotient.negative = true;
	}
	return quotient;
}

// Finds the quotient of the passed integer and the called BigInt
BigInt BigInt::operator/(const int& n) {
	return operator/(BigInt(n));
}

// Finds the quotient of the passed long and the called BigInt
BigInt BigInt::operator/(const long& n) {
	return operator/(BigInt(n));
}

// Finds the quotient of the passed float and the called BigInt
BigInt BigInt::operator/(const float& n) {
	return operator/(BigInt(n));
}

// Finds the quotient of the passed double and the called BigInt
BigInt BigInt::operator/(const double& n) {
	return operator/(BigInt(n));
}

// Finds the quotient of the passed string and the called BigInt
BigInt BigInt::operator/(const std::string& n) {
	return operator/(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                                 MODULO                                //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

// Finds the remainder of the passed BigInt and the called BigInt
BigInt BigInt::operator%(const BigInt& n) {
	if (operator<(n) || this->negative || n.negative) {
		return BigInt("0");
	}
	int l1 = this->len;
	int l2 = n.len;
	int place = 1;
	std::string slice = this->num.substr(this->len - 1);
	for (int i = l1 - 1; i > -1; --i) {
		while (BigInt(slice).operator>=(n)) {
			slice = subtract(slice, n.num);
		}
		if (i != 0) {
			place++;
			slice = trim0(this->num[this->len - place] + slice);
		}
	}
	return BigInt(slice);
}

// Finds the remainder of the passed integer and the called BigInt
BigInt BigInt::operator%(const int& n) {
	return operator%(BigInt(n));
}

// Finds the remainder of the passed long and the called BigInt
BigInt BigInt::operator%(const long& n) {
	return operator%(BigInt(n));
}

// Finds the remainder of the passed float and the called BigInt
BigInt BigInt::operator%(const float& n) {
	return operator%(BigInt(n));
}

// Finds the remainder of the passed double and the called BigInt
BigInt BigInt::operator%(const double& n) {
	return operator%(BigInt(n));
}

// Finds the remainder of the passed string and the called BigInt
BigInt BigInt::operator%(const std::string& n) {
	return operator%(BigInt(n));
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                         ARITHMETICS AND ASSIGNMENT                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                                ADDITION                               //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Finds and sets the sum of the passed BigInt and the called BigInt
//		to the called BigInt
void BigInt::operator+=(const BigInt& n) {
	*this = operator+(n);
}

// Finds and sets the sum of the passed integer and the called BigInt
//		to the called BigInt
void BigInt::operator+=(const int& n) {
	*this = operator+(n);
}

// Finds and sets the sum of the passed long and the called BigInt
//		to the called BigInt
void BigInt::operator+=(const long& n) {
	*this = operator+(n);
}

// Finds and sets the sum of the passed float and the called BigInt
//		to the called BigInt
void BigInt::operator+=(const float& n) {
	*this = operator+(n);
}

// Finds and sets the sum of the passed double and the called BigInt
//		to the called BigInt
void BigInt::operator+=(const double& n) {
	*this = operator+(n);
}

// Finds and sets the sum of the passed string and the called BigInt
//		to the called BigInt
void BigInt::operator+=(const std::string& n) {
	*this = operator+(n);
}


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                              SUBTRACTION                              //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Finds and sets the difference of the passed BigInt and the called 
//		BigInt to the called BigInt
void BigInt::operator-=(const BigInt& n) {
	*this = operator-(n);
}

// Finds and sets the difference of the passed integer and the called 
//		BigInt to the called BigInt
void BigInt::operator-=(const int& n) {
	*this = operator-(n);
}

// Finds and sets the difference of the passed long and the called 
//		BigInt to the called BigInt
void BigInt::operator-=(const long& n) {
	*this = operator-(n);
}

// Finds and sets the difference of the passed float and the called 
//		BigInt to the called BigInt
void BigInt::operator-=(const float& n) {
	*this = operator-(n);
}

// Finds and sets the difference of the passed double and the called 
//		BigInt to the called BigInt
void BigInt::operator-=(const double& n) {
	*this = operator-(n);
}

// Finds and sets the difference of the passed string and the called 
//		BigInt to the called BigInt
void BigInt::operator-=(const std::string& n) {
	*this = operator-(n);
}

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                             MULTIPLICATION                            //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Finds and sets the product of the passed BigInt and the called 
//		BigInt to the called BigInt
void BigInt::operator*=(const BigInt& n) {
	*this = operator*(n);
}

// Finds and sets the product of the passed integer and the called 
//		BigInt to the called BigInt
void BigInt::operator*=(const int& n) {
	*this = operator*(n);
}

// Finds and sets the product of the passed long and the called 
//		BigInt to the called BigInt
void BigInt::operator*=(const long& n) {
	*this = operator*(n);
}

// Finds and sets the product of the passed float and the called 
//		BigInt to the called BigInt
void BigInt::operator*=(const float& n) {
	*this = operator*(n);
}

// Finds and sets the product of the passed double and the called 
//		BigInt to the called BigInt
void BigInt::operator*=(const double& n) {
	*this = operator*(n);
}

// Finds and sets the product of the passed string and the called 
//		BigInt to the called BigInt
void BigInt::operator*=(const std::string& n) {
	*this = operator*(n);
}

	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                                DIVISION                               //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Finds and sets the quotient of the passed BigInt and the called 
//		BigInt to the called BigInt
void BigInt::operator/=(const BigInt& n) {
	*this = operator/(n);
}

// Finds and sets the quotient of the passed integer and the called 
//		BigInt to the called BigInt
void BigInt::operator/=(const int& n) {
	*this = operator/(n);
}

// Finds and sets the quotient of the passed long and the called 
//		BigInt to the called BigInt
void BigInt::operator/=(const long& n) {
	*this = operator/(n);
}

// Finds and sets the quotient of the passed float and the called 
//		BigInt to the called BigInt
void BigInt::operator/=(const float& n) {
	*this = operator/(n);
}

// Finds and sets the quotient of the passed double and the called 
//		BigInt to the called BigInt
void BigInt::operator/=(const double& n) {
	*this = operator/(n);
}

// Finds and sets the quotient of the passed string and the called 
//		BigInt to the called BigInt
void BigInt::operator/=(const std::string& n) {
	*this = operator/(n);
}


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                                 MODULO                                //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Finds and sets the remainder of the passed BigInt and the called 
//		BigInt to the called BigInt
void BigInt::operator%=(const BigInt& n) {
	*this = operator%(n);
}

// Finds and sets the remainder of the passed integer and the called 
//		BigInt to the called BigInt
void BigInt::operator%=(const int& n) {
	*this = operator%(n);
}

// Finds and sets the remainder of the passed long and the called 
//		BigInt to the called BigInt
void BigInt::operator%=(const long& n) {
	*this = operator%(n);
}

// Finds and sets the remainder of the passed float and the called 
//		BigInt to the called BigInt
void BigInt::operator%=(const float& n) {
	*this = operator%(n);
}

// Finds and sets the remainder of the passed double and the called 
//		BigInt to the called BigInt
void BigInt::operator%=(const double& n) {
	*this = operator%(n);
}

// Finds and sets the remainder of the passed string and the called 
//		BigInt to the called BigInt
void BigInt::operator%=(const std::string& n) {
	*this = operator%(n);
}


	///////////////////////////////////////////////////////////////////////////
	//                                                                       //
	//                            INCREMENTATIONS                            //
	//                                                                       //
	///////////////////////////////////////////////////////////////////////////

// Iterates the BigInt up by one
void BigInt::operator++() {
	*this = operator+(1);
}

// Iterates the BigInt down by one
void BigInt::operator--() {
	*this = operator-(1);
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   POWER                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Finds the solution to the equation (b) ^ (e)
BigInt Big_pow(const int& b, const int& e) {
	BigInt base = BigInt(b);
	BigInt result = BigInt(1);
	for (int i = 0; i < e; ++i) {
		result.operator*=(base);
	}
	return result;
}


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   OUTPUT                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Converts the passed BigInt to a string
std::string std::to_string(BigInt n) {
	std::string str = "";
	std::string num = n.get_str();
	for (int i = 0; i < n.length(); ++i) {
		str = num[i] + str;
	}
	if (n.is_negative()) {
		str = "-" + str;
	}
	return str;
}

// Overloading the "<<" operator
std::ostream& operator<<(std::ostream& os, const BigInt& n) {
	os << std::to_string(n);
	return os;
}
