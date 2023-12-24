#include<bits/stdc++.h>
using namespace std;
vector<int> tree[200001];
int ancestor[200001][21] ;
 
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
 
int query(int node, int k){
    if(k == 0){
        return node;
    }
    if(node == -1){
      return -1; 
    }    
 
    for(int i = 20; i >= 0; i--){
        if(k&(1<<i)){
            return query(ancestor[node][i], k - (1<<i));
        }
    } 
}
 
 
 
int main() {
int n , q ;
cin>>n>>q;
for(int i = 2 ; i <= n ; i++){
  int p ; 
  cin>>p ;
  tree[p].push_back(i) ; 
}
pre_process(1,-1) ;
for(int i = 0 ; i < q ; i++){
  int x , k ; 
  cin>>x>>k ;
  cout<<query(x,k)<<endl ; 
}
    return 0;
}