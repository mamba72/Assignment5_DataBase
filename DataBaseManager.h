/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#include "GenBST.h"
#include "FileIO.h"
#include "Faculty.h"
#include "Student.h"
#include <iostream>
class DataBaseManager
{
private:
	//private vars
	
	
	//helper functions

public:

	GenBST<int, Student*>* masterStudent;
	GenBST<int, Faculty*>* masterFaculty;


	DataBaseManager();
	~DataBaseManager();

	//functions
	void printAllStudents();
	void printAllFaculty();
	Student* findStudent(int id);
	Faculty* findFaculty(int id);

	Faculty* getStudentsAdvisor(int id);
	void printAdvisees(int id);

	void addStudent(Student* newStudent);
	void addFaculty(Faculty* newFaculty);

	bool deleteFaculty(int id);
	bool deleteStudent(int id);
	bool changeStudentsAdvisor(int studentId, int facultyId);
	bool removeAdviseeFromFaculty(int studentId, int facultyId);
	void rollback();

	//additional functions
	//Student* getStudent(int id);


};

//this class is used to signify that the user has tried to access a student that doesnt exist in the tree
class StudentDoesntExistException : public runtime_error
{
public:
	StudentDoesntExistException(string msg) : runtime_error(msg.c_str())
	{}
};

//this class is used to signify that the user has tried to access a faculty member that doesnt exist in the tree
class FacultyDoesntExistException : public runtime_error
{
public:
	FacultyDoesntExistException(string msg) : runtime_error(msg.c_str())
	{}
};