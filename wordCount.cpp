#include<stdio.h>
#include<stdlib.h>
#include <iomanip>
#include <iostream>
#include<string>
#include<ctype.h>
#include<vector>

using namespace std;

//Create a struxt named word that contains a string for the word and integer for its number of appearances
struct word{
	string theWord;
	int theCount;
};

//Create a vector of words
vector<word> myVector;

//Create a class HashTable
class HashTable {
	private:
		static const int size = 100; //Has a constant size of 100 
		struct bucket{ //Creates a struct for the buckets
			string aString; //Contains a string that holds the word
			int count; //Contains an integer to hold the number of appearances
			bucket* next; //Creates a pointer to another bucket
		};
		bucket* table[size]; //Creates an array of buckets

	public:
		HashTable(); //Constructor
		int hash(string aString); //Finds an index for the string that is inputted
		void insertAHash(string aString); //Inserts the string into the hash table
		int partitionStepCount(vector<word> &aVector, int low, int high); //Partition step for quicksort in regards to the word
		void quickSortCount(vector<word> aVector, int left, int right); //Quicksort in regards to the word
		int partitionStepWord(vector<word> &aVector, int low, int high); //Partition step in regards to the count
		void quickSortWord(vector<word> aVector, int left, int right); //Quicksort in regards to the count
		void sortByWord(); //Sorts the words alphabetically
		void sortByCount(); //Sorts the words by number of appearances in reverse numeric order
};

//Constructor that sets each bucket to have empty contents
HashTable::HashTable() {
	for (int i = 0; i < size; i++) {
		table[i] = new bucket;
		table[i]->aString = "";
		table[i]->count = 0;
		table[i]->next = NULL;
	}
}

//Function that finds an index to a bucket for the string to be placed in
int HashTable::hash(string aString) {
	int index, sum = 0;
	for (double i = 0; i < aString.length(); i++) { //Calculate the sum of the string based as its ASCII value
		sum = sum + (int)aString[i];
	}
	index = sum % size; //The index is the remainder of the sum divided by the size
	return index;
}

//Function that inserts a string into the hash table
void HashTable::insertAHash(string aString) {
	int index = hash(aString); //Calls hash to find the index of the bucket that the string should be placed in
	if (table[index]->aString != "") { //if the bucket is not empty
		bucket* tempBucket = table[index]; //Creates a temporary bucket
		bucket* newBucket = new bucket; //Creates a bucket to be placed into the hash table
		//Traverse until you find the last bucket or you find a match to your string
		while (tempBucket->next != NULL && tempBucket->aString != aString)
			tempBucket = tempBucket->next;

		//if the strings match then increase the count
		if (tempBucket->aString == aString) {
			tempBucket->count++;
		}

		//If the strings do not match then place the string into the bucket
		else {
			newBucket->aString = aString;
			newBucket->count = 1;
			newBucket->next = NULL;
			tempBucket->next = newBucket;
		}
	}

	//If the bucket is empty then place the string into the bucket
	else {
		table[index]->aString = aString;
		table[index]->count = 1;
		table[index]->next = NULL;
	}
}

//Function for partitioning a vector based on the words count value
int HashTable::partitionStepCount(vector<word> &aVector, int low, int high) {
        int pivot = aVector[high].theCount; //Sets the pivot point to the last element
        int p = (low - 1);
        for (int j = low; j <= high - 1; j++) { //Goes through each element in the vector
                if (aVector[j].theCount <= pivot) { //Checks to see if the jth elements count is less than or equal to the pivot elements count
                        p++;
                        swap(aVector[p], aVector[j]); //Swaps the pth element and the jth element
                }
        }
        swap (aVector[p + 1], aVector[high]); //Swaps the last element with the pivot
        return (p + 1);
}

//Function for using quicksort to sort through a vector based on the words count
void HashTable::quickSortCount(vector<word> aVector, int left, int right) {
        if (left <= right) {
                int pivotNum = partitionStepCount(myVector, left, right); //Uses the partitionStep function to find a pivot point
                quickSortCount(myVector, left, pivotNum - 1); //Traverse through left side of the vector
		quickSortCount(myVector, pivotNum + 1, right); //Traverse through the right side of the vector
        }
}

//Sort the vector based on the count values of the words
void HashTable::sortByCount() {
	int numWords = 0;
	for (int i = 0; i < size; i++) { //Go through each bucket
		if (table[i]->aString != "") { 
			bucket* tempBucket = table[i];
			//Place each buckets contents into the vector unless it is empty
			do {
				numWords++;
				word tempWord;
				tempWord.theWord = tempBucket->aString;
				tempWord.theCount = tempBucket->count;
				myVector.push_back(tempWord);
				tempBucket = tempBucket->next;
			}
			while (tempBucket != NULL);
		}
	}
	//Sort the vector based on the words count value
	quickSortCount(myVector, 0, numWords);

	//print the vector in reverse numeric order
	for (int j = numWords; j > 0 ; j--) {
		cout << myVector[j].theWord << " " << myVector[j].theCount << endl;
	}
			
}

//Function for partitioning a vector based on the words ASCII value
int HashTable::partitionStepWord(vector<word> &aVector, int low, int high) {
        string pivot = aVector[high].theWord; //Sets the pivot point to the last element
        int p = (low - 1);
        for (int j = low; j <= high - 1; j++) { //Goes through each element in the vector
                if (aVector[j].theWord <= pivot) { //Checks to see if the jth elements string is less than or equal to the pivot elements string
                        p++;
                        swap(aVector[p], aVector[j]); //Swaps the pth element and the jth element
                }
        }
        swap (aVector[p + 1], aVector[high]); //Swaps the last element with the pivot
        return (p + 1);
}

//Function for using quicksort to sort through a vector based on the words ASCII value
void HashTable::quickSortWord(vector<word> aVector, int left, int right) {
        if (left <= right) {
                int pivotNum = partitionStepWord(myVector, left, right); //Uses the partitionStep function to find a pivot point
                quickSortWord(myVector, left, pivotNum - 1); //Traverse through the left side of the vector
                quickSortWord(myVector, pivotNum + 1, right); //Traverse through the right side of the vector
        }
}

//Sort the vector based on the words ASCII values
void HashTable::sortByWord() {
        int numWords = 0;
        for (int i = 0; i < size; i++) { //Go through each bucket
                if (table[i]->aString != "") {
                        bucket* tempBucket = table[i];
			//Place each buckets content into the vactor unless it is empty
                        do {
                                numWords++;
                                word tempWord;
                                tempWord.theWord = tempBucket->aString;
                                tempWord.theCount = tempBucket->count;
                                myVector.push_back(tempWord);
                                tempBucket = tempBucket->next;
                        }
                        while (tempBucket != NULL);
                }
        }
	//Sort the vector based on the words ASCII value
        quickSortWord(myVector, 0, numWords);
	//print the vector in alphabetical order
        for (int j = 1; j <= numWords ; j++) {
                cout << myVector[j].theWord << " " << myVector[j].theCount << endl;
        }

}

int main() {
	HashTable aHashTable; //Create a hash table
	string myString; //Create a string to hold input
	while(getline(cin, myString)) {
		//Look at each line of text
		std::stringstream ss(myString); 
		while(getline(ss,myString,' ')) { //Keep going until there is a space
			int index = 0;
			//Check each character for punctuation
			while(myString[index]) {
				//if punctuation is found then split the word into two words
				if (ispunct(myString[index]) && (myString[index] != '_')) {
					string tempString1;
					string tempString2;
					for (int i = 0; i < index; i++)
						tempString1 = tempString1 + myString[i];
					for (double j = index + 1; j < myString.length(); j++)
						tempString2 = tempString2 + myString[j];
					//Insert into hash table
					if (tempString1.empty() == 0){
						aHashTable.insertAHash(tempString1);
					}
					myString = tempString2;
					index = 0;
				}
				else 
					index++;
			}
			//insert into hash table
			if (myString.empty() == 0){
				aHashTable.insertAHash(myString);
			}
		}
	}
	aHashTable.sortByWord(); //Sort and print the hash table in alphabetical order
	cout << endl;
	aHashTable.sortByCount(); //Sort and print the hash table in reverse numerical order
	return 0;
}
