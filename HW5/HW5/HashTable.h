#pragma once

#include "Queue.h"
#include "Array.h"
#include <iostream>


// HashTable.h -- class template for a hash table using chaining

// client must provide a hash function with the following characteristics:
//		1 input parameter of DataType (see below), passed by const reference
//	    returns an integer between 0 and size - 1, inclusive, where size is the
//		number of elements in the hash table
//		the name of the function is passed as the first parameter to the HashTable 
//		constructor
//		client may make as many hash functions for as many HashTables as desired
// if a struct is used for DataType, a typical use of retrieve, remove, and update would
// be to set the key of an object and then pass the object into the function
// retrieve, remove, and update will return false if:
//		(1) the hash function supplied above does not return a valid index
//	    (2) the supplied key or element cannot be found in the hash table
// otherwise, these functions will return true if successful
// For retrieve, remove and update functions, if you are using an object as an element, a 
// typical use would be to set the key of the desired object to retrieve, remove, or
// update; then pass the object into the function.
// If an object of a struct is used for DataType, the == operator must be 
// overloaded for it; the left and right operands are both DataType objects
// the == comparison is used for finding elements, usually by key value
//		Exceptions can be thrown in the constructor, the (default) copy constructor,
// the (default) assignment operator, or the insert function if out of heap memory.



// Uses the struct Profile made in earlier assignments
struct Profile {
	std::string user;
	// removed state because it is unused
	// std::string state;

	// overloaded operator for printing out the contents of info
	friend std::ostream& operator << (std::ostream& os, Profile profile) {
		os << std::endl << profile.user << std::endl;
		return os;
	}
};


template <class DataType>
class HashTable
{
public:
	HashTable(int(*hf)(const DataType &), int s);
	bool insert(const DataType & newObject); // returns true if successful; returns
											 // false if invalid index was returned 
											 // from hash function
	bool retrieve(DataType & retrieved);  // see description above class template
	bool remove(DataType & removed);      // see description above class template 
	bool update(DataType & updateObject); // see description above class template
	void makeEmpty();
private:
	Array<Queue<DataType>> table;
	int(*hashfunc)(const DataType &); // pointer to hash function from client
};

// HashTable.cpp -- function definitions for a hash table using chaining

template <class DataType>
HashTable<DataType>::HashTable(int(*hf)(const DataType &), int s)
	: table(s)
{
	hashfunc = hf;
}

template <class DataType>
bool HashTable<DataType>::insert(const DataType & newObject)
{
	int location = hashfunc(newObject);
	if (location < 0 || location >= table.length())
		return false;
	table[location].insert(newObject);
	return true;
}

template <class DataType>
bool HashTable<DataType>::retrieve(DataType & retrieved)
{
	int location = hashfunc(retrieved);
	if (location < 0 || location >= table.length())
		return false;
	if (!table[location].retrieve(retrieved))
		return false;
	return true;
}

template <class DataType>
bool HashTable<DataType>::remove(DataType & removed)
{
	int location = hashfunc(removed);
	if (location < 0 || location >= table.length())
		return false;
	if (!table[location].remove(removed))
		return false;
	return true;
}

template <class DataType>
bool HashTable<DataType>::update(DataType & updateObject)
{
	int location = hashfunc(updateObject);
	if (location < 0 || location >= table.length())
		return false;
	if (!table[location].find(updateObject))
		return false;
	table[location].replace(updateObject);
	return true;
}

template <class DataType>
void HashTable<DataType>::makeEmpty()
{
	for (int i = 0; i < table.length(); i++)
		table[i].makeEmpty();
}


