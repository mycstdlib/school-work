#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

#define rep(x,s,e) for(int x = s; x < e; x++)

const int maxn = 33;

int women[maxn][maxn];
int men[maxn][maxn];
int women_dating[maxn];
int men_dating[maxn];

// The 
int women_pref[maxn][maxn];

// Men's current priority
int pCurr[maxn];

int main()
{
  //Initialization;
  memset(women, 0, sizeof women);
  memset(men, 0, sizeof men);
  rep(i, 0, maxn) women_dating[i] = -1;
  memset(women_pref, 0, sizeof women_pref);
  memset(pCurr, 0, sizeof pCurr);

  int N;
  queue<int> free;

  cin>>N;
  rep(i, 0, N)
  {
    free.push(i);
    rep(j, 0, N)
    {
      cin>>men[i][j];
      men[i][j]--;
    }
  }
  rep(i, 0, N) 
  {
    rep(j, 0, N) 
    {
      cin>>women[i][j];
      women[i][j]--;
      women_pref[i][women[i][j]] = j;
    }
  }

  
  while(!free.empty())
  {
    int m = free.front(), w;
    free.pop();

    // m must select a woman
    while(true)
    {
      w = men[m][pCurr[m]++];
      if(women_dating[w] == -1)
      {
        women_dating[w] = m;
        break;
      }
      else if(women_pref[w][m] < women_pref[w][women_dating[w]])
      {
        free.push(women_dating[w]);
        women_dating[w] = m;
        break;
      }
    }
  }

  rep(i, 0, N)
    men_dating[women_dating[i]] = i;

  rep(i, 0, N)
    cout<<men_dating[i]+1<<" ";

  cout<<endl;
  
  return 0;
}
