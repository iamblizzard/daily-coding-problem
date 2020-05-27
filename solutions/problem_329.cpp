#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cout << "Enter N: ";
	cin >> n;
	cout << "Choices for each person is the index[0, n-1] of the opposite sex "
	"in decreasing order of their likeliness from left to right.\n";
	pair<int, int> women_pref[n][n], men_pref[n][n];
	int men_got[n], women_got[n];
	for(int i = 0; i < n; ++i) {
		men_got[i] = women_got[i] = -1;
	}

	for (int i = 0; i < n; ++i) {
		cout << "Enter choice for woman " << i << endl;
		for (int j = 0; j < n; ++j) {
			cin >> women_pref[i][j].first;
			women_pref[i][women_pref[i][j].first].second = j;
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << "Enter choice for man " << i << endl;
		for (int j = 0; j < n; ++j) {
			cin >> men_pref[i][j].first;
			men_pref[i][men_pref[i][j].first].second = j;
		}
	}

	while (true) {
		int i = 0;
		while (i < n && men_got[i] != -1)	++i;
		if (i == n) {
			break;
		}
		for (int j = 0; j < n; ++j) {
			int idx = men_pref[i][j].first;
			if (women_got[idx] == -1) {
				men_got[i] = idx, women_got[idx] = i;
				break;
			} else if (women_pref[idx][i].second < women_pref[idx][women_got[idx]].second) {
				men_got[women_got[idx]] = -1;
				men_got[i] = idx, women_got[idx] = i;
				break;
			}
		}
	}

	cout << "Stable Pairs (Men, Women) are:\n";
	for (int i = 0; i < n; ++i) {
		cout << i << " " << men_got[i] << endl;
	}

	return 0;
}