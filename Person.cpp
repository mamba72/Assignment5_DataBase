/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#include "Person.h"

Person::Person()
{

}

Person::Person(int id, string name, string level, string department)
{
	this->id = id;
	this->name = name;
	this->level = level;
	this->department = department;
}

Person::~Person()
{

}

//gitters
int Person::getId()
{
	return id;
}

string Person::getName()
{
	return name;
}

string Person::getLevel()
{
	return level;
}

string Person::getDepartment()
{
	return department;
}

//setters
void Person::setId(int id)
{
	this->id = id;
}

void Person::setName(string name)
{
	this->name = name;
}

void Person::setLevel(string level)
{
	this->level = level;
}

void Person::setDepartment(string department)
{
	this->department = department;
}

//returns a string of this person's information
string Person::serialize()
{
	string output = "";

	output += id + "\n";
	output += name + "\n";
	output += level + "\n";
	output += department + "\n";
	return output;
}