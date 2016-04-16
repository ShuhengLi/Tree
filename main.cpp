#include<iostream>
#include<fstream>
#include<stdlib.h>
#include"tree.cpp"
#include<vector>
#include<string>

vector<int> t_max(string t);
vector<int> t_add(string t);
void write_f();
void read_f();
void display_f();

vector<int> fout;
vector<string> fin;

using namespace std;
int main() {

	read_f();
//	display_f();

	int n = fin.size();
	if (n < 1) cout << " Input file is invalid" << endl;
//----------------------Get N----------------------------------------------
	int N = stoi(fin[0]);
	if (N < 1) cout << "N is too small" << endl;
	if (N > 100000) cout << "N is too large" << endl;

	Tree    *theTree = new Tree();
	theTree->Insert(1);


//---------------------------Build Tree-------------------------------------
	for (int i = 1; i < N; i++) {
		int x, y;
		string temp = fin[i];
		int temp_size = temp.size();
		for (int j = 0; j < temp_size; j++) {
//			theTree->PrintTree();
			cout << endl;
			if (fin[i][j] == ' ') {
				x = stoi(temp.substr(0, j));
				y = stoi(temp.substr(j + 1));

				//x is in the tree;
				if (theTree->find(x)) {
					theTree->Insert(y);
				}

				//y is the tree;
				if (theTree->find(y)) {
					theTree->Insert(x);
				}

				break;
			}
		}
	}

//-------------------------------Get Q-----------------------
	int Q = stoi(fin[N]);
	if (Q < 1) cout << "Q is too small" << endl;
	if (Q > 100000) cout << "Q is too large" << endl;

	theTree->PrintTree();
//-------------------------------Compute Tree----------------------------------
	for (int i = N+1; i < fin.size(); i++) {
		string temp = fin[i];
		int temp_size = temp.size();

		cout << endl;
		for (int j = 0; j < temp_size; j++) {
			//deal with add
			if (temp.substr(0, 3) == "add") {
				vector<int> vdata = t_add(temp.substr(4));
//				cout << "node number :" << vdata[0] << "  going to ADD:" << vdata[1] << endl;
				if (theTree->find(vdata[0])) {
					theTree->Add(vdata[1]);
				}
//				theTree->PrintTree();

				break;
			}
			//deal with max
			else if (temp.substr(0, 3) == "max") {
				vector<int> vdata = t_max(temp.substr(4));

				vector<int> path1 = theTree->Path(vdata[0]);
				vector<int> path2 = theTree->Path(vdata[1]);
				
				int l1 = path1.size(),l2 = path2.size();
				cout << "path1:  ";
				for (int k = 0; k < l1; k++) {
							cout << " " << path1[k] << "  ";
				}
				cout << "path2:  ";


				for (int k = 0; k < l2; k++) {
					cout << " " << path2[k] << "  ";
				}
				
				if (l2 > l1) { 
					swap(path1, path2);
					swap(l1, l2); 
				}

				int max = INT_MIN;
				//two nodes are in one path
				if (path2[l2 - 1] == path1[l2 - 1]) {
					cout << endl << "two nodes are in one path" << endl;
					for (int i = l2 - 1; i < l1; i++) {
						int tem = theTree->getData(path1[i]);
						if (tem > max) max = tem;
					}
				}
				//two nodes are in different path
				else {
					cout << endl << "two nodes are in different path" << endl;
					for (int i = 0; i < l1; i++) {
						int tem = theTree->getData(path1[i]);
						if (tem > max) max = tem;
					}
					for (int i = 0; i < l2; i++) {
						int tem = theTree->getData(path2[i]);
						if (tem > max) max = tem;
					}

				}
				cout << "max is" << max << endl;
				fout.push_back(max);
				write_f();
				break;

			}
		}
	}

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

void write_f() {
	ofstream out("e:\\output.txt");
	if (out.is_open())
	{
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
	string stmp;
	while (getline(ifs, stmp)) {
		fin.push_back(stmp);
	}
	ifs.close();
}

void display_f() {
	//----------------------test input to vector value--------------------

	for (int i = 0; i < fin.size(); i++) {
	for (int j = 0; j < fin[i].size(); j++) {
	cout << fin[i][j] ;
	}
	cout << endl;
	}
}