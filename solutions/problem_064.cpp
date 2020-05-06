#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<vector<int> > > dp;
vector<vector<bool> > visit;
int offset[8][2] = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

bool index_valid(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < n && !visit[i][j];
}

int tour_possible(int i, int j, int remaining_moves) {
	// cout << i << " " << j <<endl;
	if(remaining_moves == 0) {
		return 1;
	}
	if(dp[i][j][remaining_moves] != -1) {
		return dp[i][j][remaining_moves];
	}
	visit[i][j] = true;
	for(int k = 0; k < 8; ++k) {
		int p = i + offset[k][0], q = j + offset[k][1];
		if(index_valid(p, q) && tour_possible(p, q, remaining_moves - 1) == 1) {
			return dp[i][j][remaining_moves] = 1;
		}
	}
	visit[i][j] = false;
	return dp[i][j][remaining_moves] = 0;
}

int main()
{
	cout << "Enter N: ";
	cin >> n;
	int total_moves = n*n - 1;
	dp.resize(n, vector<vector<int>>(n, vector<int>(total_moves+1, -1)));
	visit.resize(n, vector<bool>(n, false));

	vector<pair<int, int> > solution;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			for (auto &row : visit) {
    			fill(row.begin(), row.end(), false);
			}
			for(auto &row : dp) {
				for(auto &row2 : row) {
					fill(row2.begin(), row2.end(), -1);
				}
			}
			if(tour_possible(i, j, total_moves) == 1) {
				solution.push_back({i, j});
			}
			// getchar();
		}
	}

	cout << "Total positions from where Knight can tour the board are: " << solution.size() << endl;
	for(auto p : solution) {
		cout << p.first << " " << p.second << endl;
	}
	return 0;
}