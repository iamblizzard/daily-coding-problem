#include<bits/stdc++.h>
using namespace std;

vector<vector<int> > tree;
vector<bool> visit;

pair<int, int> maxEdgesRemoved(int u) {
	visit[u] = true;
	int remNodes = 1, ans = 0;
	pair<int, int> temp;
	for(auto v : tree[u]) {
		if(!visit[v]) {
			temp = maxEdgesRemoved(v);
			ans += temp.second;
			if(temp.first & 1) {
				remNodes += temp.first;
			} else {
				++ans;
			}
		}
	}
	return {remNodes, ans};
}

int main()
{
	int n,x,y;
	cout << "Enter no. of nodes:\n";
	cin >> n;
	tree.resize(n);
	visit.resize(n, false);
	cout << "Enter " << n-1 << " edges (node pairs) indexed from 0:\n";
	for(int i = 0; i < n-1; ++i) {
		cin >> x >> y;
		tree[x].push_back(y);
		tree[y].push_back(x);
	}
	cout << maxEdgesRemoved(0).second << " edges can be removed.\n";
}