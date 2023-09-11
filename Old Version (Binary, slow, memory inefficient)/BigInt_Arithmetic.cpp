#include "BigInt.h"

// Addition
BigInt BigInt::add(BigInt o) {
	if (this->signum == 0) { return o; }
	else if (o.signum == 0) { return *this; }

	if (o.bin.size > this->bin.size) {
		return o.add(*this);
	}

	// Check signs
	if (this->signum == o.signum) {	// Same sign addition
		return BigInt(add(this->bin, o.bin, false), this->signum);
	}
	else { // Subtraction
		return sub(BigInt(o.bin, this->signum));
	}
}

// Subtraction
BigInt BigInt::sub(BigInt o) {
	// Catching the zero edgecases
	if (this->signum == 0) { return BigInt(o.bin, o.signum * -1); }
	if (o.signum == 0) { return *this; }

	/**
	* There has to be a better way to do this
	*/

	// Checking places have to be swapped
	if (o > *this) {
		if (this->signum == o.signum) {
			// Sign also has to be swapped
			return BigInt(sub(o.bin, this->bin), this->signum * -1);
		}
		else {
			// Sign is already swapped
			return BigInt(add(this->bin, o.bin, false), this->signum);
		}
	}
	else {
		if (this->signum == o.signum) {	// Same sign subtraction
			return BigInt(sub(this->bin, o.bin), this->signum);
		}
		else { // Addition
			return BigInt(add(this->bin, o.bin, false), this->signum);
		}
	}
}

// Multiplication
BigInt BigInt::mult(BigInt o) {
	// Catching the zero edgecase
	if ((this->signum == 0) || (o.signum == 0)) { return BigInt(0); }
	// Result sign
	uint8_t ressig = (this->signum == o.signum) ? 1 : -1;

	DynArr<bool> resbin = mult(this->bin, o.bin);

	BigInt t = BigInt(resbin, ressig);
	t.trim();

	return t;
}

BigInt BigInt::div(BigInt o) {
	// Catching zero edgecases
	if (this->signum == 0) { return BigInt(0); }
	else if (o.signum == 0) { throw CustExcep("Cannot divide by 0 doofus!"); }

	// Quick ans < 0 check
	if (o > *this) { return BigInt(0); }

	// Basically do long division
	// But since we are handling integers, FUCK REMAINDER
	// Also do it in reverse bc im dumb af

	// Copying and formatting binary arrays
	DynArr<bool> dividend = trim_a(this->bin);
	DynArr<bool> divisor = trim_a(o.bin);

	// Creating the result holder
	// Dividends size may not be a multiple of 4
	// Garbage fix
	int reslen = this->len;
	DynArr<bool> resbin = DynArr<bool>(false, reslen);
	uint8_t ressig = (this->signum == o.signum) ? 1 : -1;
	int resInd = reslen - 1; // -1 to get the last index (range is inclusive)
	resInd -= (this->bin.size - dividend.size);

	// Slice holder
	DynArr<bool> diviSlice;
	diviSlice = dividend.range(dividend.size - 1, dividend.size);
	int diviInd = dividend.size - 1;

	while (diviInd > -1) {

		--diviInd;	// Subtract again to get a length of 1 for inclusivity

		if (fits(diviSlice, divisor)) {
			resbin.ptr[resInd] = 1;
			// Subtract the parts
			diviSlice = sub(diviSlice, divisor);
		}
		else {
			resbin.ptr[resInd] = 0;
		}
		--resInd;

		if (diviInd > -1) {
			;
			// Drop digit
			insert(diviSlice, 0, dividend.ptr[diviInd]);
			diviSlice = trim_a(diviSlice);
		}
	}

	return BigInt(resbin, ressig);
}

// Power
BigInt BigInt::pow(int n) {
	if (this->signum == 0) { return *this; }

	DynArr<bool> res = this->bin;

	for (int i = 1; i < n; ++i) {
		// Uses the mult hub for karatsuba cases
		res = mult(res, this->bin);
	}

	int8_t ressig = (this->signum == 1) ? 1 : (n % 2 == 0) ? 1 : -1;

	return BigInt(res, ressig);
}
