#include "stdio.h"
#include <map>
#include <vector>
#include <iostream>
#include "stdio.h"
#include <queue>
#include <stack>
#include <algorithm>
#include "assert.h"
using namespace std;

const int UNDEFINED = -1;

class Graph {

	private:
		vector<vector<int> > storage;
		vector<int> color;
		vector<int> parent;
		class DFSIterator{
			public:
				DFSIterator(const Graph* graph) : begin(graph), current(0){ }
				int operator *() const{
					return current;
				}

				DFSIterator& operator ++ () {
					current = begin -> dfsVisit(current);
					if (current== UNDEFINED) {
						begin = 0;
					}
					return *this;
				}

				bool operator!= (const DFSIterator& it) const {
					if (current == *it) return false;
					 return true;
				}

			private:
				const Graph* begin;
				int current;

		};

	public:
		friend ostream& operator << (ostream& out , const Graph& str) ;
		typedef DFSIterator iterator;
		explicit Graph(int count) : color(count, UNDEFINED),
									parent(count, UNDEFINED)
		{
			vector<int> current(count, UNDEFINED);
			storage.reserve(count);

			for(int i = 0; i < count; i++){ 
				storage.push_back(current);
			}
		}
		vector<int>& operator[](size_t i) {
			return storage[i];
		}

		const vector<int>& operator[](size_t i) const {   //char*
			return storage[i];
		}

		iterator end(){
			return iterator(0);
		}

		int size() const{
			return storage.size();
		}

		bool AddEdge(unsigned int v1, unsigned int v2,int dist){
			if ((v1 <= storage.size()) && (v2 <= storage.size())){
				storage[v1][v2] = dist;
				parent[v2] = v1;
				return true;
			}
			return false;
		}

		bool RemoveEdge(unsigned int v1, unsigned int v2){
			if ((v1 <= storage.size()) && (v2 <= storage.size())){
				storage[v1][v2] = -1;
				parent[v2] = -1; 
				return true;
			}
			return false;		
		}

		int dfsVisit(int sourceVertex) const {
			int d = -1;
			while(true) {
				if (sourceVertex != -1) {
					for(int i = 0; i < static_cast<int>(storage[sourceVertex].size()); i++) {
						if ((storage[sourceVertex][i] != -1) && ( i > d)) {
							return i;
						}
					}
				}
				d = sourceVertex;
				sourceVertex = parent[sourceVertex];
				if (sourceVertex == UNDEFINED) { 
					return UNDEFINED;
				}
			}
		}

	vector<int> bfs(int sourceVertex){
		vector<int> bfs;
		for(unsigned int i = 0; i < color.size(); i++){
			color[i] = 1;
		}
		color[sourceVertex] = -1;
		queue<int> Q;
		Q.push(sourceVertex);
		while (!Q.empty()){
			int u = Q.front();
			bfs.push_back(u);
			Q.pop();
			for(unsigned int i = 0; i < color.size(); i++){
				if ((storage[u][i] != -1)&&(color[u] != 0)){
					if (color[i] == 1) color[u] = -1;
					Q.push(i);
				}
			}
			color[u] = 0;
		}
//		fill(color.begin(), color.end(), 1);
		
		return bfs;
	}
};

ostream& operator << (ostream& out , const Graph& str) {
	for(unsigned int i = 0; i < str.size();i++){
		for(unsigned int j = 0; j < str.size(); j++){
			if (str[i][j] != -1) {
				out << i << "-" << j << endl;
			}
		}
	}	
	return out;
}

void restoreGraph(Graph::iterator beginIt, Graph::iterator endIt, const vector<int>& bfs, Graph* result, vector<int> visitedVertex, const vector<int>& startBfs) {
	if (bfs.size() == 1) return;
	if (bfs.size() == 2) {
		result -> AddEdge(bfs[0], bfs[1], 1);
	}
	else 
	if (bfs.size() == 3) {
		Graph::iterator firstVertexIt(beginIt);
		++beginIt;
		Graph::iterator secondVertexIt(beginIt);
		++beginIt;
		if (*beginIt < *secondVertexIt) {
			result -> AddEdge(bfs[0], bfs[1], 1);
			result -> AddEdge(bfs[1], bfs[2], 1);
		}
		else {
			int p = distance(startBfs.begin(), find(startBfs.begin(), startBfs.end(), bfs[2]));
			if (visitedVertex[startBfs[distance(startBfs.begin(), find(startBfs.begin(), startBfs.end(), bfs[2])) - 1]] == 1){
				result -> AddEdge(bfs[0], bfs[1], 1);
				result -> AddEdge(bfs[0], bfs[2], 1);
			}
			else {
				result -> AddEdge(bfs[0], bfs[1], 1);
				result -> AddEdge(bfs[1], bfs[2], 1);				
			}
		}

	}
	else {
		Graph::iterator currentRootIt(beginIt);
		visitedVertex[*beginIt] = 1;
		++beginIt;
		visitedVertex[*beginIt] = 1;
		Graph::iterator copyFirstBeginIt(beginIt);
		Graph::iterator copySecondBeginIt(beginIt);
		Graph::iterator copyThirdBeginIt(beginIt);
		
		unsigned int index = 2;
		vector<int> vertexIndex;
		while ((beginIt != endIt) && (*beginIt != UNDEFINED)){
			while ((index < bfs.size()) && (bfs[index] != *beginIt) && (beginIt != endIt) && (*beginIt != UNDEFINED)) {
				visitedVertex[*beginIt] = 1;
				copySecondBeginIt = beginIt;
				vertexIndex.push_back(distance(bfs.begin(), find(bfs.begin(), bfs.end(), *beginIt)));
				++beginIt;
			}
			if (index == bfs.size()) {
				result -> AddEdge(*copyThirdBeginIt, index - 1, 1); 
			}
			vector<int> bitBFS;
			/*if (vertexIndex.size() == 1) {
				for(unsigned int i = 0; i < bfs.size() - 1; i++) {
					bitBFS.push_back(bfs[i + 1]);
				}
			}*/
			//else{
				sort(vertexIndex.begin(), vertexIndex.end());
				for(unsigned int i = 0; i < vertexIndex.size(); i++){
					bitBFS.push_back(bfs[vertexIndex[i]]);
				}
			//}
			vertexIndex.clear();
			if (bitBFS.empty()) return;

			result -> AddEdge(*currentRootIt, *copyFirstBeginIt, 1); 
			restoreGraph(copyFirstBeginIt, copySecondBeginIt, bitBFS, result, visitedVertex, startBfs);
			copyThirdBeginIt = copyFirstBeginIt;
			copyFirstBeginIt = beginIt;
			copySecondBeginIt = beginIt;
			index++;
		}
		if (*beginIt == *endIt) 
			result -> AddEdge(*currentRootIt, *endIt, 1); 
	}
}

int testRestore(Graph::iterator beginIt, Graph::iterator endIt, vector<int> bfs, Graph* restoreGraph, int countMistake) {
	Graph::iterator it(restoreGraph);
	while (beginIt != endIt){
		assert(*beginIt == *it);
		++beginIt;
		++it;
	}
	bool flag = true;
	vector<int> restoreBFS = restoreGraph -> bfs(0);
	if (restoreBFS.size() != bfs.size()) return ++countMistake;
	for(unsigned int i = 0 ; i < bfs.size(); i++){
		if (bfs[i] != restoreBFS[i]){ 
			flag = false;
		}
	}
	if (flag == false) 
		return ++countMistake;
	else return countMistake;
}
void checkRestore() {
	Graph p(9);
	p.AddEdge(0, 1, 5);
	p.AddEdge(0, 4, 1);
	p.AddEdge(0, 5, 1);
	p.AddEdge(1, 2, 1);
	p.AddEdge(1, 3, 1);
	p.AddEdge(2, 8, 1);
	p.AddEdge(5, 6, 1);
	p.AddEdge(6, 7, 1);
	cout << p;
	vector<int> bfs = p.bfs(0);
	Graph::iterator beginIt(&p);
	Graph::iterator endIt = p.end();
	Graph result(bfs.size());
	vector<int> visitedVertex(bfs.size(), 0);
	restoreGraph(beginIt, endIt, bfs, &result, visitedVertex, bfs);
	Graph& restore = result;
	cout << testRestore(beginIt, endIt, bfs, &restore, 0);
	
}

int creationTest(int size, int randomConst, int countMistake) {
	Graph p(size);
	if (size > 1) { 
		p.AddEdge(0, 1, 1);
		for(int i = 2; i < size; i++) {
			srand(i * randomConst);
			int random = rand() % i;
			p.AddEdge(random, i, 1);
		}
		vector<int> bfs = p.bfs(0);
		Graph::iterator beginIt(&p);
		Graph::iterator endIt = p.end();
		Graph result(bfs.size());
		vector<int> visitedVertex(bfs.size(), 0);
		restoreGraph(beginIt, endIt, bfs, &result, visitedVertex, bfs);
		Graph& restore = result;
		int current = countMistake;
		countMistake = testRestore(beginIt, endIt, bfs, &restore, countMistake);
		if (countMistake != current) cout << p << endl << "size = " << endl << size << "========" << endl;
	}
	return countMistake;
}

void bigTest() {
	int countMistake = 0;
	for(int i = 0; i < 1000; i++) {
		srand(i);
		countMistake = creationTest(rand() % 10, rand() % 100, countMistake);
	}
	cout << countMistake;
}
int main() {
	checkRestore();
	bigTest();
	return 0;
}
