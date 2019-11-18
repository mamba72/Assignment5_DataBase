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

#include<string>

#include<fstream>
using namespace std;

int getUserChoice();
Student* GatherStudentInfoFromUser();
Faculty* GatherFacultyInfoFromUser();

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

	//add some sample student and faculty objects because reading from file is broken
	Faculty* rene = new Faculty(23, "Rene German", "Professor", "Computer Science");
	db->addFaculty(rene);
	cout << "Added faculty\n";

	Student* studentTest = new Student(16, "Stephen White2", "Sophomore", "Compsci", 3.7, 23);
	db->addStudent(studentTest);




	int choice = -1;

	//while the user didnt choose 14 ( because 14 is the exit option)
	while (choice != 14)
	{
		choice = getUserChoice();

		switch (choice)
		{
		case 1://print all students
			db->printAllStudents();
			break;
		case 2://print all faculty
			db->printAllFaculty();
			break;
		case 3://find student based off ID
		{
			string response = "";
			cout << "Enter the id of the student you\'d like to find:" << endl;
			cin >> response;
			try
			{
				int id = stoi(response);
				cout << *(db->findStudent(id));
			}
			catch (invalid_argument e)
			{
				cout << "That was not a valid id. Please ensure it is an integer." << endl;
			}
			catch (StudentDoesntExistException e)
			{
				cout << e.what() << endl;
			}
			break;
		}
		case 4://find faculty by id
		{
			string response = "";
			cout << "Enter the id of the faculty member you\'d like to find:" << endl;
			cin >> response;
			try
			{
				int id = stoi(response);
				cout << *(db->findFaculty(id));
			}
			catch (invalid_argument e)
			{
				cout << "That was not a valid id. Please ensure it is an integer." << endl;
			}
			catch (FacultyDoesntExistException e)
			{
				cout << e.what() << endl;
			}

			break;
		}
		case 5://given student id print their advisor
		{
			string response = "";
			cout << "Please enter the id of the student:" << endl;
			cin >> response;

			try
			{
				int id = stoi(response);
				Faculty* advisor = db->getStudentsAdvisor(id);
				cout << *advisor;

				delete advisor;
			}
			catch (invalid_argument e)
			{
				cout << "That was not a valid id. Please ensure that it\'s an integer." << endl;
			}
			catch (TreeEmptyException e)
			{
				cout << "The faculty tree is empty." << endl;
			}
			catch (StudentDoesntExistException e)
			{
				cout << e.what() << endl;
			}
			catch (FacultyDoesntExistException e)
			{
				cout << e.what() << endl;
			}
			
			break;
		}
		case 6://given a faculty member's id, print all their students
		{
			string response;
			cout << "Enter the faculty member\'s id: " << endl;
			cin >> response;

			try
			{
				int id = stoi(response);
				db->printAdvisees(id);
			}
			catch (invalid_argument e)
			{
				cout << "Please enter a valid id. Ensure that it is an integer." << endl;
			}
			break;
		}
		case 7://add a new student
		{
			Student* newStudent = GatherStudentInfoFromUser();
			db->addStudent(newStudent);
			break;
		}
		case 8://delete a student given id
		{
			string response;
			cout << "Enter the id of the student you\'d like to delete:" << endl;
			cin >> response;

			try
			{
				int id = stoi(response);
				db->deleteStudent(id);
			}
			catch (invalid_argument e)
			{
				cout << "Please enter a valid id. It must be an integer." << endl;
			}
			break;
		}
		case 9://add faculty member
		{
			Faculty* newFaculty = GatherFacultyInfoFromUser();
			db->addFaculty(newFaculty);
			break;
		}
		case 10://delete faculty member given id
		{
			string response;
			cout << "Enter the id of the faculty member you\'d like to delete:" << endl;
			cin >> response;

			try
			{
				int id = stoi(response);
				db->deleteFaculty(id);
			}
			catch (invalid_argument e)
			{
				cout << "Please enter a valid id. It must be an integer." << endl;
			}
			break;
		}
		case 11://change students advisor given student id and new faculty id
			break;
		case 12://remove an advisee from a faculty member given the ids
			break;
		case 13://rollback
			break;
		case 14://if they chose exit
			break;
		}

		//print a new line just to make it easier to read
		cout << endl;
	}
	


	cout << "Thanks for using this data base manager!" << endl;
	cout << "Goobye :)" << endl;

	delete db;


	return 0;
}


void ProperTesting(DataBaseManager* db)
{
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
	cout << "Advisor: " << *advisor << endl;

	cout << *(db->masterStudent->getNode(16)) << endl;

	cout << "Printed Students\n";

	cout << "number of nodes: " << db->masterStudent->numNodes << endl;

}


//this function will gather all the info to create a student, create that student, and return a pointer to it
Student* GatherStudentInfoFromUser()
{
	string response = "";
	int id;
	string name;
	string level;
	string major;
	double gpa;
	int advisorId;

	cout << "Enter the ID of the student:" << endl;
	cin >> response;

	id = stoi(response);

	cout << "Enter the first and last name of the student:" << endl;
	cin >> name;
	getline(cin, name);

	cout << "Enter the year (or level) in words of your student: " << endl;
	cin >> level;

	cout << "Enter the student\'s major:" << endl;
	cin >> major;
	getline(cin, major);
	
	cout << "Enter the student\'s gpa: " << endl;
	cin >> response;
	gpa = stod(response);

	cout << "Enter the student\'s advisor id:" << endl;
	cin >> response;
	advisorId = stoi(response);

	return new Student(id, name, level, major, gpa, advisorId);
}


//this function will gather all the info to create a student, create that student, and return a pointer to it
Faculty* GatherFacultyInfoFromUser()
{
	string response = "";
	int id;
	string name;
	string level;
	string major;
	//double gpa;
	//int advisorId;

	cout << "Enter the ID of the faculty member:" << endl;
	getline(cin,response);

	id = stoi(response);

	cout << "Enter the first and last name of the faculty member:" << endl;
	//cin >> response;
	getline(cin, response);

	name = response;

	cout << "Enter the title of the faculty member: " << endl;
	getline(cin,level);

	cout << "Enter the faculty member\'s department:" << endl;
	//cin >> major;
	getline(cin, major);

	return new Faculty(id, name, level, major);
}


int getUserChoice()
{
	int choice = -1;
	while (true)
	{
		cout << "To select an option, enter the number of your choice.\nYour options are as follows:" << endl;

		cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
		cout <<	"2. Print all faculty and their information (sorted by ascending id #)" << endl;
		cout << "3. Find and display student information given the students id" << endl;
		cout << "4. Find and display faculty information given the faculty id" << endl;
		cout << "5. Given a student\'s id, print the name and info of their faculty advisor " << endl;
		cout << "6. Given a faculty id, print ALL the names and info of his/her advisees. " << endl;
		cout << "7. Add a new student " << endl;
		cout << "8. Delete a student given the id " << endl;
		cout << "9. Add a new faculty member " << endl;
		cout << "10. Delete a faculty member given the id. " << endl;
		cout << "11. Change a student\'s advisor given the student id and the new faculty id. " << endl;
		cout << "12. Remove an advisee from a faculty member given the ids " << endl;
		cout << "13. Rollback " << endl;
		cout << "14. Exit " << endl;
		string response;
		cin >> response;

		try
		{
			choice = stoi(response);

			if (choice < 1 || choice > 14)
				throw invalid_argument("");
			else
				break;
		}
		catch (invalid_argument e)
		{
			cout << "\n**That was not a valid option. Please try again.**" << endl;
			continue;
		}

	}
	

	return choice;
}