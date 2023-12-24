#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001;

int dcount[MAXN];
vector<int> adj[MAXN];

set<int> colors[MAXN];


void pre_process(int v, int p) {
	for (int n : adj[v]) {
		if(n != p) {
			pre_process(n, v);
			if(colors[v].size() < colors[n].size()) {
				swap(colors[v], colors[n]);
			}
			for(int i : colors[n]){
                colors[v].insert(i); 
            }
		}
	}
	dcount[v] = colors[v].size();
}

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		int a;
		cin >> a;
		colors[i].insert(a);
	}
	for(int i = 1; i < n; i++){
		int a;
		int b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	pre_process(1, 0);
	for(int i = 1; i <= n; i++) {
		cout << dcount[i] << " ";
	}
    cout<<endl ; 
}