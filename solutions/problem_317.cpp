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
    // Find first MSB in "M" and "N" which is not same
    // it implies that after this bit position both "0" and "1" bits are possible from M to N. So all bits in answer after that will be "0".
    for(i = 31; i >= 0; --i) {
        if(((n >> i)&1) != ((m >> i)&1)) {
            break;
        }
    }
    ++i;
    // answer is all the bits till "i" and all "0" after that
    int ans = (n >> i) << i;
    cout << "Birwise AND of [M, N] is: " << ans << endl;
    return 0;
}