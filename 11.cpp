#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;

 
const int maxn = 400001;
const ll MOD = 1e9+7;
ll segTree[1600010], a[400010], n, q;

 

vector<int> adj[maxn];

int timer = 0, st[maxn], en[maxn];
 
ll query(int i, int j, int p=1, int l=0, int r=2*n-2)
{
    if(i>j)return 0;

    if(l>=i and r<=j){
        return segTree[p];
    } 

    int mid = (l+r)/2;
    ll left = query(i, min(j, mid), p*2, l, mid);
    ll right = query(max(i, mid+1), j, p*2+1, mid+1, r);
    
    return left+right;
}
 
void update(int x, int val, int p=1, int l=0, int r=2*n-2)
{
    if(l==r) { 
      segTree[p]=val; 
      return; 
    }

    int mid = (l+r)/2;
    
    if(x<=mid){
        update(x, val, p*2, l, mid);
    }else{
        update(x, val, p*2+1, mid+1, r);
    } 

    segTree[p] = segTree[p*2]+segTree[p*2+1];
}
 
void dfs(int s, int p )
{
    st[s] = timer++;

    for(auto u : adj[s]){
        if(u!=p){
            dfs(u, s);
        } 
    }
        
    en[s] = timer++;
}
 
 
int main()
{

    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    } 

    for(int i = 1; i < n; i++){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1 , 0);

    for(int i = 1; i <= n; i++){
        update(st[i], a[i]);
    } 

    for(int i = 1; i <= n; i++){
        update(en[i], -a[i]);
    } 

   while(q--){
        int t, s; cin >> t >> s;
        if(t==1){
            int x; cin >> x;
            update(st[s],x);
            update(en[s],-x);
        }
        else cout << query(st[1], en[s]-1) << endl;
    }
}   