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

class DataBaseManager
{
private:
	GenBST<int, Student> masterStudent;
	GenBST<int, Faculty> masterFaculty;
	//private vars

	//helper functions

public:
	DataBaseManager();
	~DataBaseManager();

	//functions
	void printAllStudents();
	void printAllFaculty();
	Student* findStudent(int id);
	Faculty* findFaculty(int id);

	Faculty* getStudentsAdvisor(int id);
	void printAdvisees(int id);

	bool addStudent(Student* newStudent);
	bool addFaculty(Faculty* newFaculty);

	bool deleteFaculty(int id);
	bool changeStudentsAdvisor(int studentId, int facultyId);
	bool removeAdviseeFromFaculty(int studentId, int facultyId);
	void rollback();


};