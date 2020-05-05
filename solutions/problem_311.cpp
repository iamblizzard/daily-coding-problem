#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter size of the array: ";
    cin >> n;
    int a[n];
    cout << "Enter " << n <<" numbers:\n";
    for(int i=0; i<n; ++i) {
        cin >> a[i];
    }
    int l=0, r=n-1, ans, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(mid == n-1 || a[mid] > a[mid+1]) {
            ans = mid, r = mid-1;
        } else {
            l = mid+1;
        }
    }
    cout << "Peak number index is: " << ans << endl;
    return 0;
}