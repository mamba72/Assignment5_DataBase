/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/


#include "FileIO.h"

const string FileIO::studentFileName = "studentTable.txt";
const string FileIO::facultyFileName = "facultyTable.txt";

/*
This function will deserialize the student tree from the studentTable file and return it. 
If the file does not exist, it will return an empty student tree.
*/
GenBST<int, Student*>* FileIO::ReadStudentTree()
{	
	ifstream file;
	file.open(studentFileName);

	GenBST<int, Student*>* studentTree = new GenBST<int, Student*>(); //studentTree;

	//if the file cant be opened, create an empty bst
	if (file.is_open() == false)
	{
		return studentTree;
	}
		
	//read the file
	file.read((char*)&studentTree, sizeof(studentTree));

	return studentTree;
}

/*
This function will deserialize the faculty tree from the facultyTable file and return it.
If the file does not exist, it will return an empty faculty tree.
*/
GenBST<int, Faculty*>* FileIO::ReadFacultyTree(string fileName)
{
	ifstream file;
	file.open(facultyFileName);

	GenBST<int, Faculty*>* facultyTree;

	//if the file cant be opened, create an empty bst
	if (file.is_open() == false)
		return new GenBST<int, Faculty*> (); //facultyTree;

	//read the file
	file.read((char*)&facultyTree, sizeof(facultyTree));

	return facultyTree;
}

//bool FileIO::WriteStudentTree(GenBST<int, Student*>* tree)
//{
//	ofstream file_obj;
//	//open the file
//	file_obj.open(studentFileName);
//
//	//if the file didnt open, return false
//	if (file_obj.is_open() == false)
//		return false;
//
//	//write the object to the file
//	file_obj.write((char*)&tree, sizeof(tree));
//	return true;
//}

bool FileIO::WriteFacultyTree(GenBST<int, Faculty*>* tree)
{
	ofstream file_obj;
	//open the file
	file_obj.open(facultyFileName);

	//if the file didnt open, return false
	if (file_obj.is_open() == false)
		return false;

	//write the object to the file
	file_obj.write((char*)&tree, sizeof(tree));
	return true;
}

//using strings and doing it myself because the other way doesnt seem to work
bool FileIO::WriteStudentTree(GenBST<int, Student*>* tree)
{
	

}