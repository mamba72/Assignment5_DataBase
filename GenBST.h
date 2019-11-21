/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#pragma once
#include <iostream>
#include "GenTreeNode.h"
#include <fstream>

using namespace std;


/*
NOTE: the "inline" at the beginning of functions was created by visual studio's autocreate functions.
Not entirely sure what it does
*/

template <class T, class D>
class GenBST
{
private:
	
	const string MARKER = "\t\t";

	GenTreeNode<T, D>* getSuccessor(GenTreeNode<T, D>* curr);

	void serializeNode(GenTreeNode<T, D>* node, ofstream& file);
	void deserialize(string fileName);

public:

	GenTreeNode<T, D>* root; //pointer to root

	GenBST();
	GenBST(string fileName);
	~GenBST();

	bool contains(D value); //value is also the key in this situation. this will return whether we have it. Should change this to return the value?
	void insert(T key, D data);
	D getNode(T key);

	//delete placeholder
	bool deleteNode(D value);
	bool deleteNode(T key);

	//helper functions:
	bool isEmpty();
	GenTreeNode<T, D>* getMin();
	GenTreeNode<T, D>* getMax();
	void printTree();
	void recPrint(GenTreeNode<T, D>* node);
	GenTreeNode<T, D>* peek();

	//serialization functions
	void serialize(string fileName);


	//helper vars
	unsigned int numNodes;

};

struct TreeEmptyException : exception
{
	const char* what() const throw ()
	{
		return "This tree is empty, cannot remove.";
	}
};

struct NodeNotFoundException : exception
{
	const char* what() const throw ()
	{
		return "This node could not be found.";
	}
};

//exception to tell whether the file could be opened
#pragma once
class BSTCouldNotOpenFileException : public std::runtime_error
{
	//const char* msg;
public:
	BSTCouldNotOpenFileException(const char* msg) : std::runtime_error(msg)
	{
		//this->msg = msg;
	}

	BSTCouldNotOpenFileException(string msg) : std::runtime_error(msg.c_str())
	{
		//convert the string to a const char*
		//this->msg = msg.c_str();
	}
};

template<class T, class D>
GenBST<T, D>::GenBST()
{
	root = NULL; //empty tree
	numNodes = 0;
}

template<class T, class D>
GenBST<T, D>::GenBST(string fileName)
{
	GenBST();
	deserialize(fileName);
}

template<class T, class D>
GenBST<T, D>::~GenBST()
{
	//we need to research this
}

//pretty much equivalent to a contains function
template<class T, class D>
bool GenBST<T, D>::contains(D value)
{
	if (root == NULL)//empty tree, so it cant be there.
		return false;
	else//tree is not empty, find value
	{
		GenTreeNode<T, D>* curr = root;

		while (curr->data != value) //while we havent found it, keep searching
		{
			if (value < curr->data)
			{
				curr = curr->left;
			}
			else
			{
				curr = curr->right;
			}

			if (curr == NULL)//we didnt find the value, so return false
				return false;
		}
	}

	return true;
}

template<class T, class D>
void GenBST<T, D>::insert(T key, D data)
{
	GenTreeNode<T, D>* node = new GenTreeNode<T, D>(key, data);

	if (root == NULL)//empty tree
	{
		root = node;
	}
	else//tree is not empty, so we need to find the location to insert
	{
		GenTreeNode<T, D>* curr = root;
		GenTreeNode<T, D>* parent = NULL;

		while (curr != NULL)//could also do while true
		{
			//update parent
			parent = curr;

			//if the value is less than the current node, go left
			if (key < curr->key)
			{
				curr = curr->left;//going left
				if (curr == NULL)//we found the insertion point
				{
					parent->left = node;
					break;//break cause we inserted
				}
			}
			else//else go right (we cant be equal)
			{
				curr = curr->right;
				if (curr == NULL)//we found the insertion point
				{
					parent->right = node;
					break;//break cause we inserted
				}
			}
		}
	}
	//increment the number of nodes
	++numNodes;
}

//delete the node with the given key
template<class T, class D>
bool GenBST<T, D>::deleteNode(D value)
{
	//if its empty, then you cant delete anything. so return false
	if (root == NULL)
		throw TreeEmptyException();

	GenTreeNode<T, D>* curr = root;
	GenTreeNode<T, D>* parent = root;
	bool isLeft = true;//determine if the current node is left or right child

	//now look for the node.
	while (curr->data != value) //while we havent found it, keep searching
	{
		parent = curr;

		if (value < curr->data)
		{
			isLeft = true;
			curr = curr->left;
		}
		else
		{
			isLeft = false;
			curr = curr->right;
		}

		if (curr == NULL)//we didnt find the value, so return false
			return false;
	}
	//finished finding the node.
	//if we made it here, we found the node to delete

	//now check all the different cases

	//no children
	if (curr->left == NULL && curr->right == NULL) //means we have a leaf
	{
		if (curr == root)//the tree only has one entry
			root = NULL;
		else if (isLeft)
		{
			parent->left = NULL;
		}
		else
			parent->right = NULL;
	}

	//now check if its an exterior node (a node with only 1 child)
	//we need to determine if child is left or right, then proceed
	else if (curr->right == NULL)//has no right child
	{
		if (curr == root)
		{
			root = curr->left;
		}
		else if (isLeft)
		{
			parent->left = curr->left;
		}
		else
		{
			parent->right = curr->left;
		}
	}
	//pretty much the opposite of the previous else statement
	else if (curr->left == NULL)//has no left child
	{
		if (curr == root)
		{
			root = curr->right;
		}
		else if (isLeft)
		{
			parent->left = curr->right;
		}
		else
		{
			parent->right = curr->right;
		}
	}

	//the node to be deleted has two children
	else
	{
		GenTreeNode<T, D>* successor = getSuccessor(curr);

		if (curr == root)
		{
			root = successor;
		}
		else if (isLeft)
		{
			parent->left = successor;
		}
		else
		{
			parent->right = successor;
		}

		successor->left = curr->left;
	}
	//decrement the number of nodes
	--numNodes;
	return true;
}


//delete the node with the given key
template<class T, class D>
bool GenBST<T, D>::deleteNode(T key)
{
	//if its empty, then you cant delete anything. so return false
	if (root == NULL)
		throw TreeEmptyException();

	GenTreeNode<T, D>* curr = root;
	GenTreeNode<T, D>* parent = root;
	bool isLeft = true;//determine if the current node is left or right child

	//now look for the node.
	while (curr->key != key) //while we havent found it, keep searching
	{
		parent = curr;

		if (key < curr->key)
		{
			isLeft = true;
			curr = curr->left;
		}
		else
		{
			isLeft = false;
			curr = curr->right;
		}

		if (curr == NULL)//we didnt find the value, so return false
			return false;
	}
	//finished finding the node.
	//if we made it here, we found the node to delete

	//now check all the different cases

	//no children
	if (curr->left == NULL && curr->right == NULL) //means we have a leaf
	{
		if (curr == root)//the tree only has one entry
			root = NULL;
		else if (isLeft)
		{
			parent->left = NULL;
		}
		else
			parent->right = NULL;
	}

	//now check if its an exterior node (a node with only 1 child)
	//we need to determine if child is left or right, then proceed
	else if (curr->right == NULL)//has no right child
	{
		if (curr == root)
		{
			root = curr->left;
		}
		else if (isLeft)
		{
			parent->left = curr->left;
		}
		else
		{
			parent->right = curr->left;
		}
	}
	//pretty much the opposite of the previous else statement
	else if (curr->left == NULL)//has no left child
	{
		if (curr == root)
		{
			root = curr->right;
		}
		else if (isLeft)
		{
			parent->left = curr->right;
		}
		else
		{
			parent->right = curr->right;
		}
	}

	//the node to be deleted has two children
	else
	{
		GenTreeNode<T, D>* successor = getSuccessor(curr);

		if (curr == root)
		{
			root = successor;
		}
		else if (isLeft)
		{
			parent->left = successor;
		}
		else
		{
			parent->right = successor;
		}

		successor->left = curr->left;
	}
	//decrement the number of nodes
	--numNodes;
	return true;
}

//private helper method
template <class T, class D>
GenTreeNode<T, D>* GenBST<T, D>::getSuccessor(GenTreeNode<T, D>* d)
{
	//go right one from current, then all the way down to the left
	//to get the lowest node greater than D
	GenTreeNode<T, D>* sp = d; //sp is successor's parent and is initialized to D
	GenTreeNode<T, D>* successor = d;
	GenTreeNode<T, D>* current = d->right;//start one to the right

	while (current != NULL)//now take the one to the right and go all the way to the left
	{
		sp = successor;
		successor = current;
		current = current->left;
	}

	if (successor != d->right)
	{
		//determined that successor is descendant of right child
		sp->left = successor->right;
		successor->right = d->right;

	}

	return successor;
}

template<class T, class D>
GenTreeNode<T, D>* GenBST<T, D>::getMin()
{
	GenTreeNode<T, D>* current = root;

	if (current == NULL)//empty tree
		throw TreeEmptyException();

	while (current->left != NULL)
	{
		current = current->left;
	}

	return current;
}

template<class T, class D>
GenTreeNode<T, D>* GenBST<T, D>::getMax()
{
	GenTreeNode<T, D>* current = root;

	if (current == NULL)//empty tree
		throw TreeEmptyException();

	while (current->right != NULL)
	{
		current = current->right;
	}

	return current;
}

//prints the 
template<class T, class D>
void GenBST<T, D>::printTree()
{
	if (root == NULL)
		//cout << "NULL" << endl;
		throw TreeEmptyException();
	else
		recPrint(root);
}

template<class T, class D>
void GenBST<T, D>::recPrint(GenTreeNode<T, D>* node)
{
	if (node == NULL)
		return;

	recPrint(node->left);
	cout <<"Key: " << node->key << "\nValue: " << *(node->data) << endl;
	recPrint(node->right);
}

template<class T, class D>
bool GenBST<T, D>::isEmpty()
{
	if (root == NULL)
		return true;
	else
		return false;
}

//returns the root node
template<class T, class D>
inline GenTreeNode<T, D>* GenBST<T, D>::peek()
{
	return root;
}

template<class T, class D>
D GenBST<T, D>::getNode(T key)
{
	if (root == NULL)//empty tree, so it cant be there.
		throw TreeEmptyException();
	else//tree is not empty, find value
	{
		GenTreeNode<T, D>* curr = root;

		while (curr->key != key) //while we havent found it, keep searching
		{
			if (key < curr->key)
			{
				curr = curr->left;
			}
			else
			{
				curr = curr->right;
			}

			if (curr == NULL)//we didnt find the value, so return false
				throw NodeNotFoundException();
		}

		return curr->data;
	}
}

//returns the string of all the nodes
template<class T, class D>
void GenBST<T, D>::serialize(string fileName)
{
	ofstream file;
	//file.open(fileName, ios::app);
	file.open(fileName, ios::out);

	if (file.is_open() == false)
		throw BSTCouldNotOpenFileException("The file by the name of " + fileName + " could not be opened.");


	serializeNode(root, file);
	file.close();
}

template<class T, class D>
void GenBST<T, D>::serializeNode(GenTreeNode<T, D>* node, ofstream& file)
{
	if (node == NULL)
	{
		file << MARKER << endl;
		return;
	}
		

	serializeNode(node->left, file);
	file << node->key << endl;
	file << *(node->data) << endl;
	serializeNode(node->right, file);
}

template<class T, class D>
void GenBST<T, D>::deserialize(string fileName)
{
	ifstream file;
	file.open(fileName, ios::in);

	if (file.is_open() == false)
	{
		cout << "File is not open" << endl;
		throw BSTCouldNotOpenFileException("File by the name of " + fileName + " could not be opened.");
	}
	cout << "File is open" << endl;
	int counter = 0;
	//while the file still has lines, read in the objects
	while (file.eof() == false)
	{

		cout << "Entered while loop" << endl;

		T inKey;
		D* obj;

		cout << "Created objects" << endl;
		string keyStr;
		file >> keyStr;
		cout << "read in key" << endl;
		inKey = stoi(keyStr);
		file >> **obj;

		cout << "Printed to file" << endl;

		string emptySpacerLine;
		file >> emptySpacerLine;

		insert(inKey, *obj);

		cout << "Counter: " << counter << endl;
		++counter;

	}
}