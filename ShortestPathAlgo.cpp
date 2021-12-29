#include<iostream>
#include<map>
#include<string>
#include<list>
#include<queue>
#include<utility>
#include<functional>
#include<unordered_set>

# define INF 0x3f3f3f3f

using namespace std;

template<typename T>
class myCompare
{
public:
    int operator() (const pair<T,int> &p1, const pair<T, int> &p2)
    {
        return p1.second < p2.second;
    }
};

template<typename T>
class Graph {
	unordered_set<T> vertices;
	map<T,list<pair<T,int>>> adjList;
public:
	Graph() {
		
	}
	
	void addEdge(T u, T v, int weight = 0, bool bidirectional = false) {
		adjList[u].push_back({v,weight});
		vertices.insert(u);
		vertices.insert(v);
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
	
	class ShortPath {
	private:
		map<T,int> dist;
		map<T,bool> visited;
		void print() {
			for(auto distance: dist) {
				cout<<distance.first<<" : "<<distance.second<<"\n";
			}
		}
	public:	
		ShortPath(Graph *g) {
			for(auto vertex: g->adjList) {
				T key = vertex.first;
				dist[key] = INF;
			} 	
		}
		
		void bfs(Graph *g,T src) {
			for(auto vertex: g->adjList) {
				T key = vertex.first;
				dist[key] = 0;
			}
			queue<T> q;
			q.push(src);
			visited[src] = true;
			while(!q.empty()) {
				T u = q.front();
				q.pop();
				cout<<u<<", ";
				for(auto neighbour: g->adjList[u]) {
						T v = neighbour.first;
						if(!visited[v]) {
							dist[v] = dist[u] + 1;
							q.push(v);
							visited[v] = true;
						}
				}
			}
			cout<<"\n\nDistances from "<<src<<" are : \n";
			print();
		}
		
		void dijkstra(Graph *g, T src) {
			priority_queue<pair<T,int>,vector<pair<T,int>>,myCompare<T>> pq;
			dist[src] = 0;
			pq.push({src,0});
			while(!pq.empty()) {
				T u = pq.top().first;
				pq.pop();
				for(auto neighbour: g->adjList[u]) {
					T v = neighbour.first;
					int weight = neighbour.second;
					if(dist[v] > dist[u] + weight) {
						dist[v] = dist[u] + weight;
						pq.push({v,dist[v]});
					}
				}
			}
			cout<<"\n\nDistances from "<<src<<" are : \n";
			print();
		}
		
		void BellmanFord(Graph *g, T src) {
			dist[src] = 0;
			int V = g->vertices.size();
			for(int count = 0; count < V-1; count++) {
				for(auto row: g->adjList) {
					T u = row.first;
					for(auto x : row.second) {
						int weight = x.second;
						T v = x.first;
						if(dist[v] > dist[u] + weight) {
							dist[v] = dist[u] + weight;
						}
					}
				}
			}
			for(auto row: g->adjList) {
				T u = row.first;
				for(auto x : row.second) {
					int weight = x.second;
					T v = x.first;
					if(dist[v] > dist[u] + weight) {
						cout<<"\n Negative Cycle Detected! \n";
						return;
					}
				}
			}
			cout<<"\n\nDistances from "<<src<<" are : \n";
			print();
		}
	};
};

int main(){
	/*
	//For BFS Unweighted graph
	Graph<string> g;
	g.addEdge("Putin","Trump",0,true);
	g.addEdge("Putin","Modi",0,true);
	g.addEdge("Putin","Pope",0,true);
	g.addEdge("Modi","Trump",0,true);
	g.addEdge("Modi","Yogi",0,true);
	g.addEdge("Yogi","Prabhu",0,true);
	g.addEdge("Prabhu","Modi",0,true);
	g.print();
	*/
	//For Dijkstra Algo, Weighted Graph without negative edge weights
	//For Bellman Ford, detects negative cycle, works for negative edge weights 
	Graph<string> g;
	g.addEdge("A", "B", -1);
    g.addEdge("A", "C", 4);
    g.addEdge( "B", "C", 3);
    g.addEdge( "B", "D", 2);
    g.addEdge( "B", "E", 2);
    g.addEdge( "D", "C", 5);
    g.addEdge( "D", "B", 1);
    g.addEdge( "E", "D", -3);
    g.addEdge("D", "F", 14);
    g.addEdge("E", "F", 10);
    g.addEdge( "F", "G", 2);
    g.addEdge( "G", "H", 1);
    g.addEdge( "G", "I", 6);
    g.addEdge( "H", "I", 7);
	g.print();
	Graph<string>::ShortPath s(&g);
	//s.bfs(&g,"Modi");
	s.BellmanFord(&g,"A");
}

