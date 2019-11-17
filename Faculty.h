/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#include "Person.h"
#include "GenLinkedList.h"
#pragma once
class Faculty : public Person
{
private:
	GenLinkedList<int>* advisees;
public:
	Faculty(int id, string name, string level, string department);
	~Faculty();

	GenLinkedList<int>* getAdvisees();


	//overloaded operator functions
	//(got these from here: https://thispointer.com/c-how-to-read-or-write-objects-in-file-serializing-deserializing-objects/ )
	//overload the << operator for writing to file
	friend ostream& operator<< (ostream& fileOut, const Faculty& obj);
	//overload the >> operator for reading from file
	friend std::istream& operator>> (std::istream& fileIn, Faculty& obj);
};