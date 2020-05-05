#include <bits/stdc++.h>
using namespace std;

bool isPossible(vector<int>& nums) {
    int sum = 0, n = nums.size();
    for(auto x : nums) {
        sum += x;
    }
    if(sum & 1) {
        return false;
    }
    sum >>= 1;
    bool dp[sum+1][n+1];
    memset(dp, false, sizeof dp);
    for(int j=0; j<=n; ++j) {
        dp[0][j] = true;
    }
    for(int i=1; i<=sum; ++i) {
        for(int j=1; j<=n; ++j) {
            dp[i][j] = dp[i][j-1];
            if(i >= nums[j-1]) {
                dp[i][j] |= dp[i-nums[j-1]][j-1];
            }
        }
    }
    return dp[sum][n];
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Enter integers:\n";
    for(int i=0; i<n; ++i) {
        cin >> nums[i];
    }
    cout << (isPossible(nums) ? "YES\n" : "NO\n");
    return 0;
}