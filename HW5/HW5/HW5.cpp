#include "HashTable.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>



using namespace std;

// created hash function
int hashFunction(const Profile & toHash) {
	int index;
	
	int asciiNumber = 0;
	for (int i = 0; i < toHash.user.size(); i++) {
		asciiNumber += toHash.user[i];
	}

	return index = asciiNumber % 7;
}

int main() {
	
	// set function pointer to hashFunction
	int(*hashFuncPtr)(const Profile &) = hashFunction;

	// created hash table using the function pointer, forcing length seven
	HashTable<Profile> hashTable (hashFuncPtr, 7);
	// placeholder profile
	Profile tempProfile;



	// reading from file
	ifstream inThisFile("presidentsWstates.txt");
	// placeholder string
	string currentString;

	// TODO fix this
	cout << endl << "Adding friends to list..." << endl;
	if (inThisFile.is_open())
	{
		while (getline(inThisFile, currentString))
		{
			stringstream ss(currentString);
			getline(ss, tempProfile.user, '\t');
			
			
			// TODO convert names to ASCII number

			
			// TODO fix enqueueing profile into hash table
			hashTable.();
		}
	}

	return 0;
}
