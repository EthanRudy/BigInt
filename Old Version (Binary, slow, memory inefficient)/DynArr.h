#pragma once

#include "CustExcep.h"

#include <string>

// REMOVE
#include <iostream>

template <typename T> class DynArr
{
public:
	// Pointer array
	T* ptr = NULL;
	// Size
	int size = NULL;
	// Default value
	T def = NULL;

	/**
	* Default Constructor
	* 
	* Creates a new empty Dynamic Array object
	*/
	DynArr() {
		this->ptr = NULL;
		this->size = NULL;
	}

	/**
	* Array Constructor
	* 
	* Creates a new Dynamic Array object
	* 
	* @param arr[] An array of type T
	* @param s An integer storing arr's length
	*/
	DynArr(T arr[], int s) {
		this->ptr = arr;
		this->size = s;
	}

	/**
	* Default Value Constructor
	* 
	* Crease a new Dynamic Array object
	* 
	* @param d The default initialized value of the object
	* @param s An integer storing the objects desired length
	*/
	DynArr(T d, int s) {
		this->ptr = (T*)malloc(s * sizeof(T));

		if (ptr == NULL) {
			std::cout << "Memory Not allocated,\n";
			exit(0);
		}

		this->def = d;
		for (int i = 0; i < s; ++i) {
			ptr[i] = d;
		}
		this->size = s;
	}
	
	/**
	* Copy Constructor
	* 
	* @param o The Dynamic Array to be hard copied
	*/
	DynArr(const DynArr& o) {
		T* newPTR = (T*)malloc(o.size * sizeof(T));
		for (int i = 0; i < o.size; ++i) {
			newPTR[i] = o.ptr[i];
		}

		if (ptr != NULL) { free(ptr); }
		ptr = newPTR;

		size = o.size;
		def = o.def;
	}

	/**
	* Assignment Operator
	*/
	DynArr operator=(const DynArr& o) {
		if (this == &o) {
			return *this;
		}

		T* newPTR = (T*)malloc(o.size * sizeof(T));
		for (int i = 0; i < o.size; ++i) {
			newPTR[i] = o.ptr[i];
		}

		if (ptr != NULL) { free(ptr); }
		ptr = newPTR;

		size = o.size;
		def = o.def;

		return *this;
	}

	/*
		Destructor
	*/
	~DynArr() {
		free(ptr);
		ptr = NULL;
	}

	/**
	* Resize
	* 
	* Resizes a Dynamic Array Object
	* 
	* @param amount An integer representing how many indices are to be removed/added
	*/
	void resize(int amount) {
		if (amount == 0) { return; }
		else if (amount > 0) {
			if (def == NULL) { throw CustExcep("No default value selected/saved."); }
		}

		int newSize = this->size + amount;
		if (newSize < 0) { throw CustExcep("New size cannot be less than 0."); }

		T* newPTR = (T*)malloc(newSize * sizeof(T));

		if (newSize < this->size) {
			for (int i = 0; i < newSize; ++i) {
				newPTR[i] = this->ptr[i];
			}
		}
		else {
			for (int i = 0; i < this->size; ++i) {
				newPTR[i] = this->ptr[i];
			}

			for (int i = this->size; i < newSize; ++i) {
				newPTR[i] = this->def;
			}
		}

		this->size = newSize;
		free(ptr);
		ptr = newPTR;
	}

	/**
	* Resize
	*
	* Resizes a Dynamic Array Object
	*
	* @param amount An integer representing how many indices are to be removed/added
	* @param d The default value for any new indices
	*/
	void resize(int amount, T d) {

		if (amount == 0) { return; }

		int newSize = this->size + amount;
		if (newSize < 0) { throw CustExcep("New size cannot be less than 0."); }

		T* newPTR = (T*)malloc(newSize * sizeof(T));

		if (newSize < this->size) {
			for (int i = 0; i < newSize; ++i) {
				newPTR[i] = this->ptr[i];
			}
		}
		else {
			for (int i = 0; i < this->size; ++i) {
				newPTR[i] = this->ptr[i];
			}

			for (int i = this->size; i < newSize; ++i) {
				newPTR[i] = d;
			}
		}

		this->size = newSize;
		free(ptr);
		ptr = newPTR;
	}

	/**
	* Range
	* 
	* Returns a Dynamic Array object of a sub-range
	* 
	* @param start The starting index
	* 
	* @return res the DynArr range
	*/
	DynArr<T> range(int start) {
		DynArr<T> res;
		res.size = this->size - start;
		res.ptr = (T*)malloc(res.size * sizeof(T));
		int resind = 0;
		for (int i = start; i < this->size; ++i) {
			res.ptr[resind] = this->ptr[i];
			++resind;
		}

		return res;
	}

	/**
	* Range
	* 
	* Returns a Dynamic Array object of a sub-range
	* 
	* @param start The starting index
	* @param end The ending index
	* 
	* @return res The DynArr range
	*/
	DynArr<T> range(int start, int end) {
		DynArr<T> res;
		res.size = end - start;
		res.ptr = (T*)malloc(res.size * sizeof(T));
		int resind = 0;
		for (int i = start; i < end; ++i) {
			res.ptr[resind] = this->ptr[i];
			++resind;
		}

		return res;

	}
	
	/**
	* Shift Left
	*/
	DynArr<T> shiftLeft(T v,int amount) {
		DynArr<T> res = DynArr<T>(v, this->size + amount);
		for (int i = 0; i < this->size; ++i) {
			res.ptr[i + amount] = this->ptr[i];
		}
		return res;
	}
};

namespace std {

	/**
	* To String
	* 
	* Overloads thestandard to_string() function for Dynamic Array objects
	* 
	* @param arr The Dynamic Array object
	* 
	* @return str The string representation
	*/
	template <typename T>
	std::string to_string(DynArr<T> arr) {
		std::string str = "";

		for (int i = 0; i < arr.size; ++i) {
			str += std::to_string(arr.ptr[i]);
			if (i < arr.size - 1) {
				str += ", ";
			}
		}

		return "{ " + str + " }";
	}

	/**
	* To String (Reverse)
	* 
	* Converts the Dynamic Array object to string form but reverse
	* 
	* @param arr The Dynamic Array object
	* 
	* @return str The string representation
	*/
	template <typename T>
	std::string to_string_r(DynArr<T> arr) {
		std::string str = "";

		for (int i = arr.size - 1; i > -1; --i) {
			str += std::to_string(arr.ptr[i]);
			if (i > 0) {
				str += ", ";
			}
		}

		return "{ " + str + " }";
	}
}
