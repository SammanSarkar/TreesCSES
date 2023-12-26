#include <bits/stdc++.h>
using namespace std;

const int MAX= 2e5+2;

vector<int> children[MAX];
int subtree_size[MAX];

void dfs(int node) {
 subtree_size[node] = 1;

 for (int child : children[node]) {
 dfs(child);
  subtree_size[node] += subtree_size[child];

 }
}

int main() {
 int N;
 cin >> N;

 for (int i = 2; i <=N; i++) {
  int parent;
  cin >> parent;
  children[parent].push_back(i);
 }

 dfs(1);
 for (int i = 1; i <= N; i++) {
 cout << subtree_size[i] - 1<<" ";
}
 cout << endl;
}
