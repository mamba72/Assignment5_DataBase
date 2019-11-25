/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/

#pragma once
#include "GenBST.h"
#include "GenTreeNode.h"
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
	static const string backupFolderName;

	static void deserializeStudentNode(GenBST<int, Student*>* bst, GenTreeNode<int, Student*>* node, ifstream& fileIn);
	static void deserializeFacultyNode(GenBST<int, Faculty*>* bst, GenTreeNode<int, Faculty*>* node, ifstream& fileIn);

public:

	static GenBST<int, Student*>* deserializeStudentTree(ifstream& fileIn);
	static GenBST<int, Faculty*>* deserializeFacultyTree(ifstream& fileIn);

	static GenBST<int, Student*>* ReadStudentTree(string fileName = studentFileName);
	static GenBST<int, Faculty*>* ReadFacultyTree(string fileName = facultyFileName);

	//static bool WriteTree(GenBST<T>* tree);
	static bool WriteStudentTree(GenBST<int, Student*>* tree, string fileName = studentFileName);
	static bool WriteFacultyTree(GenBST<int, Faculty*>* tree, string fileName = facultyFileName);

	//backup stuff
	struct TreeBackups
	{
		GenBST<int, Student*>* studentTree;
		GenBST<int, Faculty*>* facultyTree;
	};

	static void backupTrees(GenBST<int, Student*>* studentTree, GenBST<int, Faculty*>* facultyTree, int backupNum);
	static TreeBackups* readBackup(int backupNum);

	static void RemoveBackups();


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