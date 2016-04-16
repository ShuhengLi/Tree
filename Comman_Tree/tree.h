/*
Author: SHhuheng Li
Date: 04/15/2016
*/


#pragma once
#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
using namespace std;

// Define a structure to be used as the tree node
struct TreeNode
{
	int      Key;
	int		data;
	vector<TreeNode*> children;
};

class Tree
{
private:
	TreeNode *root;
	TreeNode *target;//target node
	vector<int> p;//save path
	vector<TreeNode*> nodes;
public:
	Tree();
	~Tree();
	vector<int> Path(int);
	int Insert(int Key);
	void SetNodes(int);
	void Add(int);
	void PrintOne(TreeNode *T);
	void PrintTree();
	bool find(int);
	bool preorder(int, TreeNode *T);
	int getData(int);
	void AddEdge(int, int);
	void ShowV();
private:
	void ClearTree(TreeNode *T);
	void PrintAll(TreeNode *T);
	void Add_T(int, TreeNode *T);
	void Path_T(int, TreeNode *T, vector<int> &res);
	void remove_edge(TreeNode* cur);
};

#endif