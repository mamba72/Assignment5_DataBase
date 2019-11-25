/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#include "Faculty.h"


Faculty::Faculty(int id, string name, string level, string department) : Person(id, name, level, department)
{
	advisees = new GenLinkedList<int>();
}

Faculty::~Faculty()
{

}

GenLinkedList<int>* Faculty::getAdvisees()
{
	return advisees;
}

//overloaded << operator function
ostream& operator<<(ostream& fileOut, const Faculty& obj)
{
	fileOut << obj.id << endl;
	fileOut << obj.name << endl;
	fileOut << obj.level << endl;
	fileOut << obj.department << endl;
	fileOut << *(obj.advisees) << endl;
	return fileOut;
}

//overloaded >> operator for reading from file
std::istream& operator>>(std::istream& fileIn, Faculty& obj)
{
	// TODO: insert return statement here
	fileIn >> obj.id;
	fileIn >> obj.name;
	fileIn >> obj.department;
	fileIn >> obj.level;
	//fileIn >> obj.gpa;
	//fileIn >> obj.advisor;

	return fileIn;
}

void Faculty::addAdvisee(int studentId)
{
	advisees->insertFront(studentId);
}

bool Faculty::removeAdvisee(int studentId)
{
	advisees->remove(studentId);
}

