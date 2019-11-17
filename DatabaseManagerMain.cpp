/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/


#include<iostream>
#include "DataBaseManager.h"
#include "Faculty.h"
#include "Student.h"
#include "GenBST.h"
#include "FileIO.h"

#include<fstream>
using namespace std;

int main(int argc, char** argv)
{
	cout << "Hello! Welcome to the database!" << endl;

	/*GenBST<int, Student*>* studentTree = new GenBST<int, Student*>();
	Student* me = new Student(2323381, "Stephen White", "Sophomore", "Computer Science", 3.7, 1);
	studentTree->insert(me->getId(), me);

	Student* joely = new Student(2323380, "Joely", "Sophomore", "Computer Science", 2.3, 4);
	studentTree->insert(joely->getId(), joely);

	FileIO::WriteStudentTree(studentTree);

	GenBST<int, Student*>* newTree;

	newTree = FileIO::ReadStudentTree();

	cout << "Is tree empty: " << newTree->isEmpty() << endl;
	newTree->printTree();

	if(newTree->isEmpty() == false)
		cout << "Student name: " << newTree->peek()->data->getName() << endl;*/


	//GenBST<int, Student*>* testTree = new GenBST<int, Student*>();

	//testTree->insert(5, new Student(5, "Stephen White", "Sophomore", "Compsci", 3.7, 5));
	//testTree->insert(16, new Student(16, "Stephen White2", "Sophomore", "Compsci", 3.7, 5));
	//testTree->insert(2, new Student(2, "Stephen White3", "Sophomore", "Compsci", 3.7, 5));
	//cout << "Inserted Student\n";

	////cout << testTree->getNode(5)->getName() << endl;
	//cout << testTree->getNode(5)->name << endl;
	//cout << "Peeked\n";

	//cout << "Test Tree print:" << endl;
	//testTree->printTree();

	//cout << "Serialized String:" << endl;

	//testTree->serialize("testSerialize.txt");


	//GenBST<int, Student*>* otherTestTree = new GenBST<int, Student*>("testSerialize.txt");

	//cout << "Number nodes: " << otherTestTree->numNodes << endl;





	DataBaseManager* db = new DataBaseManager();
	cout << "Created DataBase\n";

	Faculty* rene = new Faculty(23, "Rene German", "Professor", "Computer Science");
	db->addFaculty(rene);
	cout << "Added faculty\n";

	Student* studentTest = new Student(16, "Stephen White2", "Sophomore", "Compsci", 3.7, 23);
	db->addStudent(studentTest);
	cout << "Added student\n";
	//db->printAllStudents();
	//cout << "my advisor: " << db->getStudentsAdvisor(2323381) << endl;

	db->masterStudent->printTree();

	cout << "Printed tree" << endl;
	
	//cout << db->masterStudent->peek()->data->getName() << endl;

	//cout << db->getStudent(2323381)->getName() << endl;
	try
	{
		cout << db->findStudent(2323381)->getName() << endl;
	}
	catch (StudentDoesntExistException e)
	{
		cout << e.what() << endl;
	}
	catch (TreeEmptyException e)
	{
		cout << e.what() << endl;
	}

	//get the student's advisor
	Faculty* advisor = db->getStudentsAdvisor(16);
	cout << "Advisor: " << advisor << endl;

	cout << *(db->masterStudent->getNode(16)) << endl;

	cout << "Printed Students\n";

	cout << "number of nodes: " << db->masterStudent->numNodes << endl;

	//delete db;

	return 0;
}
