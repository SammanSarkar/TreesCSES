#include <bits/stdc++.h>
using namespace std;
 
 
int N;
vector<int> adj[200005];
int height_dp[200005];
 
int height (int n, int p) {
 
    int ans = 0;
    for (auto child : adj[n]) {
        if (child != p)
            ans = max(ans, height(child, n) + 1);
    }
 
    height_dp[n] = ans;
    return ans;
}
 
int dfs (int n, int p) {
        int ans = 0, i = 0;
    priority_queue<int> nd;
    for (auto child : adj[n])
        if (child != p)
            nd.push(height_dp[child] + 1);
    while (!nd.empty() && i < 2) {
        ans += nd.top(); nd.pop(); i++;
    }
 
    for (auto child : adj[n])
        if (child != p)
            ans = max(ans, dfs(child, n));
 
    return ans;
}
 
int main () {

    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int a ,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    height(1,0) ;
    cout << dfs(1, -1) << endl;
}