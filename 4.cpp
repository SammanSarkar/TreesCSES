#include <bits/stdc++.h>
using namespace std;
 
const int N = 200001;
vector<int> adj[N];
int c[N];
int maxd[N];
int maxd2[N];
 
void dfs1(int v, int p)
{
  maxd[v] = 0;
 maxd2[v] = 0;
 for (auto x : adj[v])
  {
   if (x == p) continue;
 dfs1(x, v);
  if (maxd[x] + 1 > maxd[v])
    {
maxd2[v] = maxd[v];
  maxd[v] = maxd[x] + 1;
 c[v] = x;
   
    }
    else if (maxd[x] + 1 > maxd2[v])
    {
  maxd2[v] = maxd[x] + 1;
 
    }
 
  }
}
 
void dfs2(int v, int p)
{
 for (auto x : adj[v])
  {
if (x == p) continue;
if (c[v] == x)
    {
if (maxd[x] < maxd2[v] + 1)
      {
    maxd2[x] = maxd[x];
    maxd[x] = maxd2[v] + 1;
     c[x] = v;
        
      }
      else
      {
        maxd2[x] = max(maxd2[x], maxd2[v] + 1);
      
      }
  
    }
    else
    {
      maxd2[x] = maxd[x];
      maxd[x] = maxd[v] + 1;
     c[x] = v;
      
    }
    dfs2(x, v);
    
  }
}
 
int main()
{
 
  int n, u, v;
  cin >> n;
 
  for (int i = 0; i < n - 1; i++)
  {
   cin >> u >> v;
   adj[u].push_back(v);
    adj[v].push_back(u);
  }
 
  dfs1(1, 0);
  dfs2(1, 0);
 
  for (int i = 1; i <= n; i++)
  {
    cout << maxd[i] << " ";
  }
  return 0;
}