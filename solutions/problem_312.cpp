#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;
    cout << "No. of ways: ";
    if(n == 1) {
        cout << 1 << endl;
    }
    // dp1[i] represents total no. of ways till i
    // dp2[i] represents no. of ways ending with "L" shape tromino till i
    long dp1[n+1], dp2[n+1], mod = 1e9 + 7;
    dp1[0] = dp1[1] = 1;
    dp1[2] = 2;
    dp2[2] = 1;
    for(int i = 3; i <= n; ++i) {
        dp1[i] = (dp1[i-1] + dp1[i-2] + dp2[i-1]*2) % mod;
        dp2[i] = (dp2[i-1] + dp1[i-2]) % mod;
    }
    cout << dp1[n] << endl;
    return 0;
}