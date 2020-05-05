#include <bits/stdc++.h>
using namespace std;

map<string, bool> mp;
string convert(string s, int i, int c) {
    s[i] += c;
    if(c == 1) {
        if(s[i] > '9') {
            s[i] = '0';
        }
    } else {
        if(s[i] < '0') {
            s[i] = '9';
        }
    }
    return s;
}
map<string, bool> visit;
int openLock(vector<string>& deadends, string target) {
    for(auto s : deadends) {
        mp[s] = true;
    }
    if(mp["0000"]) {
        return -1;
    }
    queue<pair<string, int> > q;
    q.push({"0000", 0});
    visit["0000"] = true;
    while(!q.empty()) {
        auto p = q.front();
        if(p.first == target) {
            return p.second;
        }
        q.pop();
        string s;
        for(int i=0; i<4; ++i) {
            s = convert(p.first,i,1);
            if(!visit[s] && !mp[s]) {
                q.push({s, p.second+1});
                visit[s] = true;
            }
            s = convert(p.first,i,-1);
            if(!visit[s] && !mp[s]) {
                q.push({s, p.second+1});
                visit[s] = true;
            }
        }
    }
    return -1;
}
int main()
{
    vector<string> deadends;
    string target, s;
    cout << "Enter target: ";
    cin >> target;
    int n;
    cout << "Enter size of deadends list: ";
    cin >> n;
    cout << "Enter " << n << " deadend string(s):\n";
    while(n--) {
        cin >> s;
        deadends.push_back(s);
    }
    int answer = openLock(deadends, target);
    if(answer == -1) {
        cout << "Not possible!!\n";
    } else {
        cout << "Minimum no. of turns: " << answer << endl;    
    }
    return 0;
}