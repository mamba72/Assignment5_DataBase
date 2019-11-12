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

template <class T, class D>
class GenBST
{
private:
	GenTreeNode<T, D>* root; //pointer to root
	GenTreeNode<T, D>* getSuccessor(GenTreeNode<T, D>* curr);

public:
	GenBST();
	~GenBST();

	bool contains(D value); //value is also the key in this situation. this will return whether we have it. Should change this to return the value?
	void insert(T key, D data);

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


};

template<class T, class D>
GenBST<T, D>::GenBST()
{
	root = NULL; //empty tree
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
}

//delete the node with the given key
template<class T, class D>
bool GenBST<T, D>::deleteNode(D value)
{
	//if its empty, then you cant delete anything. so return false
	if (root == NULL)
		return false;

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
	return true;
}


//delete the node with the given key
template<class T, class D>
bool GenBST<T, D>::deleteNode(T key)
{
	//if its empty, then you cant delete anything. so return false
	if (root == NULL)
		return false;

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
		return NULL;

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
		return NULL;

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
	recPrint(root);
}

template<class T, class D>
void GenBST<T, D>::recPrint(GenTreeNode<T, D>* node)
{
	if (node == NULL)
		return;

	recPrint(node->left);
	cout << node->key << "\t" << node->data << endl;
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