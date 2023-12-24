#include <bits/stdc++.h>
 
using namespace std;
const int N = 200001 ; 
int n ; 
 
vector<int> adj[N];
long long dp[N], ans[N];
 
void dfs1(int v , int p, long long depth) {
	ans[1] += depth;
	dp[v] = 1;
	for (int i : adj[v]){
    	if (i != p) {
			dfs1(i, v, depth + 1);
			dp[v] += dp[i];
		}
  }
	
}
 
void dfs2(int v, int p) {
	for (int i : adj[v]){
    	if (i != p) {
			ans[i] = ans[v] + n - 2 * dp[i];
			dfs2(i, v);
		}
  }
	
}
 
int main() {
 
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
 
	dfs1(1,0,0);
	dfs2(1,0);
	for (int i = 1; i <= n; i++){
    cout << ans[i] <<" ";
  } 
	return 0;
}