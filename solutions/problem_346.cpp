#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int idx, dist, hops;
	Node(int n, int d, int h) : idx(n), dist(d), hops(h) {}
	bool operator < (const Node& that) const {
		return dist > that.dist;
	}
};

vector<vector<pair<int, int> > > graph;
// unordered_map<int, string> flight_name;
int k;

int findPath(int src, int dest) {
	priority_queue<Node, vector<Node> > pq;
	pq.push(Node(src, 0, 0));
	while(!pq.empty()) {
		Node node = pq.top();
		pq.pop();
		if(node.idx == dest) {
			return node.dist;
		}
		if(node.hops == k) {
			continue;
		}
		for(auto next : graph[node.idx]) {
			pq.push(Node(next.first, next.second + node.dist, node.hops + 1));
		}
	}
	return -1;
}

int main()
{
	int n, m, price, i = 0;
	string src, dest;
	unordered_map<string, int> flight_code;
	cout << "Enter total cities and k:\n";
	cin >> n >> k;
	graph.resize(n);
	cout << "Enter total no. of flight connections:\n";
	cin >> m;
	cout << "Enter " << m << " list of connections:\n";

	while(m--) {
		cin >> src >> dest >> price;
		if(flight_code.find(src) == flight_code.end()) {
			flight_code[src] = i;
			// flight_name[i] = src;
			++i;
		}
		if(flight_code.find(dest) == flight_code.end()) {
			flight_code[dest] = i;
			// flight_name[i] = dest;
			++i;
		}
		graph[flight_code[src]].push_back({flight_code[dest], price});
	}
	cout << "Enter src and dest:\n";
	cin >> src >> dest;

	int dist = findPath(flight_code[src], flight_code[dest]);
	if(dist == -1) {
		cout << "Not possible!\n";
		return 0;
	}
	cout << "Distance: " << dist << endl;

	return 0;
}

/*
14 3
7
JFK ATL 150
ATL SFO 400
ORD LAX 200
LAX DFW 80
JFK HKG 800
ATL ORD 90
JFK LAX 500
*/