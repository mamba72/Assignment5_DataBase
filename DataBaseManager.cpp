/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#include "DataBaseManager.h"

DataBaseManager::DataBaseManager()
{
	masterStudent = new GenBST<int, Student*>();// FileIO::ReadStudentTree();
	masterFaculty = new GenBST<int, Faculty*>();//FileIO::ReadFacultyTree();

	cout << "Master Student tree: " << masterStudent << endl;
	cout << "Is master student null?: " << (masterStudent == NULL) << endl;

	cout << "(From Constructor) Printing student tree straight from file:\n";
	cout << "Number of nodes in student tree: " << masterStudent->numNodes << endl;
	masterStudent->printTree();
	cout << endl;
}

DataBaseManager::~DataBaseManager()
{
	//FileIO::WriteFacultyTree(masterFaculty);
	//FileIO::WriteStudentTree(masterStudent);

	cout << "Wrote trees to file.\n";
}

void DataBaseManager::printAllStudents()
{
	masterStudent->printTree();
}

void DataBaseManager::printAllFaculty()
{
	masterFaculty->printTree();
}

Student* DataBaseManager::findStudent(int id)
{
	try
	{
		return masterStudent->getNode(id);
	}
	catch (NodeNotFoundException e)
	{
		throw StudentDoesntExistException("The student by the id of " + to_string(id) + " is not in the tree.");
	}
	
}

Faculty* DataBaseManager::findFaculty(int id)
{
	try
	{
		return masterFaculty->getNode(id);
	}
	catch (NodeNotFoundException e)
	{
		throw FacultyDoesntExistException("The faculty member by the id of " + to_string(id) + " is not in the tree.");
	}
}

Faculty* DataBaseManager::getStudentsAdvisor(int id)
{
	//get the student we are talking about
	Student* student = masterStudent->getNode(id);
	//return that student's advisor
	return masterFaculty->getNode(student->getAdvisorId());
}

//takes in a faculty id and prints all of the students
void DataBaseManager::printAdvisees(int id)
{
	Faculty* faculty = masterFaculty->getNode(id);
	int* adviseeArray = faculty->getAdvisees()->toArray();
	for (int i = 0; i <= faculty->getAdvisees()->getSize(); ++i)
	{
		cout << masterStudent->getNode(adviseeArray[i]) << endl;
	}
}

void DataBaseManager::addStudent(Student* student)
{
	//masterStudent->insert(student->getId(),student);
	masterStudent->insert(student->id, student);
}

void DataBaseManager::addFaculty(Faculty* faculty)
{
	masterFaculty->insert(faculty->getId(), faculty);
}

bool DataBaseManager::deleteFaculty(int id)
{
	return masterFaculty->deleteNode(id);
}

bool DataBaseManager::deleteStudent(int id)
{
	return masterStudent->deleteNode(id);
}






//additional functions
//Student* DataBaseManager::getStudent(int id)
//{
//	return masterStudent->getNode(id);
//}