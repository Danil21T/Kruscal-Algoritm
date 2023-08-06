#include "Kruscal.h"

int main() {
	string name;///<name of the file
	Graph G;
	cout << "Enter the file name: ";
	cin >> name;///enter the name of the received file
	try {
		G.ReadGraph(name);///reading a file
		G.Algoritm_Kruscal();///running the Kruskal algorithm
		cout << "Enter the name of the upload file: ";
		cin >> name;///entering the file to create
		G.Writting_file(name);///writing to the created file
	}
	catch (const exception& f) {
		cout << f.what() << endl;
	}
	return 0;
}