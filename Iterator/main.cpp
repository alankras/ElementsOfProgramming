#include "stdio.h"
#include <map>
#include <vector>
#include <iostream>
#include "stdio.h"
#include <queue>
#include <stack>

using namespace std;

#define UNDEFINED -1

class Graph{
	
	private:
		vector<vector<int> > storage;
		vector<int> color;
		class DFSIterator{
			public:
				DFSIterator(Graph& graph) : begin(graph), current(0){ }

				int operator *(){
					return current;
				}

				DFSIterator operator ++(){
					current = begin.DFS_VISIT(current);
					return *this;
				}

			private:
				Graph& begin;
				int current;

		};

	public:
		typedef DFSIterator iterator;
		Graph(int count){
			vector<int> current;
			for(int i = 0; i < count; i++){
				current.push_back(-1);
				color.push_back(1);// 0 - black, 1 - white , -1 -grey
			}
			for(int j = 0; j < count; j++){ 
				storage.push_back(current);
			}
		}

		bool AddEdge(unsigned int v1, unsigned int v2,int dist){
			if ((v1 <= storage.size()) && (v2 <= storage.size())){
				storage[v1][v2] = dist;
				return true;
			}
			return false;
		}

		bool RemoveEdge(unsigned int v1, unsigned int v2){
			if ((v1 <= storage.size()) && (v2 <= storage.size())){
				storage[v1][v2] = -1;
				return true;
			}
			return false;		
		}

		void PrintGraph(){
			for(unsigned int i = 0; i < storage.size();i++){
				for(unsigned int j = 0; j < storage[i].size(); j++){
					if (storage[i][j] != NULL) printf("%d - %d\n",i,j);
				}
			}			
		}

		bool IsEdgePresent(int v1, int v2){
			if (storage[v1][v2] != NULL) return true;	
			else return false;		
		}
		
		void DFS(){
			for(unsigned int i = 0; i < color.size(); i++){
				color[i] = 1;
			}
			for(unsigned int i = 0; i < color.size(); i++){
				if (color[i] == 1){ 
					DFS_VISIT(i);
			}
			
			}			
		}

		int DFS_VISIT(int v1) {
			if (color[v1] == 1) color[v1] = -1;
			for (int i = 0; i < storage[v1].size(); i++){
				if ((storage[v1][i] != -1)&&(color[i] != 0)&&(color[i] != -1)) {
					
					return i;
				}
			}
			color[v1] = 0;
			for(int i = 0; i < storage.size(); i++){
				if ((storage[i][v1] != -1) && (color[i] != 0)) {
					return DFS_VISIT(i);	
				}
			}
			return UNDEFINED;
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
		for(int i = 0; i < storage.size(); i++){
			color[i] = 1;
		}
		return bfs;
	}
};

void restoreGraph(Graph::iterator& it, const vector<int>& bfs){
	Graph result (bfs.size() - 1);
	cout << *it;

}
int main(){
	Graph p(8);
	p.AddEdge(0, 1, 5);
	p.AddEdge(0, 3, 4);
	p.AddEdge(1, 5, 3);
	p.AddEdge(5, 6, 6);
	p.AddEdge(5, 7, 1);
	p.AddEdge(3, 2, 3);
	p.AddEdge(3, 4, 8);
	vector<int> bfs = p.BFS(0);
	Graph::iterator it(p);
//	restoreGraph(it, bfs);
	it++;
	cout << *it << endl;
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;
//	it++;
	cout << *it;
	return 0;
}
