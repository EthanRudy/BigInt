#include "BigInt.h"

// Generate sthe binary representation of a number
void BigInt::generate_binary(int n) {
	for (int8_t i = 31; i > -1; --i) {
		short k = n >> i;
		if (k & 1) { bin.ptr[i] = 1; }
		else { bin.ptr[i] = 0; }
	}
}

// Trims all the non-relevant leading zeros
void BigInt::trim() {
	int trimAmount = 0;

	for (int s = this->len - 1; s > 3; s -= 4) {
		bool empty = 1;
		for (int i = 0; i < 4; ++i) {
			if (bin.ptr[s - i] == 1) { empty = 0; }
		}
		if (empty) { trimAmount += 4; }
		else { break; }
	}
	
	if (trimAmount > 0) {
		this->len -= trimAmount;

		bin.resize(-trimAmount);
		bin.size = this->len;
	}
}

// Trims all
DynArr<bool> BigInt::trim_a(DynArr<bool> bin) {
	int end = bin.size;
	for (int i = bin.size - 1; i > 0; --i) {
		if (bin.ptr[i]) {
			break;
		}
		--end;
	}
	if (end < 0) { end = 1; }
	return bin.range(0, end);
}

// Adds another 4 bits to binary array
void BigInt::extend_binary(DynArr<bool>& arr) {
	arr.resize(4, false);
	this->len += 4;
}

// Adds two binary Dynamic Arrays
DynArr<bool> BigInt::add(DynArr<bool> a, DynArr<bool> b, bool k) {
	if (a.size < b.size) { return add(b, a, k); }


	DynArr<bool> resbin = DynArr<bool>(false, a.size);

	int aInd = 0;
	int bInd = 0;

	bool carry = 0;
	while (bInd < b.size) {
		int8_t sum = a.ptr[aInd] + b.ptr[bInd] + carry;

		if (sum == 2) {
			carry = 1;
			sum = 0;
		}
		else if (sum == 3) {
			carry = 1;
			sum = 1;
		}
		else { carry = 0; }

		resbin.ptr[aInd] = sum;

		++aInd;
		++bInd;
	}

	while (aInd < a.size) {
		if (carry) {
			if (a.ptr[aInd]) {
				resbin.ptr[aInd] = 0;
			}
			else {
				resbin.ptr[aInd] = 1;
				carry = 0;
			}
		} else {
			resbin.ptr[aInd] = a.ptr[aInd];
		}

		++aInd;
	}

	if (carry) {
		if (k) {
			resbin.resize(1, false);
			this->len++;
		}
		else {
			extend_binary(resbin);
		}
		resbin.ptr[aInd] = 1;
	}

	return resbin;
}

// Subtracts two binary Dynamic Arrays
DynArr<bool> BigInt::sub(DynArr<bool> a, DynArr<bool> b) {
	DynArr<bool> resbin = DynArr<bool>(false, a.size);

	for (int i = a.size- 1; i > -1; --i) {
		if (i >= b.size) {
			resbin.ptr[i] = a.ptr[i];
		}
		else {
			if (a.ptr[i]) {
				if (b.ptr[i]) { resbin.ptr[i] = 0; }
				else { resbin.ptr[i] = 1; }
			}
			else {
				if (b.ptr[i]) {
					for (int j = i; j < a.size - 1; ++j) {
						resbin.ptr[j] = 1;
						if (resbin.ptr[j + 1]) {
							resbin.ptr[j + 1] = 0;
							break;
						}
					}
				}
				else { resbin.ptr[i] = 0; }
			}
		}
	}

	return resbin;
}

// Multiplication hub
DynArr<bool> BigInt::mult(DynArr<bool> a, DynArr<bool> b) {
	if (a.size < KARATSUBA_THRESHOLD || b.size < KARATSUBA_THRESHOLD) {
		return longMult(a, b);
	}

	DynArr<bool> res = karatsuba(a, b, 0);

	return res;
}

// Multiplies two binary Dynamic Arrays using Long Multiplication
DynArr<bool> BigInt::longMult(DynArr<bool> a, DynArr<bool> b) {
	// Creating res array of maximum result size
	DynArr<bool> res = DynArr<bool>(false, a.size + b.size);

	// Place counter for how many zeros are needed
	int place = 0;
	for (int i = 0; i < b.size; ++i) {
		if (b.ptr[i]) {
			// Row is the multiplicand shifted by the place value
			DynArr<bool> row = DynArr<bool>(false, a.size + place);
			int rowIndex = 0;

			// Fill the placeholder zeros
			while (rowIndex < place) {
				row.ptr[rowIndex] = 0;
				++rowIndex;
			}

			// Fill the rest of the digits from the multiplicand
			for (int j = 0; j < a.size; ++j) {
				row.ptr[rowIndex] = a.ptr[j];
				++rowIndex;
			}

			// Add row to the sum
			res = add(res, row, false);
		}
		// Increment number of zeros in the placeholder
		++place;
	}
	return trim_a(res);
}

// Multiplies two binary Dynamic Arrays using the Karatsuba method
DynArr<bool> BigInt::karatsuba(DynArr<bool> a, DynArr<bool> b, int amount) {
	std::string shift = "";
	for (int i = 0; i < amount; ++i) {
		shift += "\t";
	}


	if (a.size < b.size) {
		a.resize(b.size - a.size, false);
	}
	else if (b.size < a.size) {
		b.resize(a.size - b.size, false);
	}
	
	int n = a.size;

	// Base cases for now
	if (n == 0) { return DynArr<bool>(false, 1); }
	else if (n == 1) {

		return DynArr<bool>((a.ptr[0] == 0) ? false : (b.ptr[0] == 0 ? false : true), 1);
	}

	int half = n / 2;

	DynArr<bool> al = a.range(0, half);
	DynArr<bool> ah = a.range(half, n);
	
	DynArr<bool> bl = b.range(0, half);
	DynArr<bool> bh = b.range(half, n);
	
	DynArr<bool> p1 = mult(ah, bh);
	DynArr<bool> p2 = mult(al, bl);
	DynArr<bool> p3 = mult(add(ah, al, 1), add(bh, bl, 1));
	
	DynArr<bool> res = add(add(p1.shiftLeft(false, half), sub(sub(p3, p1), p2), 1).shiftLeft(false, half), p2, 1);
	
	return trim_a(res);
}


// Insert bit
void BigInt::insert(DynArr<bool> &arr, int p, bool v) {
	arr.resize(1, false);
	
	for (int i = arr.size - 1; i > p; --i) {
		arr.ptr[i] = arr.ptr[i - 1];
	}
	arr.ptr[p] = v;
}

// Integer Constructor
BigInt::BigInt(int n) {
	if (n > 0) { this->signum = 1; }
	else if (n == 0) { this->signum = 0; }
	else {
		this->signum = -1;
		n *= -1;
	}

	if (this->signum == 0) {
		this->len = 0;
		this->bin = DynArr<bool>(false, 0);
	}
	else {
		this->bin = DynArr<bool>(false, 32);
		this->len = 32;

		generate_binary(n);
		trim();
	}
}

// Byte array Constructor
BigInt::BigInt(bool* b, int l, int8_t s) {
	this->bin.ptr = b;
	this->bin.size = l;
	this->len = l;
	this->signum = s;
}

// Dynamic Array Constructor
BigInt::BigInt(DynArr<bool> b, int8_t s) {
	this->bin = b;
	this->len = b.size;
	this->signum = s;
}

// Copy Constructor
BigInt::BigInt(const BigInt& o) {
	this->bin = o.bin;
	this->len = o.len;
	this->signum = o.signum;
}

// Assignment Operator Overload
BigInt BigInt::operator=(const BigInt& o) {
	this->bin = o.bin;
	this-> len = o.len;
	this->signum = o.signum;

	return *this;
}

// Deconstructor
BigInt::~BigInt() {
	this->len = NULL;
	this->signum = NULL;
}

// Sign function
uint8_t BigInt::sign() {
	return this->signum;
}

// Size function
int BigInt::size() {
	return this->bin.size;
}

// To String
std::string BigInt::to_string() {
	if (signum == 0) { return "0"; }

	// Vector to store our BCD bits
	std::vector<bool> BCD;

	// Placing the 1's place's 4 bits
	for (int i = 0; i < 4; ++i) {
		BCD.push_back(0);
	}

	// Filling the relevant binary
	// Optimized for when all 31 bits aren't used
	for (int i = len - 1; i > -1; --i) {
		BCD.push_back(bin.ptr[i]);
	}

	// For shifts needed
	int c = len;
	// Number of places, aka. Number of 4 bit segments in our decimal representation
	int places = 1;
	// Vector that stores the starting positions of all used places
	std::vector<int> starts = { 0 };

	// Loop for all shifts
	while (c > -1) {

		// Adding another place if needed before a shift
		if (BCD[0] == 1) {
			for (int i = 0; i < starts.size(); ++i) {
				starts[i] += 4;
			}
			starts.push_back(0);

			for (int i = 0; i < 4; ++i) {
				BCD.insert(BCD.begin(), 0);
			}
		}

		// Shifting in preparation for DD
		BCD.erase(BCD.begin());
		BCD.push_back(0);

		// Decrementing shift count
		--c;

		// No shift edge case
		if (c < 1) { break; }

		// Checking all bcd places
		for (int s : starts) {
			// Convert places to decimal
			// Will change later but this is a simple
			// prototype
			// Getting decimal value of a 4 bit place
			short dTemp = 8;
			short dVal = 0;
			for (int i = s; i < s + 4; ++i) {
				if (BCD[i] == 1) {
					dVal += dTemp;
				}
				dTemp /= 2;
			}

			// Checking if a "dabble" is needed
			if (dVal > 4) {
				// Adding 3
				dVal += 3;
				// Overrite the old number and revert to binary
				for (int i = s + 3; i >= s; --i) {
					BCD[i] = dVal % 2;
					dVal /= 2;
				}
			}
		}

	}


	// Converting the BCD to decimal
	std::string res = "";
	for (int s : starts) {
		short dTemp = 8;
		short dVal = 0;
		for (int i = s; i < s + 4; ++i) {
			if (BCD[i] == 1) {
				dVal += dTemp;
			}
			dTemp /= 2;
		}
		res = std::to_string(dVal) + res;
	}

	// Displaying negative where applicable
	if (signum < 0) { res = "-" + res; }

	// Return the string representation
	return res;
}

// To String
std::string BigInt::to_string_p() {
	if (signum == 0) { return "0"; }

	// Vector to store our BCD bits
	std::vector<bool> BCD;

	// Placing the 1's place's 4 bits
	for (int i = 0; i < 4; ++i) {
		BCD.push_back(0);
	}

	// Filling the relevant binary
	// Optimized for when all 31 bits aren't used
	for (int i = len - 1; i > -1; --i) {
		BCD.push_back(bin.ptr[i]);
	}

	// For shifts needed
	int c = len;
	// Number of places, aka. Number of 4 bit segments in our decimal representation
	int places = 1;
	// Vector that stores the starting positions of all used places
	std::vector<int> starts = { 0 };


	float progress = 0.0;
	// Loop for all shifts
	while (c > -1) {

		// Adding another place if needed before a shift
		if (BCD[0] == 1) {
			for (int i = 0; i < starts.size(); ++i) {
				starts[i] += 4;
			}
			starts.push_back(0);

			for (int i = 0; i < 4; ++i) {
				BCD.insert(BCD.begin(), 0);
			}
		}

		// Shifting in preparation for DD
		BCD.erase(BCD.begin());
		BCD.push_back(0);

		// Decrementing shift count
		--c;

		// No shift edge case
		if (c < 1) { break; }

		// Checking all bcd places
		for (int s : starts) {
			// Convert places to decimal
			// Will change later but this is a simple
			// prototype
			// Getting decimal value of a 4 bit place
			short dTemp = 8;
			short dVal = 0;
			for (int i = s; i < s + 4; ++i) {
				if (BCD[i] == 1) {
					dVal += dTemp;
				}
				dTemp /= 2;
			}

			// Checking if a "dabble" is needed
			if (dVal > 4) {
				// Adding 3
				dVal += 3;
				// Overrite the old number and revert to binary
				for (int i = s + 3; i >= s; --i) {
					BCD[i] = dVal % 2;
					dVal /= 2;
				}
			}
		}

		progress = (float)(len - c) / len;
		std::cout.precision(5);
		std::cout << "BCD converstion: " << (progress * 100) << "% \r";
		std::cout.flush();

	}


	// Converting the BCD to decimal
	std::string res = "";
	for (int s : starts) {
		short dTemp = 8;
		short dVal = 0;
		for (int i = s; i < s + 4; ++i) {
			if (BCD[i] == 1) {
				dVal += dTemp;
			}
			dTemp /= 2;
		}
		res = std::to_string(dVal) + res;
	}

	// Displaying negative where applicable
	if (signum < 0) { res = "-" + res; }

	// Return the string representation
	return res;
}

// To String overload
std::string std::to_string(BigInt n) {
	return n.to_string();
}

// To String with Percentage
std::string std::to_string_p(BigInt n) {
	std::cout << "\n";
	return n.to_string_p();
}

std::ostream& operator<<(std::ostream& os, const BigInt& n) {
	os << std::to_string(n);
	return os;
}
