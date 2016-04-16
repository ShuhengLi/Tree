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


int Tree::Insert(int i)
{
	TreeNode *cur = nodes[i - 1];
	if (target->left == NULL) {
		target->left = cur;
	}
	else if (target->right == NULL) {
		target->right = nodes[i - 1];
	}

	//cur doesn't have a edge to any nodes;
	if (cur->left == NULL && cur->right == NULL) return true;

	//cur has a edge to a node, need to remove this edge;
	if (cur->left != NULL || cur->right != NULL) {
		remove_edge(cur);
	}

	return true;
}
/*
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
*/

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

	if (r->left != NULL)Path_T(val, r->left, res);
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

	// Create the new node and copy data into it

	for (int i = 0; i < num; i++) {
		TreeNode* newNode = new TreeNode();
		newNode->Key = i + 1;
		newNode->data = i == 0 ? 1 : 0;
		newNode->left = newNode->right = NULL;

		if (i == 0) 		root = newNode;
		nodes[i] = newNode;
	}

}

void Tree::remove_edge(TreeNode* cur) {
	if (cur->left == NULL && cur->right == NULL) return;

	if (cur->left != NULL || cur->right != NULL) {
		//if there is a edge between two node, remove one;
		if (cur->left != NULL) {
			TreeNode *next = cur->left;
			if (next->left == cur) next->left = NULL;
			if (next->right == cur) next->right = NULL;
			remove_edge(next);
		}
		if (cur->right != NULL) {
			TreeNode *next = cur->right;
			if (next->left == cur) next->left = NULL;
			if (next->right == cur) next->right = NULL;
			remove_edge(next);
		}

	}
	return;
}

void Tree::AddEdge(int a, int b) {
	TreeNode *t1 = nodes[a - 1];
	TreeNode *t2 = nodes[b - 1];

	if (t1->left == NULL) t1->left = t2;
	else {
		t1->right = t2;
	}

	if (t2->left == NULL) t2->left = t1;
	else {
		t2->right = t1;
	}
}

void Tree::ShowV() {
	cout << "the size of the vector is " << nodes.size() << endl;
	for (int i = 0; i < nodes.size(); i++) {
		cout << "the node KEY is " << nodes[i]->Key << "the data is  :" << nodes[i]->data << endl;
	}
	int a;
}