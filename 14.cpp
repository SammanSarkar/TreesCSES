#include <bits/stdc++.h>
using namespace std;
 

const int maxn = 200010;
int n;
vector<int> adj[maxn], subtree(maxn);


 
void dfs(int s, int p){
    subtree[s] = 1 ;

    for(int u : adj[s])    {
        if(u==p) continue;

        dfs(u, s);

        subtree[s]+=subtree[u];
    }
}
 
int dfs2(int s, int p){
    int mx = 0, node = 0;

    for(int u : adj[s]){
        if(u == p ){
            continue; 
        }
        if(subtree[u]>mx){
            mx = max(mx, subtree[u]);
            node = u;
        }
    }
        
    if(mx<=n/2){
        return s ; 
    } 
    else{
        return dfs2(node, s);
    } 
}
 
int main(){

    cin >> n;
    for(int i = 1; i < n; i++){
        int a, b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1 , 0);
    cout<<dfs2(1 , 0);
}
