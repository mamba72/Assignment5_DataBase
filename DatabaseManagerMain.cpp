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

	studentTree->insert(me->id, me);

	FileIO::WriteStudentTree(studentTree);

	GenBST<int, Student*>* newTree;

	newTree = FileIO::ReadStudentTree();

	cout << "Is tree empty: " << newTree->isEmpty() << endl;

	if(newTree->isEmpty() == false)
		cout << "Student name: " << newTree->peek()->data->name << endl;*/




	return 0;
}
