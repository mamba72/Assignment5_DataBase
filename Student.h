/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#pragma once
#include <fstream>
using namespace std;
class Student
{
public:
	Student();
	~Student();

	//variables
	int id;
	string name;
	string level;
	string major;
	double gpa;
	int advisor;//faculty ID number

	//helper functions


	//overloaded operator functions
	//(got these from here: https://thispointer.com/c-how-to-read-or-write-objects-in-file-serializing-deserializing-objects/ )
	//overload the << operator for writing to file
	friend ostream& operator<< (ostream& fileOut, const Student& obj);
	//overload the >> operator for reading from file
	friend std::istream& operator>> (std::istream& fileIn, Student& obj);
};