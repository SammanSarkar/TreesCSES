#include<bits/stdc++.h>
using namespace std;
#define SZ 200005

vector<int> a[SZ];
int s[SZ], countArr[SZ], n, k, m;
long long ans;
bool v[SZ];

void dfs_s(int u, int p) {
    s[u]=1;
    for(int x: a[u]) {
        if(!v[x] && x!=p) {
            dfs_s(x, u);
            s[u] += s[x]; 
        }
    }
}

int f_c(int u, int p, int t) {
    for(int x: a[u]) {
        if(!v[x] && x!=p && s[x]>t) {
            return f_c(x, u, t);
        }
    }
    return u;
}

void dfs(int u, int p, int d, bool c) {
    if(d>k) return;
    if(c) {
        ans += countArr[k-d];
    }
    else {
        countArr[d]++;
    }
    m = max(m, d);

    for(int x: a[u]) {
        if(!v[x] && x!=p) {
            dfs(x, u, d+1, c);
        }
    }
}

void cd(int u) {
    dfs_s(u, -1);
    int c = f_c(u, -1, s[u]>>1);
    v[c] = true;
    countArr[0] = 1;
    m = 0;
    for(int x: a[c]) {
        if(!v[x]) {
            dfs(x, c, 1, true);
            dfs(x, c, 1, false);
        }
    }
    fill(countArr, countArr+m+10, 0);
    for(int x: a[c]) {
        if(!v[x]) {
            cd(x);
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    cd(1);
    cout << ans;
}
