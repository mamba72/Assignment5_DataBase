/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#pragma once
#include <string>
using namespace std;
class Person
{
protected:
	//variables
	int id;
	string name;
	string level;
	string department;

public:
	Person();
	Person(int id, string name, string level, string department);
	~Person();

	int getId();
	string getName();
	string getLevel();
	string getDepartment();

	void setId(int id);
	void setName(string name);
	void setLevel(string level);
	void setDepartment(string department);

	string serialize();

	/*int id;
	string name;
	string level;
	string department;*/
};