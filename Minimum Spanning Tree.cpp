#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include "DisjointSet.cpp"
#include "Graph.cpp"
using namespace std;

#define INF 0x3f3f3f3f

template<typename T>
class Edge {
public:
	T src,dest;
	int weight;
	Edge(T s, T d, int w) {
		src = s;
		dest = d;
		weight = w;
	}
};

template<typename T>
class EdgeList {
public:
	vector<Edge<T>> EdgeList;
	set<T> vertices;
	void addEdge(T src, T dest, int weight) {
		Edge<T> edge(src,dest,weight);
		EdgeList.push_back(edge);
		vertices.insert(src);
		vertices.insert(dest);
	}
	
	void print() {
		for(Edge<T> edge: EdgeList) {
			cout<<edge.src<<" "<<edge.dest<<" "<<edge.weight<<"\n";
		}
		cout<<"\n";
	}
	
	void Sort() {
		sort(EdgeList.begin(), EdgeList.end(),myCompare<T>());
	}
};

template<typename T>
class MinimumSpanningTree {
public:
	void Kruskal(EdgeList<T> *e) {
		e->Sort();
		int V = e->vertices.size();
		vector<Edge<T>> MST;
		int v = 0, i = 0,res = 0;
		int E = e->EdgeList.size();
		DisjointSet<T> dset;
		for(auto vertex: e->vertices) {
			dset.Insert(vertex);
		}
		while(v < V-1 && i < E) {
			Edge<T> next_edge = e->EdgeList[i++];
			T x = dset.Find(next_edge.src);
			T y = dset.Find(next_edge.dest);
			if(x != y) {
				MST[v++] = next_edge;
				dset.Union(x,y);
				res += next_edge.weight;
			}
		}
		cout<<MST.size();
		for(auto m: MST) {
			cout<<m.src<<" "<<m.dest<<" "<<m.weight<<"\n";
		}
		cout<<res<<"\n";
	}
	void Prims(Graph<T> *g, T src) {
		priority_queue<pair<T,int>,vector<pair<T,int>>,myCompare<T>> pq;
		map<T,bool> inMST;
		map<T,T> parent;
		map<T,int> dist;
		for(auto vertex: g->vertices) {
			inMST[vertex] = false;
			parent[vertex] = vertex;
			dist[vertex] = INF;
		}
		pq.push({src,0});
		dist[src] = 0;
		while(!pq.empty()) {
			T u = pq.top().first;
			pq.pop();
			if(inMST[u] == true) {
				continue;
			}
			for(auto neighbour: g->adjList[u]) {
				T v = neighbour.first;
				int w = neighbour.second;
				if(inMST[v] == false && dist[v] > w) {
					dist[v] = w;
					pq.push({v,dist[v]});
					parent[v] = u;
				}
			}
		}
		for(auto m:parent) {
			cout<<m.first<<" ";
		}
	}
};

int main() {
	Graph<string> g;
	g.addEdge("A", "B", 10);
    g.addEdge("A", "C", 8);
    g.addEdge( "B", "D", 3);
    g.addEdge( "B", "C", 5);
    g.addEdge( "C", "E", 4);
    g.addEdge( "C", "E", 12);
    g.addEdge( "C", "D", 4);
    g.addEdge( "D", "E", 15);
   // g.addEdge("E", "F", -2);
    g.print();
	MinimumSpanningTree<string> MST;
	MST.Prims(&g,"A");
	g.print();
	return 0;	
}
