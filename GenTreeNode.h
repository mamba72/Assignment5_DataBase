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

template <class T, class DType>
class GenTreeNode
{
public:
	GenTreeNode();
	GenTreeNode(T k, DType d); // k = key, which in this exmaple is also the value (data)
	virtual ~GenTreeNode(); //when creating a template class destrcutor must be virtual

	T key;
	DType data;
	GenTreeNode<T, DType>* left;
	GenTreeNode<T, DType>* right;
};

template<class T, class DType>
GenTreeNode<T, DType>::GenTreeNode()
{
	key = NULL;
	data = NULL;
	left = NULL;
	right = NULL;
}

template<class T, class DType>
GenTreeNode<T, DType>::GenTreeNode(T k, DType d)
{
	key = k;
	data = d;
	left = NULL;
	right = NULL;
}

template<class T, class DType>
GenTreeNode<T, DType>::~GenTreeNode()
{
	//we should research this
}