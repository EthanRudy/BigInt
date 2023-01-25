// Initialization file for the BigInt class
// @file BigInt.cpp
// @author Ethan Rudy
// @version 1.0

#include "BigInt.h"

// Generates the binary representation of a number
void BigInt::generate_binary(int n) {
	// Simple decimal to binary function
	short t;
	for (short i = 31; i > -1; --i) {
		short k = n >> i;
		if (k & 1) {
			bin[i] = 1;
			if (lsegs == 0) {
				lsegs = i + (i % 4);
			}
		}
		else { bin[i] = 0; }
	}
}

// Generates the 2's complement representation from binary
void BigInt::generate_2scomp() {
	// https://en.wikipedia.org/wiki/Two%27s_complement

	// 1: Flip all bits
	for (short i = 0; i < 32; ++i) {
		bin[i] = !bin[i];
	}

	// 2: Add 1
	for (short i = 0; i, 31; ++i) {
		if (!bin[i]) {
			bin[i] = 1;
			break;
		}
		bin[i] = 0;
		if (!bin[i + 1]) {
			bin[i + 1] = 1;
			break;
		}
	}
}

// Integer constructor
BigInt::BigInt(int n) {
	// Modifying the negative flag
	if (n < 0) {
		neg = true;
		n *= -1;
	}

	// Generate the binary representation
	generate_binary(n);
}


// To string
std::string BigInt::to_string() {
	// Vector to store our BCD bits
	std::vector<bool> BCD;

	// Placing the 1's place's 4 bits
	for (short i = 0; i < 4; ++i) {
		BCD.push_back(0);
	}

	// Filling the relevant binary
	// Optimized for when all 31 bits aren't used
	if (lsegs == 32) { --lsegs; }
	for (short i = lsegs; i > -1; --i) {
		BCD.push_back(bin[i]);
	}

	// For shifts needed
	short c = lsegs;
	// Number of places, aka. Number of 4 bit segments in our decimal representation
	short places = 1;
	// Vector that stores the starting positions of all used places
	std::vector<short> starts = { 0 };

	// Loop for all shifts
	while (c > -1) {
		// Adding another place if needed before a shift
		if (BCD[0] == 1) {
			for (short i = 0; i < starts.size(); ++i) {
				starts[i] += 4;
			}
			starts.push_back(0);

			for (short i = 0; i < 4; ++i) {
				BCD.insert(BCD.begin(), 0);
			}
		}

		// Shifting in preparation for DD
		BCD.erase(BCD.begin());
		BCD.push_back(0);

		// Decrementing shift count
		--c;

		// No shift edge case
		if (c < 0) { break; }

		// Checking all bcd places
		for (short s : starts) {
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
	for (short s : starts) {
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
	if (neg) { res = "-" + res; }

	// Return the string representation
	return res;
}
