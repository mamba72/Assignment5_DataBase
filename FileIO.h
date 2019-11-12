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

//template<class T>
class FileIO
{
private:
	//static GenBST<T>* ReadTree();
public:

	//FileIO();
	//~FileIO();

	static GenBST<Student>* ReadStudentTree();
	static GenBST<Faculty>* ReadFacultyTree();

	//static bool WriteTree(GenBST<T>* tree);
	static bool WriteStudentTree(GenBST<Student>* tree);
	//static bool WriteFacultyTree(GenBST<Faculty>* tree);
};

/*
bool FileIO::WriteStudentTree(GenBST<Student>* tree)
{

}
*/


//the main function that will be doing the actual reading
/*
template<class T>
GenBST<T>* FileIO<T>::ReadTree()
{
	if (new T == new Student)
	{

	}
	GenBST<T>* myTree = new GenBST<T>();
	return myTree;

}

template<class T>
GenBST<Student>* FileIO<T>::ReadStudentTree()
{
	GenBST<Student>* myTree = ReadTree<Student>();
	return myTree;
}

template<class T>
GenBST<Faculty>* FileIO<T>::ReadFacultyTree()
{

}
*/