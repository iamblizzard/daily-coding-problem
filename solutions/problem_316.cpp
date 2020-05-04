#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int no_of_ways[N];
	vector<int> coins;
	for(int i = 0; i < N; ++i) {
		cin >> no_of_ways[i];
	}

	for(int i = 1; i < N; ++i) {
		if(no_of_ways[i] == 0) {
			continue;
		}
		// find first denomination which is must
		coins.push_back(i);
		// then reduce the no. of ways formed by the denomination "i". 
		// this logic is the reverse of finding no. of ways (by adding the no. of ways from denomination "i")
		for(int j = N-1; j >= i; --j) {
			no_of_ways[j] -= no_of_ways[j-i];
		}
	}
	
	for(auto coin : coins) {
		cout << coin << " ";
	}
	cout << endl;

	return 0;
}