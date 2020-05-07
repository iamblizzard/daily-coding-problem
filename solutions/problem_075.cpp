#include<bits/stdc++.h>
using namespace std;

int binarySearch(vector<int>& tailIndex, vector<int>& a, int val) {
    int l = 0, r = tailIndex.size() - 1, mid, index;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(a[tailIndex[mid]] >= val) {
            index = mid, r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return index;
}

int main()
{
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> a(n);
    cout << "Enter array:\n";
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> tailIndex, LIS;
    vector<int> prevIndex(n, -1);
    tailIndex.push_back(0);
    for(int i = 1; i < n; ++i) {
        if(a[i] < a[tailIndex.front()]) {
            tailIndex[0] = i;
        }
        if(a[tailIndex.back()] < a[i]) {
            prevIndex[i] = tailIndex.back();
            tailIndex.push_back(i);
        } else {
            int index = binarySearch(tailIndex, a, a[i]);
            prevIndex[i] = tailIndex[index - 1];
            tailIndex[index] = i;
        }
    }
    for(int i = tailIndex.back(); i >= 0; i = prevIndex[i]) {
        LIS.push_back(a[i]);
    }
    reverse(LIS.begin(), LIS.end());
    cout << "LIS size is: " << LIS.size() << endl;
    for(auto x : LIS) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}