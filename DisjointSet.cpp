#include<iostream>
#include<map>

template<typename T>
class DisjointSet {
	std::map<T,T> parent;
	std::map<T,int> rank;
public:
	
	void Insert(T node) {
		parent[node] = node;
		rank[node] = 0;
	}
	
	T Find(T x) {
		if(x == parent[x])
			return x;
		parent[x] = Find(parent[x]);
		return parent[x];
	}
	
	void Union(T x, T y) {
		T x_rep = Find(x), y_rep = Find(y);
		if(x_rep == y_rep)
			return;
		if(rank[x_rep] > rank[y_rep])
			parent[x_rep] = y_rep;
		else
			parent[y_rep] = x_rep;
	}
	
	void print() {
		for(auto node: parent) {
			std::cout<<node.first<<" "<<node.second<<"\n";
		}
	}
};
