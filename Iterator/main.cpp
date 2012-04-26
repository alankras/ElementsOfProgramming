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

#define UNDEFINED -1

class Graph {

	private:
		vector<vector<int> > storage;
		vector<int> color;
		vector<int> parent;
		class DFSIterator{
			public:
				DFSIterator(const Graph& graph) : begin(&graph), current(0){ }
				int operator *() const{
					return current;
				}

				DFSIterator operator ++ () {
					current = begin -> DFS_VISIT(current);
					return *this;
				}

				bool operator != (const DFSIterator& it) {
					if (current == *it) return false;
					 return true;
				}

			private:
				const Graph* begin;
				int current;

		};

	public:
		typedef DFSIterator iterator;
		Graph(int count){
			vector<int> current(count, -1);
			for(int i = 0; i < count; i++){ 
				storage.push_back(current);
				color.push_back(-1);
				parent.push_back(-1);
			}
		}
		iterator end(){
			iterator endIt(*this);
			for(size_t i = 0; i < storage.size(); i++) {
				++endIt;
			}
			return endIt;
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

		void PrintGraph(){
			for(unsigned int i = 0; i < storage.size();i++){
				for(unsigned int j = 0; j < storage[i].size(); j++){
					if (storage[i][j] != -1) printf("%d - %d\n", i, j);
				}
			}			
		}

		bool IsEdgePresent(int v1, int v2){
			if (storage[v1][v2] != NULL) return true;	
			else return false;		
		}

		int DFS_VISIT(int v1) const {
			int d = -1;
			while(true) {
				if (v1 != -1) {
					for(int i = 0; i < storage[v1].size(); i++) {
						if ((storage[v1][i] != -1) && ( i > d)) return i;
					}
				}
				d = v1;
				v1 = parent[v1];
				if (v1 == -1) { 
					return UNDEFINED;
				}
			}
		}

	vector<int> BFS(int v1){
		vector<int> bfs;
		for(unsigned int i = 0; i < color.size(); i++){
			color[i] = 1;
		}
		color[v1] = -1;
		queue<int> Q;
		Q.push(v1);
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
		for(unsigned int i = 0; i < storage.size(); i++){
			color[i] = 1;
		}
		return bfs;
	}
};

void restoreGraph(Graph::iterator& beginIt, Graph::iterator& endIt, const vector<int>& bfs, Graph* result) {
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
			result -> AddEdge(bfs[0], bfs[1], 1);
			result -> AddEdge(bfs[0], bfs[2], 1);
		}

	}
	else {
		Graph::iterator currentRootIt(beginIt);
		++beginIt;
		Graph::iterator copyBeginIt(beginIt);
		Graph::iterator copy2BeginIt(beginIt);
		
		unsigned int index = 2;
		vector<int> vertexIndex;
		while ((beginIt != endIt) && (*beginIt != UNDEFINED)){
			while ((index + 1 < bfs.size()) && (bfs[index] != *beginIt) && (beginIt != endIt) && (*beginIt != UNDEFINED)) {
				copy2BeginIt = beginIt;
				vertexIndex.push_back(distance(bfs.begin(), find(bfs.begin(), bfs.end(), *beginIt)));
				++beginIt;
			}
			vector<int> bitBFS;
			if (vertexIndex.size() == 1) {
				for(unsigned int i = 0; i < bfs.size() - 1; i++) {
					bitBFS.push_back(bfs[i + 1]);
				}
				vertexIndex.clear();
			}
			else{
				sort(vertexIndex.begin(), vertexIndex.end());
				for(unsigned int i = 0; i < vertexIndex.size(); i++){
					bitBFS.push_back(bfs[vertexIndex[i]]);
				}
				vertexIndex.clear();
			}
			if (bitBFS.size() > 0){
				result -> AddEdge(*currentRootIt, *copyBeginIt, 1); 
				restoreGraph(copyBeginIt, copy2BeginIt, bitBFS, result);
			}
			else return;
			copyBeginIt = beginIt;
			copy2BeginIt = beginIt;
			index++;
		}
	}
}

void testRestore(Graph::iterator& beginIt, Graph::iterator& endIt, vector<int> bfs, Graph& restoreGraph) {
	Graph::iterator it(restoreGraph);
	while (beginIt != endIt){
		assert(*beginIt == *it);
		++beginIt;
		++it;
	}
	vector<int> restoreBFS = restoreGraph.BFS(0);
	for(unsigned int i = 0 ; i < bfs.size(); i++){
		assert(bfs[i] == restoreBFS[i]);
	}
	
}
void checkRestore() {
	Graph p(6);
	p.AddEdge(0, 1, 5);
	p.AddEdge(0, 2, 4);
	p.AddEdge(0, 3, 3);
	p.AddEdge(1, 4, 6);
	p.AddEdge(1, 5, 1);
	vector<int> bfs = p.BFS(0);
	Graph::iterator beginIt(p);
	Graph::iterator endIt = p.end();
	Graph result(bfs.size());
	restoreGraph(beginIt, endIt, bfs, &result);
	Graph& restore = result;
	testRestore(beginIt, endIt, bfs, restore);
}
int main() {
	checkRestore();
	return 0;
}
