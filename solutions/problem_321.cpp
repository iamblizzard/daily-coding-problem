#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter N: ";
    cin >> n;
    queue<int> q;
    q.push(n);
    unordered_map<int, int> comeFrom;
    while(!q.empty()) {
        auto p = q.front();
        q.pop();
        if(p == 1)    break;
        if(comeFrom.find(p - 1) == comeFrom.end()) {
            comeFrom[p - 1] = p;
            q.push(p - 1);
        }
        for(int i = 2; i*i <= p; ++i) {
            if(p % i == 0) {
                if(comeFrom.find(p/i) == comeFrom.end()) {
                    comeFrom[p/i] = p;
                    q.push(p/i);
                }
            }
        }
    }
    vector<int> steps;
    int s = 1;
    while(s != n) {
        s = comeFrom[s];
        steps.push_back(s);
    }
    cout << "Total Steps required: " << steps.size() << endl;
    if(steps.size() > 0) {
        reverse(steps.begin(), steps.end());
        for(auto step : steps) {
            cout << step << " -> ";
        }
        cout << "1\n";
    }
    return 0;
}