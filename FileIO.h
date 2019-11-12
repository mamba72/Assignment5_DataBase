/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#pragma once
#include "GenBST.h"
#include "Faculty.h"
#include "Student.h"
#include <fstream>

//template<class T>
class FileIO
{
private:
	//static GenBST<T>* ReadTree();
	static const string studentFileName;
	const static string facultyFileName;

public:

	//FileIO();
	//~FileIO();

	static GenBST<int, Student*>* ReadStudentTree();
	static GenBST<int, Faculty*>* ReadFacultyTree(string fileName = facultyFileName);

	//static bool WriteTree(GenBST<T>* tree);
	static bool WriteStudentTree(GenBST<int, Student*>* tree);
	static bool WriteFacultyTree(GenBST<int, Faculty*>* tree);

	static bool WriteBackupOfTrees(GenBST<int, Student*> studentTree, GenBST<int, Faculty*> facultyTree);
};


//exception to tell whether the file could be opened
class CouldNotOpenFileException : public std::runtime_error
{
	//const char* msg;
public:
	CouldNotOpenFileException(const char* msg) : std::runtime_error(msg)
	{
		//this->msg = msg;
	}

	CouldNotOpenFileException(string msg) : std::runtime_error(msg.c_str())
	{
		//convert the string to a const char*
		//this->msg = msg.c_str();
	}
};