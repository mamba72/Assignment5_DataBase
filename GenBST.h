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

using namespace std;


/*
NOTE: the "inline" at the beginning of functions was created by visual studio's autocreate functions.
Not entirely sure what it does
*/

template <class T>
class GenBST
{
private:
	GenTreeNode<T>* root; //pointer to root
	GenTreeNode<T>* getSuccessor(GenTreeNode<T>* curr);

public:
	GenBST();
	~GenBST();

	bool search(T value); //value is also the key in this situation. this will return whether we have it. Should change this to return the value?
	void insert(T value);

	//delete placeholder
	bool deleteNode(T value);

	//helper functions:
	bool isEmpty();
	GenTreeNode<T>* getMin();
	GenTreeNode<T>* getMax();
	void printTree();
	void recPrint(GenTreeNode<T>* node);



};

template<class T>
GenBST<T>::GenBST()
{
	root = NULL; //empty tree
}

template<class T>
GenBST<T>::~GenBST()
{
	//we need to research this
}

//pretty much equivalent to a contains function
template<class T>
bool GenBST<T>::search(T value)
{
	if (root == NULL)//empty tree, so it cant be there.
		return false;
	else//tree is not empty, find value
	{
		GenTreeNode<T>* curr = root;

		while (curr->key != value) //while we havent found it, keep searching
		{
			if (value < curr->key)
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

template<class T>
void GenBST<T>::insert(T value)
{
	GenTreeNode<T>* node = new GenTreeNode<T>(value);

	if (root == NULL)//empty tree
	{
		root = node;
	}
	else//tree is not empty, so we need to find the location to insert
	{
		GenTreeNode<T>* curr = root;
		GenTreeNode<T>* parent = NULL;

		while (curr != NULL)//could also do while true
		{
			//update parent
			parent = curr;

			//if the value is less than the current node, go left
			if (value < curr->key)
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
}

//delete the node with the given key
template<class T>
bool GenBST<T>::deleteNode(T value)
{
	//if its empty, then you cant delete anything. so return false
	if (root == NULL)
		return false;

	GenTreeNode<T>* curr = root;
	GenTreeNode<T>* parent = root;
	bool isLeft = true;//determine if the current node is left or right child

	//now look for the node.
	while (curr->key != value) //while we havent found it, keep searching
	{
		parent = curr;

		if (value < curr->key)
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
		GenTreeNode<T>* successor = getSuccessor(curr);

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
	return true;
}

//private helper method
template <class T>
GenTreeNode<T>* GenBST<T>::getSuccessor(GenTreeNode<T>* d)
{
	//go right one from current, then all the way down to the left
	//to get the lowest node greater than D
	GenTreeNode<T>* sp = d; //sp is successor's parent and is initialized to D
	GenTreeNode<T>* successor = d;
	GenTreeNode<T>* current = d->right;//start one to the right

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

template<class T>
GenTreeNode<T>* GenBST<T>::getMin()
{
	GenTreeNode<T>* current = root;

	if (current == NULL)//empty tree
		return NULL;

	while (current->left != NULL)
	{
		current = current->left;
	}

	return current;
}

template<class T>
GenTreeNode<T>* GenBST<T>::getMax()
{
	GenTreeNode<T>* current = root;

	if (current == NULL)//empty tree
		return NULL;

	while (current->right != NULL)
	{
		current = current->right;
	}

	return current;
}

//prints the 
template<class T>
void GenBST<T>::printTree()
{
	recPrint(root);
}

template<class T>
void GenBST<T>::recPrint(GenTreeNode<T>* node)
{
	if (node == NULL)
		return;

	recPrint(node->left);
	cout << node->key << endl;
	recPrint(node->right);
}

template<class T>
bool GenBST<T>::isEmpty()
{
	if (root == NULL)
		return true;
	else
		return false;
}