#include "BigInt.h"

// Compare operator overload
bool BigInt::operator==(const BigInt& o) {
	if (this->len != o.len) { return false; }
	for (int i = 0; i < this->len; ++i) {
		if (this->bin.ptr[i] != o.bin.ptr[i]) { return false; }
	}
	return true;
}

// Inverse Compare operator overload
bool BigInt::operator!=(const BigInt& o) {
	return !operator== (o);
}

// Less-Than operator overload
bool BigInt::operator<(const BigInt& o) {
	if (this->len < o.len) { return true; }
	else if (this->len > o.len) { return false; }
	else {
		for (int i = this->len - 1; i > -1; --i) {
			if (this->bin.ptr[i] != o.bin.ptr[i]){
				if (this->bin.ptr[i] == 1) { return false; }
				return true;
			}
		}
	}
	return false;
}

// Greater-Than operator overload
bool BigInt::operator>(const BigInt& o) {
	if (this->len < o.len) { return false; }
	else if (this->len > o.len) { return true; }
	else {
		for (int i = this->len - 1; i > -1; --i) {
			if (this->bin.ptr[i] != o.bin.ptr[i]) {
				if (this->bin.ptr[i] == 1) { return true; }
				return false;
			}
		}
	}
	return false;
}

// Less-Than or Equal-To overload
bool BigInt::operator<=(const BigInt& o) {
	if (this->len < o.len) { return true; }
	else if (this->len > o.len) { return false; }
	else {
		for (int i = this->len - 1; i > -1; --i) {
			if (this->bin.ptr[i] != o.bin.ptr[i]) {
				if (this->bin.ptr[i] == 1) { return false; }
				return true;
			}
		}
	}
	return true;
}

// Greater-Than or Equal-To overload
bool BigInt::operator>=(const BigInt& o) {
	if (this->len < o.len) { return false; }
	else if (this->len > o.len) { return true; }
	else {
		for (int i = this->len - 1; i > -1; --i) {
			if (this->bin.ptr[i] != o.bin.ptr[i]) {
				if (this->bin.ptr[i] == 1) { return true; }
				return false;
			}
		}
	}
	return true;
}

// Fits Inside
bool BigInt::fits(DynArr<bool> a, DynArr<bool> b) {
	if (a.size > b.size) { return true; }
	else if (a.size < b.size) { return false; }
	else {
		for (int i = a.size - 1; i > -1; --i) {
			if (!a.ptr[i]) {
				if (b.ptr[i]) { return false; }
			}
			else {
				if (!b.ptr[i]) { return true; }
			}
		}
	}
	return true;
}
