// Tester file for the BigInt class
// @file BigInt_Tester.cpp
// @author Ethan Rudy
// @version 1.0

#include "BigInt.h"
#include <iostream>
#include <chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << BigInt("18446744073709551615") + 1 << "\n";

	auto end = std::chrono::high_resolution_clock::now();
	auto dura = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Found in " << dura.count() << " microseconds\n";
}
