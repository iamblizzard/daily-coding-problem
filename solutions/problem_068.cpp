#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
	cout << "Enter total number of bishops: ";
    cin >> n;
	int x[n], y[n];
	for(int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
	}
	unordered_map<int, int> diagonal1, diagonal2;
	for(int i = 0; i < n; ++i) {
        diagonal1[x[i] - y[i]]++;
        diagonal2[x[i] + y[i]]++;
	}
	long total_pairs = 0;
	for(auto x : diagonal1) {
		total_pairs += (x.second * (x.second - 1)) >> 1;
	}
	for(auto x : diagonal2) {
		total_pairs += (x.second * (x.second - 1)) >> 1;
	}
    cout << "Total attacking pairs: " << total_pairs << endl;
    return 0;
}