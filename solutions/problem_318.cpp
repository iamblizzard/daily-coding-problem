/*  Here dp[i][j] represents total songs played is "i" and unique songs are "j"
    Now we have to find dp[N][M]
    dp[i][j] = dp[i-1][j-1] * (M-j+1) [if song at "j" index wasn't played yet]
                                |--> total no. of possibilities to select "j"th song
                + dp[i-1][j] * (j-B)  [if song at "j" index was played before]
                                 |--> since we can't repeat last B songs
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M, B;
    cout << "Enter N, M and B: ";
    cin >> N >> M >> B;
    long dp[N+1][M+1];
    // we are using mod as answer may be very large
    long mod = 1e9+7;
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            dp[i][j] = (dp[i-1][j-1] * (M-j+1)) % mod;
            dp[i][j] += (dp[i-1][j] * max(j-B, 0)) % mod;
            dp[i][j] %= mod;
        }
    }
    cout << "Total no. of ways are: " << dp[N][M] << endl;
}