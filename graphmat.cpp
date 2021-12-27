#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

//Reverse Mapping

template<typename T>
class Graph {
	int V;
	int i = 0;
	unordered_map<int, T> invmp;
	unordered_map<T, int> mp;
	int **adjMatrix;
public:
	Graph(int V) {
    	this->V = V;
    	adjMatrix = new int*[V];
    	for (int i = 0; i < V; i++) {
      		adjMatrix[i] = new int[V];
      		for (int j = 0; j < V; j++)
      	  		adjMatrix[i][j] = -1;
    	}
  	}
  	
  	~Graph() {
    	for (int i = 0; i < V; i++) {
      		delete[] adjMatrix[i];
    		delete[] adjMatrix;
    	}
	}
	void addEdge(T u, T v, bool bidirectional = false, int weight = 0) {
		if(mp.find(u) == mp.end()) {
			mp[u] = ++i;
			invmp[i] = u;
		}
		if(mp.find(v) == mp.end()) {
			mp[v] = ++i;
			invmp[i] = v;
		}
		adjMatrix[mp[u]][mp[v]] = weight;
		if(bidirectional) {
			adjMatrix[mp[v]][mp[u]] = weight;
		}
	}
	
	void print() {
		//cout<<i;
		for(int k = 1; k <= i; k++)
			cout<<invmp[k]<<"  ";
		for(int k = 1; k <= i; k++)
		{
			cout<<"\n";
			for(int l = 1; l <= i; l++)
			{
				cout<<adjMatrix[k][l]<<"\t";
			}
		}
	}
};

int main() {
	Graph<string> g(10);
	g.addEdge("Putin","Trump",false);
	g.addEdge("Putin","Modi",false);
	g.addEdge("Putin","Pope",false);
	g.addEdge("Modi","Trump",true);
	g.addEdge("Modi","Yogi",true);
	g.addEdge("Yogi","Prabhu",false);
	g.addEdge("Prabhu","Modi",false);
	g.print();
}
