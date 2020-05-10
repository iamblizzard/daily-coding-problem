#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cout << "Enter string:\n";
    cin >> s;
    int count[256] = {0}, temp[256] = {0};
    int distinct = 0;
    for(auto x : s) {
        count[x]++;
        if(count[x] == 1)   ++distinct;
    }
    int c = distinct;
    int ans = s.size();
    int j = 0, index;
    for(int i=0; i < s.size(); ++i) {
        temp[s[i]]++;
        if(temp[s[i]] == 1) {
            --c;
        }
        // there is at least 1 occurence of each char between [j, i]
        if(c == 0) {
            while(j <= i) {
                // this is the smallest window of all chars ending at index i
                if(temp[s[j]] == 1) {
                    if(ans > i-j+1) {
                        ans = i-j+1, index = j;
                    }
                    break;
                }
                temp[s[j++]]--;
            }
            temp[s[j++]]--;
            ++c;
        }
    }
    cout << "Window size is: " << ans << endl;
    cout << s.substr(index, ans) << endl;
    return 0;
}