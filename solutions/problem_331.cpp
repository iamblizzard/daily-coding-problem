#include<bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	cout << "Enter string:\n";
	cin >> s;

	int x = 0, y = 0;
	for(auto xx : s) {
		if(xx == 'x')	++x;
		else			++y;
	}

	int ans = x, xc = 0, yc = 0;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == 'x')	++xc;
		else			++yc;
		ans = min(ans, yc + (x - xc));
	}
	cout << ans << endl;
	return 0;
}