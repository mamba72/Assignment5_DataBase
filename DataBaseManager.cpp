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
	masterStudent = FileIO::ReadStudentTree();
	masterFaculty = FileIO::ReadFacultyTree();

	//cout << "Master Student tree: " << masterStudent << endl;
	//cout << "Is master student null?: " << (masterStudent == NULL) << endl;

	//cout << "(From Constructor) Printing student tree straight from file:\n";
	//cout << "Number of nodes in student tree: " << masterStudent->numNodes << endl;
	//masterStudent->printTree();
	cout << endl;
}

DataBaseManager::~DataBaseManager()
{
	try
	{
		FileIO::WriteFacultyTree(masterFaculty);
	}
	catch (BSTCouldNotOpenFileException e)
	{
		cout << "Failed writing faculty tree to file." << endl;
		cout << e.what() << endl;
	}
	
	try
	{
		FileIO::WriteStudentTree(masterStudent);
	}
	catch (BSTCouldNotOpenFileException e)
	{
		cout << "Failed writing student tree to file." << endl;
		cout << e.what() << endl;
	}
}

//prints the whole student tree
void DataBaseManager::printAllStudents()
{
	try
	{
		masterStudent->printTree();
	}
	catch (TreeEmptyException e)
	{
		cout << "The student tree is empty." << endl;
	}
	
}

//prints the whole faculty tree
void DataBaseManager::printAllFaculty()
{
	try
	{
		masterFaculty->printTree();
	}
	catch (TreeEmptyException e)
	{
		cout << "The faculty tree is empty." << endl;
	}
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
	Student* student;
	try
	{
		//get the student we are talking about
		 student = masterStudent->getNode(id);
		//return that student's advisor
		
		 //if that student's advisor id is -1, it has no adivsor
		 if (student->getAdvisorId() == -1)
			 throw StudentHasNoAdvisorException("Student by id of " + to_string(id) + " has no advisor.");

	}
	catch (NodeNotFoundException e)
	{
		throw StudentDoesntExistException("Student by the ID of " + to_string(id) + " doesn't exit.");
	}

	try
	{
		return masterFaculty->getNode(student->getAdvisorId());
	}
	catch (NodeNotFoundException e)
	{
		throw FacultyDoesntExistException("Faculty member by the ID of " + to_string(student->advisor) + " doesnt exist.");
	}
	
}

//takes in a faculty id and prints all of the students
void DataBaseManager::printAdvisees(int id)
{
	Faculty* faculty;
	try
	{
		faculty = masterFaculty->getNode(id);
	}
	catch (NodeNotFoundException e)
	{
		throw FacultyDoesntExistException("The faculty member by the id of " + to_string(id) + " doesnt exist.");
	}

	int* adviseeArray = faculty->getAdvisees()->toArray();


	for (int i = 0; i <= faculty->getAdvisees()->getSize(); ++i)
	{
		cout << *(masterStudent->getNode(adviseeArray[i])) << endl;
	}
}

//given a student, add them to the list and add their id to the provided advisor
void DataBaseManager::addStudent(Student* student)
{
	
	//if the given student has an advisor id of -1, it doesnt have an advisor
	if (student->getAdvisorId() != -1)
	{
		//now add that student's id to the provided advisors list

		Faculty* faculty;

		try
		{
			faculty = masterFaculty->getNode(student->getAdvisorId());

		}
		catch (NodeNotFoundException e)
		{
			cout << "The advisor id given with that student doesnt exist. \nPlease ensure that faculty member is in the database." << endl;
			cout << "Failed to add student to database." << endl;
			return;
		}

		faculty->addAdvisee(student->getId());
	}
	

	//if the provided advisor id exists, add that student to the tree
	masterStudent->insert(student->getId(), student);
}

void DataBaseManager::addFaculty(Faculty* faculty)
{
	masterFaculty->insert(faculty->getId(), faculty);
}

bool DataBaseManager::deleteFaculty(int id)
{
	Faculty* faculty = masterFaculty->getNode(id);
	//if that faculty member has advisees, then remove that advisor id from that student
	if (faculty->getAdvisees()->isEmpty() == false)
	{
		int* advisees = faculty->getAdvisees()->toArray();
		//iterate through the advisee array setting all the student's advisor ids to -1
		for (int i = 0; i < faculty->getAdvisees()->getSize() + 1; ++i)
		{
			changeStudentsAdvisor(advisees[i], -1);
		}
	}

	return masterFaculty->deleteNode(id);
}

bool DataBaseManager::deleteStudent(int id)
{
	try
	{
		return masterStudent->deleteNode(id);
	}
	catch (TreeEmptyException e)
	{
		cout << "The tree is empty. Can\'t delete the student with id " + id << endl;
	}
}

bool DataBaseManager::changeStudentsAdvisor(int studentId, int facultyId)
{

	Faculty* newAdvisor;
	Faculty* oldAdvisor;
	Student* student;

	//grab the student
	try
	{
		student = masterStudent->getNode(studentId);
	}
	catch (NodeNotFoundException e)
	{
		throw StudentDoesntExistException("The given student id does not exist in the tree");
	}

	//if the current advisor's id is the same as the new advisor id, then return true
	//this means that the students current advisor is already the given advisor id
	if (student->getAdvisorId() == facultyId)
		return true;

	if (facultyId != -1)
	{
		//grab the new advisor
		try
		{
			//grab the new advisor
			newAdvisor = masterFaculty->getNode(facultyId);
		}
		catch (NodeNotFoundException e)
		{
			throw FacultyDoesntExistException("The given faculty id does not exist in the tree.");
		}

		newAdvisor->addAdvisee(studentId);
	}
	
	
	//if it makes it here, everything checks out.

	oldAdvisor = masterFaculty->getNode(student->getAdvisorId());
	oldAdvisor->removeAdvisee(studentId);

	

	student->setAdvisorId(facultyId);

	return true;
}

bool DataBaseManager::removeAdviseeFromFaculty(int studentId, int facultyId)
{

	//Faculty* newAdvisor;
	Faculty* oldAdvisor;
	Student* student;

	//grab the student
	try
	{
		student = masterStudent->getNode(studentId);
	}
	catch (NodeNotFoundException e)
	{
		throw StudentDoesntExistException("The given student id does not exist in the tree");
	}

	//if the current advisor's id is the same as the new advisor id, then return true
	//this means that the students current advisor is already the given advisor id
	if (student->getAdvisorId() == facultyId)
		return true;

	//if it makes it here, everything checks out.

	oldAdvisor = masterFaculty->getNode(facultyId);
	oldAdvisor->removeAdvisee(studentId);

	student->setAdvisorId(-1);

	return true;
}




//additional functions
//Student* DataBaseManager::getStudent(int id)
//{
//	return masterStudent->getNode(id);
//}