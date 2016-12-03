#include "HashTable.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>



using namespace std;

// created hash function
int hashFunction(const Profile & toHash) {

	// hash table index to be returned
	int index;
	
	// placeholder for the ASCII sum of the name strings
	int asciiNumber = 0;

	// loop to find the ASCII sum of the usernames
	for (int i = 0; i < toHash.user.size(); i++) {
		asciiNumber += toHash.user[i];
	}

	// index will be the remainder of the ASCII divided by 7
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

	// loop to add names to table
	cout << endl << "Adding names to table..." << endl;
	if (inThisFile.is_open())
	{
		while (getline(inThisFile, currentString))
		{
			stringstream ss(currentString);
			getline(ss, tempProfile.user, '\t');
			
			hashTable.insert(tempProfile);
		}
	}

	// print current contents of the table
	hashTable.printTable();



	return 0;
}
