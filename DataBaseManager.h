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
	GenBST<Student> masterStudent;
	GenBST<Faculty> masterFaculty;


public:
	DataBaseManager();
	~DataBaseManager();



};