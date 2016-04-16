/*
Author: SHhuheng Li
Date: 04/15/2016
*/

#include <iostream>
#include <string.h>
#include "tree.h"

using namespace std;


Tree::Tree()
{
	root = NULL;
	return;
}

Tree::~Tree()
{
	ClearTree(root);
	return;
}


void Tree::ClearTree(TreeNode *T)
{
	if (T == NULL) return;  // Nothing to clear
	if (T->left != NULL) ClearTree(T->left); // Clear left sub-tree
	if (T->right != NULL) ClearTree(T->right); // Clear right sub-tree
	delete T;    // Destroy this node
	return;
}

int Tree::Insert(int Key)
{
	TreeNode *newNode;

	// Create the new node and copy data into it
	newNode = new TreeNode();
	newNode->Key = Key;
	newNode->data = 0;
	newNode->left = newNode->right = NULL;

	// Call other Insert() to do the actual insertion
	return(Insert(newNode));
}

int Tree::Insert(TreeNode *newNode)
{
	TreeNode *temp;

	temp = root;
	if (temp == NULL) {
		root = newNode;
		newNode->data = 1;
		return true;
	}
	if (target->left == NULL) {
		target->left = newNode;
		return true;
	}
	if (target->right == NULL) {
		target->right = newNode;
		return true;
	}
	return 0;

}

bool Tree::find(int i) {
	TreeNode *temp = root;
	return preorder(i, temp);
}

bool Tree::preorder(int i, TreeNode* T) {
	if (T == NULL) return false;
	if (T->Key == i) {
		target = T;
		return true;
	}

	return preorder(i, T->left) || preorder(i, T->right);
}


void Tree::PrintOne(TreeNode *T)
{
	cout << "id: " << T->Key << "  val: " << T->data << endl;
}


void Tree::PrintAll(TreeNode *T)
{
	if (T != NULL)
	{
		PrintOne(T);
		PrintAll(T->left);
		PrintAll(T->right);
	}
}


void Tree::PrintTree()
{
	PrintAll(root);
}

void Tree::Add(int val)
{
	TreeNode *temp = target;
	Add_T(val, temp);
}

void Tree::Add_T(int val, TreeNode *r)
{
	if (r == NULL) return;
	r->data += val;
	Add_T(val, r->left);
	Add_T(val, r->right);
}

vector<int> Tree::Path(int id)
{
	p.clear();
	vector<int> res;
	TreeNode *temp = root;
	Path_T(id, temp, res);
	return p;
}

void Tree::Path_T(int val, TreeNode *r, vector<int> &res)

{	
	res.push_back(r->Key);
	if (r->Key == val) {
		p = res;
		return;
	}

	if(r->left!=NULL)Path_T(val, r->left, res);
	if (r->right != NULL)Path_T(val, r->right, res);
	res.pop_back();
}

int Tree::getData(int id)
{
	find(id);
	return target->data;
}

void Tree::SetNodes(int num) {
	nodes.resize(num);
}