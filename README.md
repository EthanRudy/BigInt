# big::Integer Documentation
## Type Definitions
#### BLOCK (int)
	typedef int BLOCK;
The [BLOCK](#BLOCK%20(int)) data type is the base structure of every [big::Integer](#Default%20Constructor). A [BLOCK](#BLOCK%20(int)) is an enumeration of the integer type, as we want it to have a range of around 9 digits. We choose 9 digits (1 billion), to reduce iterations in computations whilst also staying safe from overflows
#### BLOCK_PRODUCT
	typedef long long BLOCK_PRODUCT;
The [BLOCK_PRODUCT](#BLOCK_PRODUCT) is an intermediate type primarily used in multiplication. Since we have to multiply [BLOCKs](#BLOCK%20(int)), we need a data type large enough to hold up to ~18 digits without over/underflow. Long Long provides this functionality.
## Constants
#### MIN
	const BLOCK MIN = 0;
Holds the minimum value of a [BLOCK](#BLOCK%20(int)) at any given time. If a [BLOCK](#BLOCK%20(int)) is less than MIN, we must borrow until all BLOCKS are positive, [BLOCKs](#BLOCK%20(int)) includes changing the entire sign and size of the  [big::Integer](#Default%20Constructor)
#### MAX
	const BLOCK MAX = 999999999;
Holds the maximum value of a [BLOCK](#BLOCK%20(int)) at any given time. If a [BLOCK](#BLOCK%20(int)) is greater than MAX, we must carry until all [BLOCKs](#BLOCK%20(int)) are <= 999,999,999, this includes appending more [BLOCKs](#BLOCK%20(int)) to the [big::Integer](#Default%20Constructor)
#### BASE
	const BLOCK BASE = 1000000000;
Stores the base used when constructing & truncating [BLOCKs](#BLOCK%20(int)). One can think of [big::Integer](#Default%20Constructor) using a base-1000000000 number system, where each digit is still base-10. Sounds insane, trust me it's not.
#### DIGITS
	const int DIGITS = 9;
Stores the amount of digits each block takes up. Used in output manipulation, aka. filling zeros in the middle of [BLOCKs](#BLOCK%20(int)).
## Member Variables
#### num
	std::vector<BLOCK> num;
The primary storage of the [big::Integer](#Default%20Constructor). Big-endian order,
#### sign
	bool sign;
Denotes what sign the [big::Integer](#Default%20Constructor) is. Mimics the sign bit behavior used in binary numbers.
```
sign == 0 : num >= 0
sign == 1 : num < 0
```

## Public Member Functions

### Constructors
#### Default Constructor
Initializes the [big::Integer](#Default%20Constructor) to a default value of 0
##### Source:
```c++
Integer::Integer() {
	num = { 0 };	// Set default value to 0
	sign = false;
}
```
##### Example:
```cpp
int main() {
	big::Integer num;
}
```
#### Signed Integer Constructor(s)
Initializes the [big::Integer](#Default%20Constructor) to a passed value of type { *int*, *long*, *long long* }
##### Source:
```cpp
Integer::Integer({int, long, long long} n) {
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
```
##### Example:
```cpp
int main() {
	int n = -10;
	big::Integer num(n);
}
```
#### Unsigned Integer Constructor(s)
Initializes the [big::Integer](#Default%20Constructor) to a passed value of type *unsigned* { *int*, *long*, *long long* }. The only difference from the signed constructor is the removal of the sign logic, as all unsigned values are > -1.
##### Source:
```cpp
Integer::Integer(unsigned {int, long, long long} n) {
	sign = 0;
		do {
			num.push_back(n % BASE);
			n /= BASE;
		} while (n > 0);
}
```
##### Example:
```cpp
int main() {
	unsigned n = 10;
	big::Integer num(n);
}
```
#### Character Constructor(s)
Initializes the [big::Integer](#Default%20Constructor) to the decimal representation of the passed *char* array or *std::string* object using the [construct_from_string()](#Construct%20from%20String) private method.
##### Source:
```cpp
Integer::Integer(const char* str) {
	construct_from_string(str);
}

or

Integer::Integer(const std::string& str) {
	construct_from_string(str);
}
```
##### Example:
```cpp
int main() {
	char* n1 = "1234";
	std::string n2 = "-4321";

	big::Integer num1(n1);
	big::Integer num2(n2);
}
```
#### Copy Constructor
Initializes the [big::Integer](#Default%20Constructor) to the[big::Integer](#Default%20Constructor) *o*. 
NOTE: This is **NOT** an assignment
##### Source:
```cpp
Integer::Integer(const Integer& o) {
	num.clear();

	sign = o.sign;
	for (BLOCK i : o.num) {
		num.push_back(i);
	}
}
```
##### Example:
```cpp
int main() {
	big::Integer A(10);
	big::Integer B(A);
}
```

#### Deconstructor
Deconstructs and frees up memory reserved by the [big::Integer](#Default%20Constructor)
##### Source:
```cpp
Integer::~Integer() {
	num.clear();
}
```
##### Example:
```cpp
int main() {
	// Either done automatically when the object's scope ends

	// Or by calling directly:
	big::Integer a("12345678987654321");
	a.~Integer();
}
```
### Assignment Operands
Assignment Operands follow the patter of constructors. The main difference is the presence of the `num.clear();`, to clear any previous value before appending more [BLOCKs](#BLOCK%20(int)).
#### big::Integer Assignment
Assigns the value of a [big::Integer](#Default%20Constructor) to the value of the passed [big::Integer](#Default%20Constructor) *o*
##### Source:
```cpp
Integer& Integer::operator=(const Integer& o) {
	num.clear();

	sign = o.sign;
	for (BLOCK i : o.num) {
		num.push_back(i);
	}

	return *this;
}
```
##### Example:
```cpp
int main() {
	big::Integer a(10);
	big::Integer b = a;
}
```

#### Signed Integer Assignment(s)
Assigns the value of a [big::Integer](#Default%20Constructor) to the value of the passed { *int*, *long*, *long long* }
##### Source:
```cpp
Integer& Integer::operator=({int, long, long long} n) {
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
```
##### Example:
```cpp
int main() {
	big::Integer num = -10;
}
```

#### Unsigned Integer Assignment(s)
Assigns the value of a [big::Integer](#Default%20Constructor) to the value of the passed *unsigned* { *int*, *long*, *long long* }
##### Source:
```cpp
Integer& Integer::operator=(unsigned {int, long, long long} n) {
	num.clear();

	sign = 0;

	while (n > 0) {
		num.push_back(n % BASE);
		n /= BASE;
	}

	return *this;
}
```
##### Example:
```cpp
int main() {
	big::Integer num = 1234;
}
```

#### Character Assignment(s)
Assigns the value of a [big::Integer](#Default%20Constructor) to the decimal representation of the passed *char* or *std::string*
##### Source:
```cpp
Integer& Integer::operator=(const char* c) {
	num.clear();

	construct_from_string(c);

	return *this;
}

or

Integer& Integer::operator=(const std::string& c) {
	num.clear();

	construct_from_string(c);

	return *this;
}
```
##### Example:
```cpp
int main() {
	big::Integer num = "1234";
}
```

### Comparator Operands
#### Equivalence
Returns the equivalence T/F of the two specified [big::Integers](#Default%20Constructor)
##### Source:
```cpp
bool Integer::operator==(const Integer& o) const {
	if (sign != o.sign) { return false; }
	if (num.size() != o.num.size()) { return false; }

	for (int i = 0; i < num.size(); ++i) {
		if (num[i] != o.num[i]) { return false; }
	}

	return true;
}
```
##### Example:
```cpp
int main() {
	big::Integer A(1);
	big::Integer B("1");

	std::cout << (A == B) << "\n"; // True
}
```
#### Non-Equivalence
Returns the inverse equivalence T/F of the two specified [big::Integers](#Default%20Constructor)
##### Source:
```cpp
bool Integer::operator!=(const Integer& o) const {
	if (sign != o.sign) { return true; }
	if (num.size() != o.num.size()) { return true; }

	for (int i = 0; i < num.size(); ++i) {
		if (num[i] != o.num[i]) { return true; }
	}

	return false;
}
```
##### Example:
```cpp
int main() {
	big::Integer A("1234");
	big::Integer B(1234);

	std::cout << (A != B) << "\n"; // False
}
``````

#### Less Than
Returns T/F whether the left [big::Integer](#Default%20Constructor) is less than the right
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A("1");
	big::Integer B(2);

	std::cout << (A < B) << "\n"; // True
}
``````

#### Greater Than
Returns T/F whether the left [big::Integer](#Default%20Constructor) is greater than the right
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A("1");
	big::Integer B(2);

	std::cout << (A > B) << "\n"; // False
}
```

#### Less Than or Equal to
Returns T/F whether the left [big::Integer](#Default%20Constructor) is less than or equal to the right
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A("2");
	big::Integer B(2);

	std::cout << (A <= B) << "\n"; // True
}
```

#### Greater Than or Equal To
Returns T/F whether the left [big::Integer](#Default%20Constructor) is greater than or equal to the right
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A("2");
	big::Integer B(2);

	std::cout << (A >= B) << "\n"; // True
}
```

### Arithmetic Operands
#### Addition
Returns the sum of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(123456789);
	big::Integer B(987654321);

	big::Integer C = A + B;
}
```

#### Subtraction
Returns the difference of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(123456789);
	big::Integer B(987654321);

	big::Integer C = A - B;
}
```

#### Multiplication (big::Integer)
Returns the product of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(123456789);
	big::Integer B(987654321);

	big::Integer C = A * B;
}
```

#### Multiplication (BLOCK)
Returns the sum of the specified [big::Integer](#Default%20Constructor) (left) and [BLOCK](#BLOCK%20(int)) right.
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(123456789);
	BLOCK B = 100;

	big::Integer C = A ** B;
}
```

#### Division
Returns the quotient of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A("12345678987654321");
	big::Integer B(12345);

	big::Integer C = A / B;
}
```

#### Modulo
Returns the remainder of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A("12345678987654321");
	big::Integer B(12345);

	big::Integer C = A % B;
}
```

### Arithmetic & Assignment Operands
#### Addition
Assigns (left) and returns the sum of of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(1);
	big::Integer B(99);

	A += B;
}
```

#### Subtraction
Assigns (left) and returns the difference of of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(1);
	big::Integer B(99);

	A -= B;
}
```

#### Multiplication (big::Integer)
Assigns (left) and returns the product of of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
const Integer& Integer::operator*=(const Integer& o) {
	// Cant think of an encompassing method of in place multiplication

	*this = *this * o;

	return *this;
}
```
##### Example:
```cpp
int main() {
	big::Integer A(99);
	big::Integer B(99);

	A *= B;
}
```

#### Multiplication (BLOCK)
Assigns (left) and returns the sum of of the specified [big::Integer](#Default%20Constructor) (left) and [BLOCK](#BLOCK%20(int)) (right).
##### Source:
```cpp
const Integer& Integer::operator*=(BLOCK n) {
	// Cant think of an encompassing method of in place BLOCK multiplication

	*this = *this * n;

	return *this;

}
```
##### Example:
```cpp
int main() {
	big::Integer A(1);
	BLOCK B = 12345678;

	A *= B;
}
```

#### Division
Assigns (left) and returns the quotient of of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
const Integer& Integer::operator/=(const Integer& o) {
	// Cant think of an encompassing method of in place division

	*this = *this / o;

	return *this;

}
```
##### Example:
```cpp
int main() {
	big::Integer A("12345678987654321);
	big::Integer B(2);

	A /= B;
}
```

#### Modulo
Assigns (left) and returns the remainder of of the two specified [big::Integers](#Default%20Constructor).
##### Source:
```cpp
const Integer& Integer::operator%=(const Integer& o) {
	// Cant think of an encompassing method of in place modulo

	*this = *this % o;

	return *this;

}
```
##### Example:
```cpp
int main() {
	big::Integer A("12345678987654321);
	big::Integer B(2);

	A %= B;
}
```

### Unary Overloads
#### Inverse Sign (Negative)
Returns the numerical opposite of the specified [big::Integer](#Default%20Constructor).
##### Source:
```cpp
Integer Integer::operator-() const {
	Integer result = *this;
	result.sign = !sign;

	return result;
}
```
##### Example:
```cpp
int main() {
	big::Integer A(10);

	// Utilizes the ostream operator
	std::cout << -A << "\n";
}
```

#### Pre-Increment
Increments, then returns the value of the specified [big::Integer](#Default%20Constructor). Equivalent to`var++;`
##### Source:
```cpp
Integer Integer::operator++(int) {
	Integer result = *this;
	result.num[0] += (sign ? -1 : 1);

	result.tweak_blocks();

	return result;
}
```
##### Example:
```cpp
int main() {
	big::Integer A(1);
	A++; // A == 2
}
```

#### Pre-Decrement
Decrements, then returns the value of the specified [big::Integer](#Default%20Constructor). Equivalent to`var--;`
##### Source:
```cpp
Integer Integer::operator--(int) {
	Integer result = *this;
	result.num[0] -= (sign ? -1 : 1);

	result.tweak_blocks();

	return result;
}
```
##### Example:
```cpp
int main() {
	big::Integer A(1);
	A--; // A == 0
}
```

#### Post-Increment
Increments, using an intermediate to not destroy the original state of the specified [big::Integer](#Default%20Constructor) until the function is complete. Equivalent to `++var;`
##### Source:
```cpp
const Integer& Integer::operator++() {
	num[0] += (sign ? -1 : 1);
	tweak_blocks();

	return *this;
}
```
##### Example:
```cpp
int main() {
	int arr = { 1, 2, 3 };
	big::Integer A = 1;

	std::cout << arr[A++] << "\n"; // "3", A == 2;

	// Reset A
	A = 1;
	
	std::cout << arr[++A] << "\n"; // "2", then A == 2;
}
```

#### Post-Decrement
Decrements, using an intermediate to not destroy the original state of the specified [big::Integer](#Default%20Constructor) until the function is complete. Equivalent to `--var;`
##### Source:
```cpp
const Integer& Integer::operator--() {
	num[0] -= (sign ? -1 : 1);
	tweak_blocks();

	return *this;
}
```
##### Example:
```cpp
int main() {
	int arr = { 1, 2, 3 };
	big::Integer A = 1;

	std::cout << arr[A--] << "\n"; // "1", A == 0;

	// Reset A
	A = 1;
	
	std::cout << arr[--A] << "\n"; // "2", then A == 0;
}
```

### Bitwise Operands
Note: AND, OR, and XOR are **VERY** due to the [big::Integers](#Default%20Constructor) having to be converted to binary every operation. Both of the shifting functions use multiplication and division by two to calculate the result.
#### AND
Returns the result of a bitwise AND `&` operation of the two specified [big::Integers](#Default%20Constructor)
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(5);
	big::Integer B(3);

	std::cout << (A & B) << "\n"; // A(5): 101, B(3): 011, C(1): 001
	// 1
}
```

#### OR
Returns the result of a bitwise OR `|` operation of the two specified [big::Integers](#Default%20Constructor)
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(5);
	big::Integer B(3);

	std::cout << (A | B) << "\n"; // A(5): 101, B(3): 011, C(7): 111
	// 7
}
```

#### XOR
Returns the result of a bitwise XOR `^` operation of the two specified [big::Integers](#Default%20Constructor)
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer A(5);
	big::Integer B(3);

	std::cout << (A ^ B) << "\n"; // A(5): 101, B(3): 011, C(6): 110
	// 6
}
```

#### Shift Left
Returns the result of a logical left shift `<<` operation of the specified [big::Integer](#Default%20Constructor) (left) by the specified *int* (right)
##### Source:
```cpp
Integer Integer::operator<<(int n) {
	Integer result = *this;

	while (n > 0) {
		result /= 2;
		--n;
	}

	return result;
}
```
##### Example:
```cpp
int main() {
	big::Integer num(5); // 101

	std::cout << (num << 3) << "\n"; // 101000 OR 5 * 2^(3)
	// 40
}
```

#### Shift Right
Returns the result of a logical right shift `>>` operation of the specified [big::Integer](#Default%20Constructor) (left) by the specified *int* (right)
##### Source:
```cpp
Integer Integer::operator>>(int n) {
	Integer result = *this;

	while (n > 0) {
		result *= 2;
		--n;
	}

	return result;
}
```
##### Example:
```cpp
int main() {
	big::Integer num(5); // 101

	std::cout << (num >> 1) << "\n"; // 10 OR 5 / 2^(1)
	// 2
}
```

### Miscellaneous
#### Get Length
Returns the length of the [num](#num) std::vector. This is the number of [BLOCKs](#BLOCK%20(int)) a big::Integer contains.
##### Source:
```cpp
unsigned int Integer::getLength() {
	return num.size();
}
```
##### Example:
```cpp
int main() {
	// Just large enough to make two BLOCKs
	big::Integer num("1000000000");

	std::cout << num.getlength() << "\n";
	// 2
}
```

#### Get Digit Length
Returns the number of digits in the [big::Integer](#Default%20Constructor). This is the length of the string representation (minus the sign char).
##### Source:
```cpp
unsigned int Integer::getDigitLength() {
	// CHANGE TO USE THE TO_STRING() FUNCTION

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
```
##### Example:
```cpp
int main() {
	big::Integer num(100);

	std::cout << num.getDigitLength() << "\n";
	// 3
}
```

#### Get Chunk
Returns the value of [num](#num) at a specified index *n*.
##### Source:
```cpp
unsigned int Integer::getChunk(unsigned int n) {
	return num[n];
}
```
##### Example:
```cpp
int main() {
	big::Integer num("1000000000");

	std::cout << num.getChunk(0) << "\n"; // 1
	std::cout << num.getChunk(1) << "\n"; // 0
}
```

## Private Member Functions
###  Strings
#### Construct From String
Constructs a fresh [big::Integer](#Default%20Constructor) object using the provided characters. It functions as follows: determine sign, remove leading zeros, finally append [BLOCKs](#BLOCK%20(int)).
##### Source:
```cpp
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
```

### Arithmetic Helpers
#### Tweak Blocks
This function is a doozy. It manages most of the logic outside of arithmetic. It borrows and carries, fixes and sign errors, calls [trim_leading()](#Trim%20Leading%20Zeros) to remove any remaining zeros.
##### Source:
```cpp
int main() {
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
}
```

#### Trim Leading Zeros
Trims any excess zero's from the most significant end (Big-Endian aka. Left) of the [big::Integer](#Default%20Constructor).
##### Source:
```cpp
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
```

#### Denominator in Remainder
Self explanatory helper used in [Division and Modulus](#Division) to calculate the next digit of the quotient in the appropriate step.
##### Source:
```cpp
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
```

### Binary
#### Get Binary Representation
Creates a binary representation of the called upon [big::Integer](#Default%20Constructor).
##### Source:
```cpp
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
```

#### Construct from Binary
Constructs a [big::Integer](#Default%20Constructor) given the passed characters.
##### Source:
```cpp
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
```

## Non-Member Functions
### Strings
#### Ostream Operator
Sends the string representation of a [big::Integer](#Default%20Constructor) to the outbound data stream `ostream`.
##### Source:
```cpp
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
```
##### Example:
```cpp
int main() {
	big::Integer num("-12345678987654321");

	std::cout << num << "\n";
	// -12345678987654321
}
```

#### To String
Creates a string representation of a [big::Integer](#Default%20Constructor)
using the `ostream` operator on a `ostringstream` object. Little cheeky, but it works.
##### Source:
```cpp
std::string to_string(const Integer& n) {
	std::ostringstream ss;
	ss << n;
	return ss.str();
}
```
##### Example:
```cpp
int main() {
	big::Integer A(1234);
	std::string B = big::to_string(A); // B == "1234"
}
```
### Arithmetic
#### Quotient and Remainder
Finds the quotient and remainder of two *int*s in one function call. Used only in [denominator_in_remainder()](#Denominator%20in%20Remainder) to simplify the code.
##### Source:
```cpp
div_t quot_and_rem(int num, int den) {
	div_t result;
	result.quot = num / den;
	result.rem = num % den;
	return result;
}
```
