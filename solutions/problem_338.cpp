#include<bits/stdc++.h>
using namespace std;

int main()
{
	unsigned int n;
	cout << "Enter n:\n";
	cin >> n;

	// find the first set of 1's [start, end] starting from LSB
	int x = n, start = -1, idx = 0, end = -1;
	while(x) {
		if(x&1) {
			if(start == -1)	start = idx;
		} else {
			if(start != -1) {
				end = idx-1;
				break;
			}
		}
		x >>= 1, ++idx;
	}
	if(end == -1)	end = idx-1;
	// remove all 1's from [first, end) and shift end 1 to the left by 1 position
	// add removed 1's in the last i.e, to the LSBs

	unsigned int ans = n;
	ans &= ~((1 << (end+1)) - 1);
	ans |= 1 << (end+1);
	ans |= (1 << (end - start)) - 1;

	cout << ans << endl;

	return 0;
}