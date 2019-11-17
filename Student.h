/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#pragma once
#include "Person.h"
#include <fstream>
using namespace std;
class Student : public Person
{
private:
	//double gpa;
	//int advisor;//faculty ID number

	//im doing this to essentially "hide" the getDepartment function fron the outside classes.
	//I want to do this because a student doesnt really have a department, they have a major and I want to make that clear.
	//This only works because I also have a functiont that calls this function.
	using Person::getDepartment;
	using Person::setDepartment;
	using Person::serialize;
public:
	Student();
	Student(int id, string name, string year, string major, double gpa, int advisor);
	~Student();

	//variables

	
	double gpa;
	int advisor;//faculty ID number

	//helper functions
	string getMajor();
	void setMajor(string newMajor);
	int getAdvisorId();
	void setAdvisorId(int advisorId);
	void setGpa(double gpa);

	string serialize();
	Student* deserialize(istream& fileIn, Student& obj);
	//overloaded operator functions
	//(got these from here: https://thispointer.com/c-how-to-read-or-write-objects-in-file-serializing-deserializing-objects/ )
	//overload the << operator for writing to file
	friend ostream& operator<< (ostream& fileOut, const Student& obj);
	//overload the >> operator for reading from file
	friend std::istream& operator >> (std::istream& fileIn, Student& obj);
};

