#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m,n;
    cout << "Enter M: ";
    cin >> m;
    cout << "Enter N: ";
    cin >> n;
    int i;
    // assuming 32 bit INTEGER
    for(i = 31; i >= 0; --i) {
        if(((n >> i)&1) != ((m >> i)&1)) {
            break;
        }
    }
    ++i;
    int ans = (n >> i) << i;
    cout << "Birwise AND of [M, N] is: " << ans << endl;
    return 0;
}