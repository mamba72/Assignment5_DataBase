/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#include "Student.h"

Student::Student()
{

}

Student::Student(int id, string name, string year, string major, double gpa, int advisor)
{
	this->id = id;
	this->name = name;
	this->level = year;
	this->major = major;
	this->gpa = gpa;
	this->advisor = advisor;
}

Student::~Student()
{

}

//overloaded << operator function
ostream& operator<<(ostream& fileOut, const Student& obj)
{
	// TODO: insert return statement here
	fileOut << obj.id << "\n" << obj.name << "\n" << obj.major << "\n" << obj.level << "\n" << obj.gpa << "\n" << obj.advisor << endl;
	return fileOut;
}

//overloaded >> operator for reading from file
std::istream& operator>>(std::istream& fileIn, Student& obj)
{
	// TODO: insert return statement here
	fileIn >> obj.id;
	fileIn >> obj.name;
	fileIn >> obj.major;
	fileIn >> obj.level;
	fileIn >> obj.gpa;
	fileIn >> obj.advisor;

	return fileIn;
}