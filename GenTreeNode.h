/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 5
*/
#pragma once
#include <iostream>

using namespace std;

template <class T>
class GenTreeNode
{
public:
	GenTreeNode();
	GenTreeNode(T k); // k = key, which in this exmaple is also the value (data)
	virtual ~GenTreeNode(); //when creating a template class destrcutor must be virtual

	T key;
	GenTreeNode<T>* left;
	GenTreeNode<T>* right;
};

template<class T>
inline GenTreeNode<T>::GenTreeNode()
{
	key = NULL;
	left = NULL;
	right = NULL;
}

template<class T>
inline GenTreeNode<T>::GenTreeNode(T k)
{
	key = k;
	left = NULL;
	right = NULL;
}

template<class T>
inline GenTreeNode<T>::~GenTreeNode()
{
	//we should research this
}