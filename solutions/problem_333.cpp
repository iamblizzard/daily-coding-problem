//Credits: https://www.geeksforgeeks.org/the-celebrity-problem/

#include<bits/stdc++.h>
using namespace std;

vector<vector<bool> > v;
int my_id;

bool randomFill() {
	int n = v.size();
	my_id = rand() % n;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i == my_id)		v[i][j] = false;
			else if(j == my_id)	v[i][j] = true;
			else				v[i][j] = rand() % 2;
			// cout << v[i][j] << " ";
		}
		// cout << endl;
	}
	if(rand() % 5 == 0) {
		v[0][my_id] = false;
	}
}

bool knows(int i, int j) {
	return v[i][j];
}

int findCelebrity(int n) {
	if(n == 1)	return 0;
	int id = findCelebrity(n - 1);

	if(id == -1) {
		return n-1;
	} else if(knows(id, n-1) && !knows(n-1, id)) {
		return n-1;
	} else if(knows(n-1, id) && !knows(id, n-1)) {
		return id;
	} else {
		return -1;
	}
}

int main()
{
	int n;
	cout << "Enter n:\n";
	cin >> n;

	v.resize(n, vector<bool>(n));
	randomFill();
	// cout << my_id << endl;

	int id = findCelebrity(n);
	
	if(id == -1) {
		cout << -1 << endl;
		return 0;
	}
	int i;
	for(i = 0; i < n; ++i) {
		if(i == id)	continue;
		if(knows(id, i) || !knows(i, id)) {
			break;
		}
	}

	cout << (i == n ? id : -1) << endl;

	return 0;
}