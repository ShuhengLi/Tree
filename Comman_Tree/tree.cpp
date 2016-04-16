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
	for (int i = 0; i < T->children.size(); i++) {
		ClearTree(T->children[i]);
		delete T;
	}
	delete T;    // Destroy this node
	return;
}


int Tree::Insert(int i)
{
	TreeNode *cur = nodes[i - 1];
	target->children.push_back(cur);

	//cur doesn't have a edge to any nodes;
	if (cur->children.empty()) return true;

	//cur has a edge to a node, need to remove this edge;
	else {
		remove_edge(cur);
	}

	return true;
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
	bool res = 0;
	for (auto it = T->children.begin(); it != T->children.end(); it++) {
		res = res || preorder(i, *it);
	}

	return  res;
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
		for (int i = 0; i < T->children.size(); i++) {
			PrintAll(T->children[i]);
		}
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

void Tree::Add_T(int val, TreeNode *T)
{
	if (T == NULL) return;
	T->data += val;
	/*
	for (int i = 0; i < T->children.size(); i++) {
	Add_T(val, T->children[i]);
	}
	*/
	for (auto it = T->children.begin(); it != T->children.end(); it++) {
		Add_T(val, *it);
	}
}

//find a path from root to target node and save it in private: vector<int> p;
vector<int> Tree::Path(int id)
{
	p.clear();
	vector<int> res;
	TreeNode *temp = root;
	Path_T(id, temp, res);
	return p;
}

void Tree::Path_T(int val, TreeNode *T, vector<int> &res)

{
	res.push_back(T->Key);
	if (T->Key == val) {
		p = res;
		return;
	}
	for (int i = 0; i < T->children.size(); i++) {
		Path_T(val, T->children[i], res);
	}
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
		newNode->data = 0;
		vector<TreeNode*> nodeNew;
		newNode->children = nodeNew;

		if (i == 0) 		root = newNode;
		nodes[i] = newNode;
	}

}

void Tree::remove_edge(TreeNode* cur) {
	if (cur->children.size() == 0) return;


	for (auto i = cur->children.begin(); i < cur->children.end(); i++) {
		TreeNode* next = *i;
		for (auto it = next->children.begin(); it != next->children.end();)
		{
			if (*it == cur) {
				next->children.erase(it);
				break;
			}
			else
				it++;
		}
		remove_edge(next);
	}
	return;
}

void Tree::AddEdge(int a, int b) {
	TreeNode *t1 = nodes[a - 1];
	TreeNode *t2 = nodes[b - 1];

	t1->children.push_back(t2);
	t2->children.push_back(t1);
}

void Tree::ShowV() {
	cout << "the size of the vector is " << nodes.size() << endl;
	for (int i = 0; i < nodes.size(); i++) {
		cout << "the node KEY is " << nodes[i]->Key << "the data is  :" << nodes[i]->data << endl;
	}
	int a;
}