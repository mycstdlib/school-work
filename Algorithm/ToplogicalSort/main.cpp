#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;
// CONST
const int maxn = 52;
// VARS
vector<int> E[maxn];
vector<int> L;
vector<int> C;
char color[maxn];
int n, m;
int din[maxn];//degree
int dfs(int root)
{
  color[root] = 1;

  int res = 0;

  for(int i = 0; i < E[root].size(); i++)
  {
    int to = E[root][i];

    if(color[to] == 1)
    {
      color[root] = 2;
      C.push_back(to);
      C.push_back(root);
      if(root == to)
      {
        color[root] = 2;
        return -1;
      }
      else return to;
    }

    if(color[to] == 0)
    {
      res = dfs(to);
      if(res != 0)
      {
        color[root] = 2;
        if(res != -1)
          C.push_back(root);
        //Circle has finished
        if(res == root)
          return -1;
        else if(res == -1)
          return -1;
        else return res;
      }
    }
  }
  L.push_back(root);

  color[root] = 2;
  return 0;
}
//DFS way to sort
bool dfs_traverse()
{
  int res = 0;
  for(int i = 1; i <= n; i++)
  {
    if(din[i] == 0 && color[i] == 0)
    {
      res = dfs(i);
      if(res == -1) break;
    }
  }
  if(C.size() == 0)
  {
    for(int i = 1; i <= n && C.size() == 0; i++)
    {
      if(color[i] == 0)
      {
        res = dfs(i);
        if(res == -1) break;
      }
    }
  }
  reverse(L.begin(), L.end());
  reverse(C.begin(), C.end());
  return res;
}

//Kahn way to sort

void input()
{
  scanf("%d%d", &n, &m);
  memset(din, 0, sizeof din);
  memset(color, 0, sizeof color);
  int a, b;
  for(int i = 0 ; i < m;i++)
  {
    scanf("%d%d", &a, &b);

    //Add Edge
    E[a].push_back(b);

    din[b]++;
  }
}

void solve()
{
  if(dfs_traverse() == 0) 
  {
    printf("YES\n");
    for(int i = 0; i < L.size(); i++)
    {
      printf("%d", L[i]);
      if(i != L.size() - 1) printf(",");
    }
  }
  else
  {
    printf("NO\n");
    for(int i = 0; i < C.size(); i++)
    {
      printf("%d", C[i]);
      if( i != C.size() - 1) printf(",");
    }
  }
}

int main()
{
  input();
  solve();
  return 0;
}
