#include <bits/stdc++.h>
using namespace std;

vector<int> adj[200005];
int dp[200005][2];


void dfs(int v, int p) {
 for (int u : adj[v]) {
 if (u != p) {
    dfs(u, v);
    dp[v][0] += max(dp[u][0], dp[u][1]);
   }
 }
 for (int u : adj[v]) {
   if (u != p) {
    dp[v][1] = max(dp[v][1], dp[u][0] + 1 + dp[v][0] - max(dp[u][0], dp[u][1]));
  }
 }
}


int main() {
 int n;
 cin >> n;
 for (int i = 1; i < n; i++) {
 int u, v;
  cin >> u >> v;
  adj[u].push_back(v), adj[v].push_back(u);
 }
 dfs(1, 0);

 cout << max(dp[1][0], dp[1][1]) << endl;
}