#include<iostream>
#include<map>
#include<string>
#include<list>

using namespace std;

template<typename T>
class Graph {
	map<T,list<pair<T,int>>> adjList;
public:
	Graph() {
		
	}
	
	void addEdge(T u, T v, bool bidirectional = false, int weight = 0) {
		adjList[u].push_back(make_pair(v,weight));
		if(bidirectional) {
			adjList[v].push_back(make_pair(u,weight));
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
	g.print();
	Graph<int> g2;
	g2.addEdge(1,2);
	g2.addEdge(100,2);
	g2.addEdge(100,3);

	g2.print();
}

