#include <bits/stdc++.h>
using namespace std;

// time complexity is O(N)
long linearTimeSolution(int n) {
    long ans = 0;
    for(int i=1; i<=n; ++i) {
        int x = i;
        // this is the main part of the solution
        // this loop runs in the order of the no. of bits in "x"
        // after each iteration rightmost "1" bit in "x" will set to "0"
        while(x) {
            x &= (x-1);
            ++ans;
        }
    }
    return ans;
}

// time complexity is O(no. of bits in n) => O(ceil(log10(n)))
long constantTimeSolution(int n) {
    int bits = 0, x = n;
    while(x) {
        x >>= 1, ++bits;
    }
    long ways[bits], pow = 2;
    ways[0] = ways[1] = 1;
    for(int i = 2; i < bits; ++i) {
        ways[i] = (ways[i-1] << 1) + pow;
        pow <<= 1;
    }
    int totalOnes = 0;
    long ans = 0;
    for(int i = bits-1; i >= 0; --i) {
        if((n >> i) & 1) {
            ans += ways[i] + pow * totalOnes;
            ++totalOnes;
        }
        pow >>= 1;
    }
    if(n & 1) {
        --totalOnes;
    }
    ans += totalOnes;
    return ans;
}

int main()
{
    int n;
    cout << "Enter N: ";
    cin >> n;
    cout << "Linear   complexity solution: " << linearTimeSolution(n) << endl;
    cout << "Constant complexity solution: " << constantTimeSolution(n) << endl;
    return 0;
}