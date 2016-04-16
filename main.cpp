/*
Author: SHhuheng Li
Date: 04/15/2016
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include"tree.cpp"
#include<vector>
#include<string>
using namespace std;

vector<int> t_max(string t);
vector<int> t_add(string t);
vector<int> t_data(string t);
int getmax(vector<int> vdata, Tree *theTree);

void write_f();
void read_f();
void display_f();

vector<int> fout;
vector<string> fin;


int main() {
//-----------------------------Read File----------------------------------
	read_f();
//----------------------Get N----------------------------------------------
	int N = stoi(fin[0]);
	if (N < 1) cout << "N is too small" << endl;
	if (N > 100000) cout << "N is too large" << endl;
//-------------------------------Get Q-------------------------------------
	int Q = stoi(fin[N]);
	if (Q < 1) cout << "Q is too small" << endl;
	if (Q > 100000) cout << "Q is too large" << endl;
//---------------------------Build Tree-------------------------------------

	cout << "Prepare to build a Tree" << endl;
	Tree    *theTree = new Tree();
	theTree->SetNodes(N);


	for (int i = 1; i < N; i++) {
		int x, y;
		string temp = fin[i];
		vector<int> vdata = t_data(temp);
		x = vdata[0];
		y = vdata[1];
		//x is connect to the tree;
		if (theTree->find(x)) {
			theTree->Insert(y);
		}
		//y is connect to the tree;
		else if (theTree->find(y)) {
			theTree->Insert(x);
		}
		//none node connect to the tree;
		else {
			theTree->AddEdge(x, y);
		}
	}
	cout << "Complete building a Tree" << endl;
//	theTree->PrintTree();


//-------------------------------Compute Tree----------------------------------
	for (int i = N+1; i < fin.size(); i++) {
		string temp = fin[i];
		int temp_size = temp.size();

		//deal with add
		if (temp.substr(0, 3) == "add") {
		vector<int> vdata = t_add(temp.substr(4));
			if (theTree->find(vdata[0])) {
				theTree->Add(vdata[1]);
			}
		}

		//deal with max
		else if (temp.substr(0, 3) == "max") {
			vector<int> vdata = t_max(temp.substr(4));
			int max = getmax(vdata,theTree);
			fout.push_back(max);
		}
	}
//----------------------------------Write File------------------------------------	
	write_f();
	cout << "done" << endl;
	getchar();
	return 0;
}

vector<int> t_max(string t) {
	vector<int> res;
	int n, a;
	for (int j = 0; j < t.size(); j++) {

		if (t[j] == ' ') {
			n = stoi(t.substr(0, j));
			a = stoi(t.substr(j + 1));
			res.push_back(n);
			res.push_back(a);
			return res;
		}
	}
	
}

vector<int> t_add(string t) {
	vector<int> res;
	int n, b;
	for (int j = 0; j < t.size(); j++) {
		if (t[j] == ' ') {
			n = stoi(t.substr(0, j));
			b = stoi(t.substr(j + 1));
			res.push_back(n);
			res.push_back(b);
			return res;
		}
	}
}
vector<int> t_data(string t) {
	vector<int> res;
	int temp_size = t.size();

	for (int j = 0; j < temp_size; j++) {
		if (t[j] == ' ') {
			res.push_back(stoi(t.substr(0, j)));
			res.push_back(stoi(t.substr(j + 1)));
			return res;
		}
	}
}


void write_f(){
	ofstream out("e:\\output.txt");
	if (out.is_open())
	{
		cout << "Writing file..." << endl;
		for (int i = 0; i < fout.size(); i++) {
			out << fout[i];
		}
		out.close();
	}
}

void read_f() {
	ifstream ifs;
	ifs.open("e:\\input.txt");
	if (!ifs.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	fin.clear();
	cout << "Openning file..." << endl;
	string stmp;
	while (getline(ifs, stmp)) {
		fin.push_back(stmp);
	}
	ifs.close();
	int n = fin.size();
	if (n < 1) cout << " Input file is invalid" << endl;
}

void display_f() {
	for (int i = 0; i < fin.size(); i++) {
		for (int j = 0; j < fin[i].size(); j++) {
		cout << fin[i][j] ;
		}
		cout << endl;
	}
}


int getmax(vector<int> vdata,Tree *theTree) {
	vector<int> path1 = theTree->Path(vdata[0]);
	vector<int> path2 = theTree->Path(vdata[1]);
	int l1 = path1.size(), l2 = path2.size();
	if (l2 > l1) {
		swap(path1, path2);
		swap(l1, l2);
	}

	int max = INT_MIN;
	//two nodes are in one path, find max value from l2-1 to l1;
	if (path2[l2 - 1] == path1[l2 - 1]) {
		for (int i = l2 - 1; i < l1; i++) {
			int tem = theTree->getData(path1[i]);
			if (tem > max) max = tem;
		}
	}
	//two nodes are in different path,find max value from this two path;
	else {
		for (int i = 0; i < l1; i++) {
			int tem = theTree->getData(path1[i]);
			if (tem > max) max = tem;
		}
		for (int i = 0; i < l2; i++) {
			int tem = theTree->getData(path2[i]);
			if (tem > max) max = tem;
		}

	}
	return max;
	
}