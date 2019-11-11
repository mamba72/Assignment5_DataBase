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

template<class T>
class FileIO
{
public:

	//FileIO();
	//~FileIO();

	static GenBST<T> ReadTree(T type = new T);
	//static Student ReadStudentTree();

	static bool WriteTree(GenBST<T> tree);

};