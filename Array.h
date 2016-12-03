#pragma once

// Array.h -- class template for an adjustable array
// When debugging, use #define DEBUG_ARRAY above your #include "Array.h".
// When done debugging, comment out #define DEBUG_ARRAY for better performance. 
// The constructor, copy constructor, overloaded assignment, and changeSize 
// functions can cause an exception to be thrown if out of heap memory. 

#include <string>
#include <iostream>

using namespace std;

template <class DataType>
class Array
{
public:
	Array();
	Array(int size);
	Array(const Array<DataType> & ap);
	~Array();
	Array<DataType> & operator =(const Array<DataType> & right);
	inline DataType & operator [ ](int index);
	void changeSize(int newSize);	// will not alter values unless newSize is smaller
									// than current capacity; in this case, the values
									// from 0 to newSize - 1 will not be altered
	inline int length() const;	    // returns the current capacity of the array
	string err() const;		    // returns error message from errorCode
private:
	DataType *elements;		// points to the dynamic array
	int capacity;
	DataType dud;		    // returned from operator [ ] if index error occurs
	int errorCode;			// contains code for error if array misuse occurs
	inline void deepCopy(const Array<DataType> & original);
};

// Array.cpp -- function definitions for an array

// Error codes -- use powers of 2
// 0	No error.
// 1	Nonpositive size passed into constructor.
// 2	Invalid index was used.
// 4	Nonpositive new size passed into changeSize function

// made the default constructor make arrays size 2 by default
template <class DataType>
Array<DataType>::Array() {
	capacity = 2;
	elements = new DataType[capacity];
}

template <class DataType>
Array<DataType>::Array(int size)
{
	if (size < 1) {
		capacity = 1;
		errorCode = 1; // nonpositive size
	}
	else {
		capacity = size;
		errorCode = 0; // no error
	}

	elements = new DataType[capacity];
}

template <class DataType>
Array<DataType>::Array(const Array<DataType> & ap)
{
	deepCopy(ap);
}

template <class DataType>
Array<DataType>::~Array()
{
	delete[] elements;
}

template <class DataType>
Array<DataType> & Array<DataType>::operator =(const Array<DataType> & right)
{
	if (this == &right)
		return *this;
	delete[] elements;
	deepCopy(right);

	return *this;
}

template <class DataType>
inline DataType & Array<DataType>::operator [ ](int index)
{
#ifdef DEBUG_ARRAY
	if (index < 0 || index >= capacity) {
		errorCode |= 2;  // invalid index
		return dud;
	}
#endif
	return elements[index];
}



// will not alter values unless newSize is smaller than current capacity; 
// in this case, the values from 0 to newSize - 1 will not be altered
template <class DataType>
void Array<DataType>::changeSize(int newSize)
{
	if (newSize < 1)
	{
		errorCode |= 4; // nonpositive new size 
		return;
	}

	DataType *newArray = new DataType[newSize];

	int limit = (newSize > capacity) ? capacity : newSize;

	for (int i = 0; i < limit; i++)
		newArray[i] = elements[i];

	delete[] elements;

	elements = newArray;

	capacity = newSize;
}

template <class DataType>
inline int Array<DataType>::length() const
{
	return capacity;
}

template <class DataType>
string Array<DataType>::err() const
{

	if (errorCode == 0)
		return "No error.\n";

	string errorMessage = "";
	if (errorCode & 1) { // nonpositive size
		errorMessage += "Nonpositive size passed into constructor, so\n";
		errorMessage += "the capacity was set to 1 by default.\n";
	}
	if (errorCode & 2)  // invalid index
		errorMessage += "Index out of range.\n";
	if (errorCode & 4) { // nonpositive new size in changeSize
		errorMessage += "Nonpositive size passed into changeSize, so\n";
		errorMessage += "the size of the array was not changed.\n";
	}

	return errorMessage;
}


template <class DataType>
inline void Array<DataType>::deepCopy(const Array<DataType> & original)
{
	capacity = original.capacity;
	errorCode = original.errorCode;
	elements = new DataType[capacity];
	for (int i = 0; i < capacity; i++)
		elements[i] = original.elements[i];
}

