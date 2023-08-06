#pragma once
#include <iostream> 
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define edge pair<int,int>//< edge - пара чисел соответствующая номерам вершин

/*!

	\brief A class that performs graph traversal using the Kruskal algorithm.

*/
class Graph {
private:
	vector<pair<int, edge>> Graph_tree; ///< list of vertex pairs and the length of the edge between them
	vector<pair<int, edge>> Decision_tree; ///< final graph traversal according to Kruskal's algorithm
	int* parent = NULL; ///< array of parent elements
	int size = 0; ///< the maximum value of the peaks
public:
	/*!
		Class constructor
	*/
	Graph() {

		parent = NULL;
		size = 0;
		Graph_tree.clear();
		Decision_tree.clear();

	}

	/*!
		Class deconstructor

	*/
	~Graph()
	{
		delete[] parent;
		Graph_tree.clear();
		Decision_tree.clear();
	}

	/*!
		\brief The addition of the numbers in the adjacency list.
		\param u - first vertex
		\param v - second vertex
		\param w - path length.
		\return void
	*/
	void Add(int u, int v, int w) {

		Graph_tree.push_back(make_pair(w, edge(u, v)));

	}
	/*!
		\brief Search for a subset.
		\param i - variable being checked.

		This function checks whether the variable i is a parent of itself, if so, the value i is returned, otherwise the search continues recursively.

		\return The subset that it belongs to.


	*/

	int perent_search(int i) {
		if (i == parent[i])
			return i;
		else
			return perent_search(parent[i]);
	}

	/*!
		\param u - subset of the first vertex
		\param v - subset of the second vertex.
		\return void

		This function makes two vertices members of the same subset.


	*/

	void parent_set(int u, int v) {
		parent[u] = parent[v];
	}
	/*!
		\brief The Kruskal algorithm

		This function implements the Kruskal algorithm, which is used to find the minimum spanning tree.

		\code
		void Algoritm_Kruscal() {
		int i, top1, top2;
		sort(Graph_tree.begin(), Graph_tree.end());
		for (i = 0; i < Graph_tree.size(); i++) {
			top1 = perent_search(Graph_tree[i].second.first);
			top2 = perent_search(Graph_tree[i].second.second);
			if (top1 != top2) {
				Decision_tree.push_back(Graph_tree[i]);
				parent_set(top1, top2);
			}
		}
	}
		\endcode
	*/

	void Algoritm_Kruscal() {
		int i, top1, top2;
		sort(Graph_tree.begin(), Graph_tree.end());
		for (i = 0; i < Graph_tree.size(); i++) {
			top1 = perent_search(Graph_tree[i].second.first);
			top2 = perent_search(Graph_tree[i].second.second);
			if (top1 != top2) {
				Decision_tree.push_back(Graph_tree[i]);
				parent_set(top1, top2);
			}
		}
	}


	/*!
		\brief Recording the result.
		\param name - File name.
		\return void

		This function writes the result of graph traversal to a text file with GraphViz support.

	*/

	void Writting_file(string name) {
		ofstream fout;
		fout.open(name);
		fout << "digraph Graph{" << endl << "edge[weight=2, arrowhead=none];" << endl;
		for (int j = 0; j < Graph_tree.size(); j++) {
			int z = 0;
			for (int i = 0; i < Decision_tree.size(); i++) {
				if (Graph_tree[j].first == Decision_tree[i].first && Graph_tree[j].second.first == Decision_tree[i].second.first && Graph_tree[j].second.second == Decision_tree[i].second.second) {
					z = 1;
					fout << Decision_tree[i].second.first << " -> " << Decision_tree[i].second.second << "[label = \"" << Decision_tree[i].first << "\", color = green ];" << endl;
				}
			}
			if (z == 0) {
				fout << Graph_tree[j].second.first << " -> " << Graph_tree[j].second.second << "[label= \"" << Graph_tree[j].first << "\"];" << endl;
			}
		}
		fout << "}";
		fout.close();
	}

	/*!
		\brief Reading the graph.
		\param name - File name.

		this function reads an adjacent list from a text file and writes the result to a variable G.



	*/
	void ReadGraph(string name) {
		char ch;
		int y = 0, h = 0;
		ifstream fin;
		fin.exceptions(ifstream::badbit | ifstream::failbit);
		fin.open(name);
		while (fin.get(ch)) {
			if (strchr("0123456789", ch) != NULL) {
				y = 1;
			}
			else { y = 0; h = 0; }
			if (ch == '\n') {
				break;
			}
			if (y == 1 && h == 0) {
				h = 1;
				size++;
			}
		}
		fin.clear();
		fin.seekg(0);
		int** graph = new int* [size];
		for (int i = 0; i < size; i++) {
			graph[i] = new int[size];
			for (int j = 0; j < size; j++) {
				fin >> graph[i][j];
			}
		}

		int symbol1 = 0;
		int symbol2 = 0;
		int symbol3 = 0;

		for (symbol1; symbol1 < size; symbol1++) {
			for (symbol2 = 0; symbol2 < size; symbol2++) {
				symbol3 = graph[symbol1][symbol2];
				int z = 0;
				for (int j = 0; j < Graph_tree.size(); j++) {
					if (Graph_tree[j].second.first == symbol2 && Graph_tree[j].second.second == symbol1) {
						z = 1;
						break;
					}
				}
				if (z == 1) {
					continue;
				}
				if (symbol3 != 0) {

					Add(symbol1, symbol2, symbol3);
				}
			}
		}

		parent = new int[size];

		for (int i = 0; i < size; i++)
			parent[i] = i;

		for (int i = 0; i < size; i++) {
			delete[] graph[i];
		}
		delete[] graph;
		fin.close();
	}
};
