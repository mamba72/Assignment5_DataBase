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
const string FileIO::backupFolderName = "Backups";

/*
This function will deserialize the student tree from the studentTable file and return it. 
If the file does not exist, it will return an empty student tree.
*/
GenBST<int, Student*>* FileIO::ReadStudentTree(string fileName)
{	
	ifstream file;
	file.open(fileName);

	GenBST<int, Student*>* studentTree;// = new GenBST<int, Student*>(); //studentTree;

	//if the file cant be opened, create an empty bst
	if (file.is_open() == false)
	{
		cout << "Couldnt open file named " << fileName << endl;
		return new GenBST<int, Student*>();
	}
		
	//read the file
	//file.read((char*)&studentTree, sizeof(studentTree));
	/*Student* newStudent;

	while (file.eof() == false)
	{
		newStudent = Student::readFromFile(file);
		studentTree->insert(newStudent->getId(), newStudent);
		cout << "Inserted student by the name of " << newStudent->getName() << endl;
	}*/

	studentTree = deserializeStudentTree(file);
	file.close();
	return studentTree;
}

/*
This function will deserialize the faculty tree from the facultyTable file and return it.
If the file does not exist, it will return an empty faculty tree.
*/
GenBST<int, Faculty*>* FileIO::ReadFacultyTree(string fileName)
{
	ifstream file;
	file.open(fileName);

	GenBST<int, Faculty*>* facultyTree;

	//if the file cant be opened, create an empty bst
	if (file.is_open() == false)
	{
		cout << "Couldnt open file named " << fileName << endl;
		return new GenBST<int, Faculty*>(); //facultyTree;
	}
		

	//read the file
	//file.read((char*)&facultyTree, sizeof(facultyTree));

	facultyTree = deserializeFacultyTree(file);

	file.close();
	return facultyTree;
}

bool FileIO::WriteFacultyTree(GenBST<int, Faculty*>* tree, string fileName)
{
	tree->serialize(fileName);

	return true;
}

//using strings and doing it myself because the other way doesnt seem to work
bool FileIO::WriteStudentTree(GenBST<int, Student*>* tree, string fileName)
{
	tree->serialize(fileName);
	return true;

}


GenBST<int, Student*>* FileIO::deserializeStudentTree(ifstream& fileIn)
{
	GenBST<int, Student*>* newTree = new GenBST<int, Student*>();

	string blankLine = "";
	//get rid of the first line because it is always the marker
	getline(fileIn, blankLine);

	deserializeStudentNode(newTree, newTree->root, fileIn);

	return newTree;
}


void FileIO::deserializeStudentNode(GenBST<int, Student*>* bst, GenTreeNode<int, Student*>* node, ifstream& fileIn)
{

	//marker for bst
	const string MARKER = "\t\t";

	int key;
	int id;
	string name;
	string year;
	string department;
	double gpa;
	int advisorId;

	string response = "empty";

	getline(fileIn, response);

	while(response == "")
	{
		//cout << "found new line" << endl;
		getline(fileIn, response);

		if (fileIn.eof() == true)
		{
			//cout << "reached end of file." << endl;
			return;
		}
			
	}

	//cout << "Response: " << response << endl;
	if (response == MARKER)
		return;

	key = stoi(response);
	//cout << "Key: " << key << endl;


	getline(fileIn, response);
	if (response == MARKER)
		return;
	id = stoi(response);


	//cout << "id: " << id << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	name = response;
	//cout << "name: " << name << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	year = response;
	//cout << "year: " << year << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	department = response;
	//cout << "major: " << department << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	gpa = stod(response);
	//cout << "gpa: " << gpa << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	advisorId = stoi(response);
	//cout << "advisorid: " << advisorId << endl;

	/*cout << "From file: " << endl;
	cout << "\t" << key << endl;
	cout << "\t" << id << endl;
	cout << "\t" << name << endl;
	cout << "\t" << year << endl;
	cout << "\t" << department << endl;
	cout << "\t" << advisorId << endl;

	cout << "Creating new node" << endl;*/
	Student* newStudent = new Student(id, name, year, department, gpa, advisorId);

	node = new GenTreeNode<int, Student*>(id, newStudent);

	bst->insert(id, newStudent);

	deserializeStudentNode(bst, node->left, fileIn);
	deserializeStudentNode(bst, node->right, fileIn);

	//GenTreeNode<int, Student*>* newNode = new GenTreeNode<int, Student*>(key, );


}



void FileIO::deserializeFacultyNode(GenBST<int, Faculty*>* bst, GenTreeNode<int, Faculty*>* node, ifstream& fileIn)
{

	//marker for bst
	const string MARKER = "\t\t";

	int key;
	int id;
	string name;
	string level;
	string department;

	string response = "empty";

	getline(fileIn, response);

	while (response == "")
	{
		//cout << "found new line" << endl;
		getline(fileIn, response);

		if (fileIn.eof() == true)
		{
			//cout << "reached end of file." << endl;
			return;
		}

	}

	//cout << "Response: " << response << endl;
	if (response == MARKER || response == "empty")
		return;

	key = stoi(response);
	//cout << "Key: " << key << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	id = stoi(response);

	//cout << "id: " << id << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	name = response;
	//cout << "name: " << name << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	level = response;
	//cout << "Level: " << level << endl;
	getline(fileIn, response);
	if (response == MARKER)
		return;
	department = response;
	//cout << "Department: " << department << endl;


	//cout << "From file: " << endl;
	//cout << "\t" << key << endl;
	//cout << "\t" << id << endl;
	//cout << "\t" << name << endl;
	//cout << "\t" << level << endl;
	//cout << "\t" << department << endl;
	////cout << "\t" << advisorId << endl;

	//cout << "Creating new node" << endl;
	Faculty* newFaculty = new Faculty(id, name, level, department);

	//read in the advisees
	do
	{
		int id = 0;
		getline(fileIn, response);
		if (response == MARKER)
			return;
		try
		{
			id = stoi(response);
		}
		catch (invalid_argument e)
		{
			//cout << "No more advisee ids found." << endl;
			break;
		}
		
		//cout << "adviseeid: " << id << endl;

		newFaculty->addAdvisee(id);
	} while (response != "");

	node = new GenTreeNode<int, Faculty*>(id, newFaculty);

	bst->insert(id, newFaculty);

	deserializeFacultyNode(bst, node->left, fileIn);
	deserializeFacultyNode(bst, node->right, fileIn);
}


GenBST<int, Faculty*>* FileIO::deserializeFacultyTree(ifstream& fileIn)
{
	GenBST<int, Faculty*>* newTree = new GenBST<int, Faculty*>();

	string blankLine = "";
	//get rid of the first line because it is always the marker
	getline(fileIn, blankLine);

	deserializeFacultyNode(newTree, newTree->root, fileIn);

	return newTree;
}


//backup the trees to files
void FileIO::backupTrees(GenBST<int, Student*>* studentTree, GenBST<int, Faculty*>* facultyTree, int backupNum)
{
	
	string studentBackupName = backupFolderName + "StudentBackup" + to_string(backupNum) + ".txt";
	string facultyBackupName = backupFolderName + "FacultyBackup" + to_string(backupNum) + ".txt";

	WriteStudentTree(studentTree,studentBackupName);

	WriteFacultyTree(facultyTree, facultyBackupName);

}

FileIO::TreeBackups* FileIO::readBackup(int backupNum)
{
	string studentBackupName = backupFolderName + "StudentBackup" + to_string(backupNum) + ".txt";
	string facultyBackupName = backupFolderName + "FacultyBackup" + to_string(backupNum) + ".txt";

	TreeBackups* backup = new TreeBackups();



	backup->studentTree = ReadStudentTree(studentBackupName);
	backup->facultyTree = ReadFacultyTree(facultyBackupName);

	return backup;
}


