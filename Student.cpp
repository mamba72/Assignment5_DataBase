/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#include "Student.h"
#include <iostream>//remove

Student::Student()
{
	id = -1;
	name = "NULL";
	level = "NULL";
	department = "NULL";
	gpa = -1;
	advisor = -1;
}

Student::Student(int id, string name, string year, string major, double gpa, int advisor) : Person(id, name, year, major)
{
	/*this->id = id;
	this->name = name;
	this->level = year;
	this->department = major;*/


	this->gpa = gpa;
	this->advisor = advisor;
}

Student::~Student()
{

}

//overloaded << operator function
//ostream& operator<<(ostream& fileOut, const Student& obj)
//{
//	// TODO: insert return statement here
//	fileOut << obj.id << "\n" << obj.name << "\n" << obj.department << "\n" << obj.level << "\n" << obj.gpa << "\n" << obj.advisor << endl;
//	return fileOut;
//}

ostream& operator<<(ostream& fileOut, const Student& obj)
{
	
	fileOut << obj.id << endl;

	//write the name
	const size_t nameSize = obj.name.size();
	fileOut.write(obj.name.data(), nameSize);

	fileOut << endl;

	//write the major
	const size_t majorSize = obj.department.size();
	fileOut.write(obj.department.data(), majorSize);

	fileOut << endl;

	//write the level
	const size_t levelSize = obj.level.size();
	fileOut.write(obj.level.data(), levelSize);

	fileOut << endl;

	//write the gpa
	fileOut << obj.gpa << endl;

	//write the advisor id
	fileOut << obj.advisor << endl;

	return fileOut;
}

//overloaded >> operator for reading from file
//ifstream& operator>>(std::ifstream& fileIn, Student& obj)
//{
//	string strIn = "";
//	fileIn >> strIn;
//	cout << "ID: " << strIn << endl;
//	obj.id = stoi(strIn);
//	cout << "Inserted ID" << endl;
//	fileIn >> strIn;
//	cout << "Name: " << strIn << endl;
//	obj.setName(strIn);
//	cout << "Inserted Name" << endl;
//	fileIn >> strIn;
//	obj.department = strIn;
//	fileIn >> strIn;
//	cout << "Level: " << strIn << endl;
//	obj.level = strIn;
//	fileIn >> obj.gpa;
//	fileIn >> obj.advisor;
//
//	return fileIn;
//}

istream& operator >>(std::istream& fileIn, Student& obj)
{
	//obj.deserialize(fileIn, obj);
	
	string strIn = "";
	fileIn >> strIn;
	obj.setId(stoi(strIn));
	cout << "Inserted Id" << endl;

	size_t nameSize = 0;
	fileIn >> nameSize;
	obj.name.resize(nameSize);
	fileIn.read(&obj.name[0], nameSize);
	cout << "Inserted Name" << endl;


	cout << "returning fileIn" << endl;
	return fileIn;

}

string Student::getMajor()
{
	return getDepartment();
}

void Student::setMajor(string newMajor)
{
	setDepartment(newMajor);
}

int Student::getAdvisorId()
{
	return advisor;
}

string Student::serialize()
{
	string output = Person::serialize();
	return output;
}

void Student::setGpa(double gpa)
{
	this->gpa = gpa;
}

void Student::setAdvisorId(int advisorId)
{
	this->advisor = advisorId;
}

//void Student::deserialize(istream& fileIn)
//{
//	int numMembers = 6;
//	//string* linesFromFile = new string[6];
//	string linesFromFile[6];
//	string line = "";
//	for (int i = 0; i < numMembers; ++i)
//	{
//		getline(fileIn, line);
//		//if the line is empty, just skip it
//		if (line == "")
//		{
//			--i;
//			continue;
//		}
//
//		linesFromFile[i] = line;
//		cout << "Line Num: " << i << " Contents: " << line << endl;
//	}
//
//	/*cout << "Obj Name: " << this->name << endl;
//	cout << "Obj name size: " << sizeof(name) << endl;
//	cout << "Obj name length: " << name.length() << endl;*/
//
//	int id = stoi(linesFromFile[0]);
//	string name = linesFromFile[1];
//	string year = linesFromFile[2];
//	string major = linesFromFile[3];
//	double gpa = stod(linesFromFile[4]);
//	int advisor = stoi(linesFromFile[5]);
//
//	cout << "Inserting to student" << endl;
//	//obj = Student(id, name, year, major, gpa, advisor);
//	setId(id);
//	cout << "Inserted ID" << endl;
//	setName(name);
//	//this->name = name;
//	cout << "Inserted Name" << endl;
//	setLevel(year);
//	//this->level = year;
//	cout << "Inserted level" << endl;
//	setMajor(major);
//	cout << "Inserted Major" << endl;
//	setGpa(gpa);
//	cout << "Inserted GPA" << endl;
//	setAdvisorId(advisor);
//	cout << "Inserted Advisor" << endl;
//}


Student* Student::deserialize(istream& fileIn, Student& obj)
{

}