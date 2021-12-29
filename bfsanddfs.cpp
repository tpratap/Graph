#include<iostream>
#include<map>
#include<string>
#include<list>
#include<queue>
#include<unordered_set>

using namespace std;

template<typename T>
class Graph {
public:
	map<T,list<pair<T,int>>> adjList;
	//unordered_set<T> vertices;
	Graph() {
		
	}
	
	void addEdge(T u, T v, bool bidirectional = false, int weight = 0) {
		adjList[u].push_back({v,weight});
		//vertices.insert(u);
		//vertices.insert(v);
		if(bidirectional) {
			adjList[v].push_back({u,weight});
		}
	}	
	
	void print() {
		for(auto row: adjList) {
			T key = row.first;
			cout<<key<<"->";
			for(auto element: row.second) {
				cout<<element.first<<" ";
				if(element.second != 0)
					cout<<"("<<element.second<<"), ";
			}
			cout<<"\n";
		}	
	}
	
	void bfs(T src,map<T,bool> &visited) {
		queue<T> q;
		q.push(src);
		visited[src] = true;
		while(!q.empty()) {
			T vertex = q.front();
			q.pop();
			cout<<vertex<<", ";
			for(auto neighbour: adjList[vertex]) {
					if(!visited[neighbour.first]) {
						q.push(neighbour.first);
						visited[neighbour.first] = true;
					}
			}
		}
	}
	
	void dfs(T src,map<T,bool> &visited) {	
		visited[src] = true;
		cout<<src<<", ";
		for(auto neighbour: adjList[src]) {
				if(!visited[neighbour.first]) {
					dfs(neighbour.first,visited);
			}
		}
	}
	
	void bfsAll() {
		map<T,bool> visited;
		for(auto src: adjList) {
			if(!visited[src.first]) {
				bfs(src.first,visited);
			}
		}
		cout<<"\n";
	}
	
	void dfsAll() {
		map<T,bool> visited;
		for(auto src: adjList) {
			if(!visited[src.first]) {
				dfs(src.first,visited);
			}
		}
		cout<<"\n";
	}
};


int main(){
	Graph<string> g;
	g.addEdge("Putin","Trump",false);
	g.addEdge("Putin","Modi",false);
	g.addEdge("Putin","Pope",false);
	g.addEdge("Modi","Trump",true);
	g.addEdge("Modi","Yogi",true);
	g.addEdge("Yogi","Prabhu",false);
	g.addEdge("Prabhu","Modi",false);
	
/*
    ___________________> Modi-->Prabhu <----
   |			/    \            /
   |		      /       \         /
   Putin------>   Trump	         Yogi
   |
   |---->Pope
*/
	g.print();
	g.bfsAll();
	g.dfsAll();
}

