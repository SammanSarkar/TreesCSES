#include<bits/stdc++.h>
using namespace std;
 
int n, q;
vector<int> tree[200001];
int ancestor[200005][21],dep[200005];
int c[200001] ; 
 
 
void pre_process(int node, int par){
 
    ancestor[node][0] = par;
 
    for(int i = 1; i <=20; i++){
        if(ancestor[node][i-1] != -1){
            ancestor[node][i] = ancestor[ancestor[node][i-1]][i-1];
        }else{  
            ancestor[node][i] = -1;
        } 
    }
 
    for(auto ch : tree[node]){
		if(ch == par){
			continue;
		}
          pre_process(ch, node);
	}
 
}
 
void dfs(int x, int d , int p ){
    dep[x] = d;
    for(int k : tree[x]){
		if(k == p ){
			continue ; 
		}
         dfs(k, d + 1 ,x);
    }
}
 
 
int LCA(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = 0; i < 20; i++){
        if(d & (1 << i)) b = ancestor[b][i];
    }
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
        if(ancestor[a][i] != ancestor[b][i]){
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}
 
 
void dfs2(int x , int p){
  for(int k : tree[x]){
		if(k == p ){
			continue ; 
		}
         dfs2(k,x);
         c[x]+=c[k] ; 
    }
}
 
 
int main(){
	#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
    cin >> n >> q;
    
	for(int i = 2 ; i <= n ; i++){
		int p , q; 
		cin>>p>>q;
		tree[p].push_back(q) ; 
		tree[q].push_back(p) ; 
	}
 
	pre_process(1 ,0 );
    
    dfs(1, 1 , 0);
    while(q--){
        int a, b;
        cin >> a >> b;
        int lca = LCA(a,b) ; 
        c[a]++ ; c[b]++ ; c[lca]--; 
        if(ancestor[lca][0]!= -1){
            c[ancestor[lca][0]]-- ;
        }
    }
    dfs2(1,0) ; 	
 
    for(int i = 1; i <= n ; i++){
        cout<<c[i]<<" " ; 
    }   
}