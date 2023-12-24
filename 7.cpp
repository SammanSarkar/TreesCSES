#include<bits/stdc++.h>
using namespace std;
 
int n, q;
vector<int> tree[200001];
int ancestor[200005][21],dep[200005];
 
 
 
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
          pre_process(ch, node);
	}
 
}
 
void dfs(int x, int d){
    dep[x] = d;
    for(int k : tree[x]){
         dfs(k, d + 1);
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
 
int main(){
    cin >> n >> q;
    
	for(int i = 2 ; i <= n ; i++){
		int p ; 
		cin>>p ;
		tree[p].push_back(i) ; 
	}
 
	pre_process(1 ,0 );
    
    dfs(1, 1);
    while(q--){
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << endl;
    }
}