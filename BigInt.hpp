/*
	BigInt - Support for arbitrary sized integers
	Now all in one file!

	No copyright, idk how that works.

*/

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>	// "Chunk" storage
#include <iomanip>	// Used in output manipulation
#include <sstream>	// Used here and there for string manipulation
#include <climits>	// Used in constructors for underflow detection

typedef int CHUNK; // This will be the data type that holds a "chunk" of our number
typedef long long CHUNK_PROD; // Self explanatory, keeps the overflows out of the library that eliminates them

static const CHUNK BASE = 1000000000; // This is what we use to extract chunks
static const CHUNK MAX_VALUE = 999999999; // This is the upper bound of what we'll allow our chunks to be
static const int NUM_DIGIS = 9; // Length of CHUNKS, used in output and string constructors


/*
	Might write an exception class for things like division by 0 or string inputs, but right now I'm the only one using this
*/

/*
	Helper functions for our constructors using div_t(s)
*/
inline static div_t intDiv(int num, int den) {
	div_t res;
	res.quot = num / den;
	res.rem = num - den * res.quot;	// Reduce division operations
	return res;
}

inline static ldiv_t longDiv(long num, long den) {
	ldiv_t res;
	res.quot = num / den;
	res.rem = num - den * res.quot;	// Reduce division operations
	return res;
}

inline static lldiv_t llongDiv(long long num, long long den) {
	lldiv_t res;
	res.quot = num / den;
	res.rem = num - den * res.quot;	// Reduce division operations
	return res;
}

class BigInt {
	// Iostream overloads
	friend std::ostream& operator<<(std::ostream& os, const BigInt& o);
	friend std::istream& operator<<(std::istream& is, BigInt& o);
public:
	// Constructors
	BigInt();				// Default (0)

	BigInt(unsigned int n);	// Unsigned values
	BigInt(unsigned long n);
	BigInt(unsigned long long n);

	BigInt(int n);			// Signed values
	BigInt(long n);
	BigInt(long long n);

	BigInt(const char* c);	// Strings
	BigInt(const std::string& str);

	// Assignment Operands
	BigInt& operator=(const BigInt& o);	// Object

	BigInt& operator=(unsigned int n);	// Unsigned values
	BigInt& operator=(unsigned long n);
	BigInt& operator=(unsigned long long n);

	BigInt& operator=(int n);			// Signed values
	BigInt& operator=(long n);
	BigInt& operator=(long long n);

	BigInt& operator=(const char* c);
	BigInt& operator=(const std::string& str);

	// Relational Operands
	bool operator==(const BigInt& o) const;
	bool operator!=(const BigInt& o) const;
	bool operator>(const BigInt& o) const;
	bool operator<(const BigInt& o) const;
	bool operator>=(const BigInt& o) const;
	bool operator<=(const BigInt& o) const;

	// I understand the value of bitwise operands but i don't want to, go back to v4 for that

	// Arithmetic Operands
	BigInt operator+(const BigInt& o) const;
	BigInt operator-(const BigInt& o) const;
	BigInt operator*(const BigInt& o) const;
	BigInt operator*(CHUNK o);					// This will be used a ton, so an efficient method is made
	BigInt operator/(const BigInt& o) const;
	BigInt operator%(const BigInt& o) const;

	// Arithmetic-Assignment Operands
	const BigInt& operator+=(const BigInt& o);
	const BigInt& operator-=(const BigInt& o);
	const BigInt& operator*=(const BigInt& o);
	const BigInt& operator*=(CHUNK o);
	const BigInt& operator/=(const BigInt& o);
	const BigInt& operator%=(const BigInt& o);

	// Unary Operands
	BigInt operator-() const;	// -x
	BigInt operator++(int);		// x++
	BigInt operator--(int);
	const BigInt& operator++();	// ++x
	const BigInt& operator--();

	std::string toString() const;

private:
	std::vector<CHUNK> num; // Number storage vector
	bool neg;				// Negative boolean

	void fromString(const std::string& str);	// Used in string constructors
	void tweak(bool onlyTrim = false, bool validSign = false); // Used to correct results
	void trimZeros();	// Trims the leading zeros of a BigInt being tweaked
	void trunc();		// Truncates the CHUNKS to the base value (stops overflows)
	bool chunksFixed();	// Returns if the chunks are fixed, obv

	void multByChunk(CHUNK o, std::vector<CHUNK>& num);
	static CHUNK denInRem(const BigInt& rem, const BigInt& den);	// this time this isn't repeated subtraction!
};

#pragma region Constructors
inline BigInt::BigInt() {
	neg = false;
	num.push_back(0);
}

inline BigInt::BigInt(unsigned int n) {
	neg = false;
	do {
		num.push_back(n % BASE);
		n /= BASE;
	} while (n > 0);
}

inline BigInt::BigInt(unsigned long n) {
	neg = false;
	do {
		num.push_back(n % BASE);
		n /= BASE;
	} while (n > 0);
}

inline BigInt::BigInt(unsigned long long n) {
	neg = false;
	do {
		num.push_back(n % BASE);
		n /= BASE;
	} while (n > 0);
}

inline BigInt::BigInt(int n) {
	neg = (n < 0);

	if (neg) { n = -n; }

	do {
		div_t div = intDiv(n, BASE);
		num.push_back(div.rem);
		n = div.quot;
	} while (n > 0);
}

inline BigInt::BigInt(long n) {
	neg = (n < 0);

	if (neg) { n = -n; }

	do {
		ldiv_t div = longDiv(n, BASE);
		num.push_back(div.rem);
		n = div.quot;
	} while (n > 0);
}

inline BigInt::BigInt(long long n) {
	neg = (n < 0);

	if (neg) { n = -n; }

	do {
		lldiv_t div = llongDiv(n, BASE);
		num.push_back(div.rem);
		n = div.quot;
	} while (n > 0);
}

inline void BigInt::fromString(const std::string& str) {
	neg = (str[0] == '-');
	num.reserve(str.size() / NUM_DIGIS + 1);

	int index = str.size() - NUM_DIGIS;
	for (; index >= 0; index -= NUM_DIGIS) {	// Everything that fits easily
		num.push_back(std::stoi(str.substr(index, 9)));
	}

	if (index > -NUM_DIGIS) {	// Overhang
		num.push_back(std::stoi(str.substr((neg ? 1 : 0), (size_t)NUM_DIGIS + index - (neg ? 1 : 0))));
		// Ternary accounts for negative sign
	}

}

inline BigInt::BigInt(const char* c) {
	fromString(c);
}

inline BigInt::BigInt(const std::string& str) {
	fromString(str);
}
#pragma endregion

#pragma region Assignment Operators

inline BigInt& BigInt::operator=(const BigInt& o) {
	neg = o.neg;
	num = o.num;

	return *this;
}

inline BigInt& BigInt::operator=(unsigned int n) {
	num.clear();

	neg = false;
	do {
		num.push_back(n % BASE);
		n /= BASE;
	} while (n > 0);

	return *this;
}

inline BigInt& BigInt::operator=(unsigned long n) {
	num.clear();

	neg = false;
	do {
		num.push_back(n % BASE);
		n /= BASE;
	} while (n > 0);

	return *this;
}

inline BigInt& BigInt::operator=(unsigned long long n) {
	num.clear();

	neg = false;
	do {
		num.push_back(n % BASE);
		n /= BASE;
	} while (n > 0);

	return *this;
}

inline BigInt& BigInt::operator=(int n) {
	num.clear();

	neg = (n < 0);

	if (neg) { n = -n; }

	do {
		div_t div = intDiv(n, BASE);
		num.push_back(div.rem);
		n = div.quot;
	} while (n > 0);

	return *this;
}

inline BigInt& BigInt::operator=(long n) {
	num.clear();

	neg = (n < 0);

	if (neg) { n = -n; }

	do {
		ldiv_t div = longDiv(n, BASE);
		num.push_back(div.rem);
		n = div.quot;
	} while (n > 0);

	return *this;
}

inline BigInt& BigInt::operator=(long long n) {
	num.clear();

	neg = (n < 0);

	if (neg) { n = -n; }

	do {
		lldiv_t div = llongDiv(n, BASE);
		num.push_back(div.rem);
		n = div.quot;
	} while (n > 0);

	return *this;
}

inline BigInt& BigInt::operator=(const char* c) {
	num.clear();

	fromString(c);

	return *this;
}

inline BigInt& BigInt::operator=(const std::string& str) {
	num.clear();

	fromString(str);

	return *this;
}

#pragma endregion

#pragma region Relational Operands
inline bool BigInt::operator==(const BigInt& o) const {
	if (neg != o.neg) { return false; }

	if (num.size() != o.num.size()) { return false; }

	for (int i = num.size(); i > -1; --i) {
		if (num[i] != o.num[i]) { return false; }
	}

	return true;
}

inline bool BigInt::operator!=(const BigInt& o) const {
	if (neg != o.neg) { return true; }

	if (num.size() != o.num.size()) { return true; }

	for (int i = num.size(); i > -1; --i) {
		if (num[i] != o.num[i]) { return true; }
	}

	return false;
}

inline bool BigInt::operator>(const BigInt& o) const {
	if (neg && !o.neg) { return false; }
	if (!neg && o.neg) { return true; }

	if (num.size() > o.num.size()) { return neg ? false : true; }
	if (num.size() < o.num.size()) { return neg ? true : false; }

	for (int i = num.size(); i > -1; --i) {
		if (num[i] < o.num[i]) { return neg ? true : false; }
		if (num[i] > o.num[i]) { return neg ? false : true; }
	}

	return false;
}

inline bool BigInt::operator<(const BigInt& o) const {
	if (neg && !o.neg) { return true; }
	if (!neg && o.neg) { return false; }

	if (num.size() > o.num.size()) { return neg ? true : false; }
	if (num.size() < o.num.size()) { return neg ? false : true; }

	for (int i = num.size(); i > -1; --i) {
		if (num[i] < o.num[i]) { return neg ? false : true; }
		if (num[i] > o.num[i]) { return neg ? true : false; }
	}

	return false;
}

inline bool BigInt::operator>=(const BigInt& o) const {
	if (neg && !o.neg) { return false; }
	if (!neg && o.neg) { return true; }

	if (num.size() > o.num.size()) { return neg ? false : true; }
	if (num.size() < o.num.size()) { return neg ? true : false; }

	for (int i = num.size(); i > -1; --i) {
		if (num[i] < o.num[i]) { return neg ? true : false; }
		if (num[i] > o.num[i]) { return neg ? false : true; }
	}

	return true;
}

inline bool BigInt::operator<=(const BigInt& o) const {
	if (neg && !o.neg) { return true; }
	if (!neg && o.neg) { return false; }

	if (num.size() > o.num.size()) { return neg ? true : false; }
	if (num.size() < o.num.size()) { return neg ? false : true; }

	for (int i = num.size(); i > -1; --i) {
		if (num[i] < o.num[i]) { return neg ? false : true; }
		if (num[i] > o.num[i]) { return neg ? true : false; }
	}

	return true;
}

#pragma endregion

#pragma region Arithmetic Operands
inline BigInt BigInt::operator+(const BigInt& o) const {
	BigInt res;
	res.num.resize(num.size() > o.num.size() ? num.size() : o.num.size(), 0);	// Get ready for ternary hellscapes :D
	for (int i = 0; i < num.size() || i < o.num.size(); ++i) {
		res.num[i] = (i < num.size() ? (neg ? -num[i] : num[i]) : 0) + (i < o.num.size() ? (o.neg ? -o.num[i] : o.num[i]) : 0);
	}
	res.tweak();

	return res;
}

inline BigInt BigInt::operator-(const BigInt& o) const {
	BigInt res;
	res.num.resize(num.size() > o.num.size() ? num.size() : o.num.size(), 0);
	for (int i = 0; i < num.size() || i < o.num.size(); ++i) {
		res.num[i] = (i < num.size() ? (neg ? -num[i] : num[i]) : 0) - (i < o.num.size() ? (o.neg ? -o.num[i] : o.num[i]) : 0);
	}
	res.tweak();

	return res;
}

inline BigInt BigInt::operator*(const BigInt& o) const {
	BigInt res;
	res.num.resize(num.size() + o.num.size(), 0);
	CHUNK_PROD c = 0;
	int digi = 0;
	
	for (;; ++digi) {
		// Initial calculation
		lldiv_t div = llongDiv(c, BASE); // Should've name it something to do with chunk prod
		c = div.quot;
		res.num[digi] = div.rem;

		bool found = false;
		for (int i = digi < o.num.size() ? 0 : digi - o.num.size() + 1; i < num.size() && i <= digi; ++i) { // choosing starting point
			CHUNK_PROD prod = res.num[digi] + num[i] * (CHUNK_PROD)o.num[digi - i]; // Conversion because it overflowed

			if (prod > MAX_VALUE || prod < -MAX_VALUE) {	// Trunc to base func, but only right here
				div = llongDiv(prod, BASE);
				c += div.quot;	// Preserve cascading carry value
				prod = div.rem;
			}
			res.num[digi] = prod;
			found = true;
		}

		// Result found, do no more math
		if (!found) { break; }
	}
	// Hande possible remaining carry
	for (; c > 0; ++digi) {
		lldiv_t div = llongDiv(c, BASE);
		res.num[digi] = div.rem;
		c = div.quot;
	}
	res.tweak();

	// Handle sign
	res.neg = (res.num.size() == 1 && res.num[0] == 0) ? false : (neg != o.neg);

	return res;
}

inline BigInt BigInt::operator*(CHUNK o) {	// This one is much easier
	BigInt res = *this;
	CHUNK fact = o < 0 ? -o : o;	// make positive

	multByChunk(fact, res.num);
	
	res.tweak();
	res.neg = (res.num.size() == 1 && res.num[0] == 0) ? false : (neg = o < 0);

	return res;
}

inline BigInt BigInt::operator/(const BigInt& o) const {
	BigInt den = (o.neg ? -o : 0), num = (neg ? -*this : *this), quot, rem;	// brb unary operator time lol
	quot.num.resize(num.num.size(), 0); // I have made a severe lack of judgement when naming numerator

	for (int i = num.num.size() - 1; i > -1; --i) {
		rem.num.insert(rem.num.begin(), num.num[i]);
		rem.tweak(true);	// only trim
		CHUNK count = denInRem(rem, den);
		rem -= den * count;	// brb a-a operand time lol
		quot.num[i] += count;
	}

	quot.tweak();

	quot.neg = (quot.num.size() == 1 && quot.num[0] == 0) ? false : (neg != o.neg); // Yoinked from *()

	return quot;
}

inline BigInt BigInt::operator%(const BigInt& o) const {	// lol this is faster
	BigInt den = (o.neg ? -o : 0), num = (neg ? -*this : *this), rem;	// brb unary operator time lol

	for (int i = num.num.size() - 1; i > -1; --i) {
		rem.num.insert(rem.num.begin(), num.num[i]);
		rem.tweak(true);	// only trim
		CHUNK count = denInRem(rem, den);
		rem -= den * count;
	}

	rem.tweak();

	rem.neg = (rem.num.size() == 1 && rem.num[0] == 0) ? false : (neg != o.neg);

	return rem;
}

#pragma endregion

#pragma region Arithmetic-Assignment Operands
inline const BigInt& BigInt::operator+=(const BigInt& o) {
	if (o.num.size() > num.size()) { num.resize(o.num.size(), 0); }

	for (int i = 0; i < num.size(); ++i) {
		num[i] = (neg ? -num[i] : num[i]) + (o.neg ? -o.num[i] : o.num[i]);
	}
	tweak();

	return *this;
}

inline const BigInt& BigInt::operator-=(const BigInt& o) {
	if (o.num.size() > num.size()) { num.resize(o.num.size(), 0); }

	for (int i = 0; i < num.size(); ++i) {
		num[i] = (neg ? -num[i] : num[i]) - (o.neg ? -o.num[i] : o.num[i]);
	}
	tweak();

	return *this;
}

// The rest of these are pretty complicated so if these are really bad, ill fix them, but its like 3am rn and I need this running for an euler problem
inline const BigInt& BigInt::operator*=(const BigInt& o) {
	*this = *this * o;

	return *this;
}

inline const BigInt& BigInt::operator*=(CHUNK o) {	// This one is much easier
	*this = *this * o;
	
	return *this;
}

inline const BigInt& BigInt::operator/=(const BigInt& o) {
	*this = *this / o;

	return *this;
}

inline const BigInt& BigInt::operator%=(const BigInt& o) {	// lol this is faster
	*this = *this % o;

	return *this;
}

#pragma endregion

#pragma region Unary Operands
inline BigInt BigInt::operator-() const {
	BigInt res = *this;
	res.neg = !neg;
	return res;
}

inline BigInt BigInt::operator++(int) {
	BigInt res = *this;
	num[0] += (neg ? -1 : 1);
	tweak(false, true);
	return res;
}

inline BigInt BigInt::operator--(int) {
	BigInt res = *this;
	num[0] -= (neg ? -1 : 1);
	tweak(false, true);
	return res;
}

inline const BigInt& BigInt::operator++() {
	num[0] += (neg ? -1 : 1);
	tweak(false, true);
	return *this;
}

inline const BigInt& BigInt::operator--() {
	num[0] -= (neg ? -1 : 1);
	tweak(false, true);
	return *this;
}

#pragma endregion

inline std::string BigInt::toString() const {
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}

#pragma region Private Functions

inline void BigInt::tweak(bool onlyTrim, bool validSign) {
	if (!onlyTrim) {	// God forbid there is ever a bug in this if statement
		trunc();

		// Everything fits, now we need to make all CHUNKS positive
		if (chunksFixed()) {
			neg = validSign ? false : !neg;
			for (int i = 0; i < num.size(); ++i) {
				num[i] = abs(num[i]);	// I'm embarrassed that I had a bug here :(
			}
		}
		else {
			neg = ((num.size() == 1 && num[0] == 0) || !validSign) ? neg : true;
		}
	}

	trimZeros();
}

inline void BigInt::trimZeros() {
	for (int i = num.size() - 1; i > 0; --i) {	// Leave 1 zero if its zero, so many range errors D:
		if (num[i] != 0) { return; }
		else { num.erase(num.begin() + i); }
		// TODO check efficiency, trying something new instead of resizing
	}
}

inline void BigInt::trunc() {
	for (int i = 0; i < num.size(); ++i) {
		if (num[i] > MAX_VALUE || num[i] < -MAX_VALUE) {	// CHUNK has surpassed limits
			div_t div = intDiv(num[i], BASE);	// Correct
			num[i] = div.rem;
			if (i + 1 >= num.size()) { num.push_back(div.quot); }	// This has crashed so many times D:
			else { num[i + 1] += div.quot; }
		}
	}
}

// This function alone is the reason my hairline is visible from the back
inline bool BigInt::chunksFixed() {
	bool isNeg = false;	// Decides how much I'm going to hate this
	int i = num.size() - 1;
	for (; i > -1; --i) {
		if (num[i] != 0) {
			isNeg = num[i--] < 0;
			break;
		}
	}
	
	// i tried to ternary this control statement, its not worth the hair loss, but it'd be really funny
	// TODO go bald
	if (isNeg) {
		for (; i > -1; --i) {	// Pick up where we left off at the problem CHUNK
			if (num[i] > 0) {
				int index = i + 1, ii = 0;
				for (; index < num.size() && num[index] == 0; ++index, ++ii) {
					++num[index];
					num[i] -= BASE;		// Swippity swap
					for (; ii > 0; --ii) {
						num[i + ii] = -MAX_VALUE;
					}
				}
			}
		}
	}
	else {	// Dear god not again
		for (; i > -1; --i) {
			if (num[i] < 0) {
				int index = i + 1, ii = 0;
				for (; index < num.size() && num[index] == 0; ++index, ++ii) {
					--num[index];
					num[i] += BASE;		// Swippity swap, part 2, "the swappening"
					for (; ii > 0; --ii) {
						num[i + ii] = MAX_VALUE;
					}
				}
			}
		}
	}

	return isNeg;
}

inline void BigInt::multByChunk(CHUNK o, std::vector<CHUNK>& num) {
	CHUNK c = 0;

	for (int i = 0; i < num.size(); ++i) {
		CHUNK_PROD prod = num[i] * (CHUNK_PROD)o + c;	// Once again to stop overflows
		if (prod > MAX_VALUE || prod < -MAX_VALUE) {	// Trunc func
			lldiv_t div = llongDiv(prod, BASE);
			c = div.quot;
			prod = div.rem;
		}
		else { c = 0; }
		num[i] = prod;
	}
	// Handle carry
	if (c > 0) { num.push_back(c); }
	// Why can't all functions be like this :(
}

inline CHUNK BigInt::denInRem(const BigInt& rem, const BigInt& den) {
	CHUNK min = 0, max = MAX_VALUE;
	
	while (max > min) {
		CHUNK avg = max + min;
		div_t div = intDiv(avg, 2);
		avg = div.rem ? (div.quot + 1) : div.quot;	// I feel so fancy
		BigInt prod = den * avg;

		if (rem == prod) { return avg; }
		else if (rem > prod) { min = avg; }
		else { max = avg - 1; }
	}

	return min;
}

#pragma endregion


#pragma region Non-Member Functions
inline std::ostream& operator<<(std::ostream& os, const BigInt& o) {
	if (o.neg) { os << '-'; }

	bool firstCHUNK = true;
	for (int i = o.num.size() - 1; i > -1; --i) {
		if (firstCHUNK) {	// dont add extraneous 0's
			os << o.num[i];
			firstCHUNK = false;
		}
		else {
			os << std::setfill('0') << std::setw(NUM_DIGIS) << o.num[i];
		}
	}

	return os;
}

inline std::istream& operator<<(std::istream& is, BigInt& o) {
	std::string str;

	is >> str;
	o.fromString(str);

	return is;
}
#pragma endregion

#endif BIGINT_HPP