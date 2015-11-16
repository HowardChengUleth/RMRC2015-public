#include <iostream>
#include <algorithm>
#include <bitset>
#include <climits>

using namespace std;

int n, m;
bitset<100> bundle[201];
int price[201];
int best[201];

int f(int goal)
{
  if (best[goal] >= 0) return best[goal];

  int total = 0;
  bitset<100> bought;
  best[goal] = price[goal];    // just buy the bundle
  
  // try to see if I can buy the goal with other bundles.  This is not
  // designed to be very efficient here...
  for (int i = 0; i < m; i++) {
    if (i == goal) continue;

    // special case when bundles are the same
    if (bundle[i] == bundle[goal]) {
      best[goal] = min(best[goal], price[i]);
      continue;
    }
    
    // subset test
    if ((bundle[i] & ~bundle[goal]).none()) {
      bought |= bundle[i];
      total += f(i);
    }
  }

  if (bundle[goal] == bought) {
    best[goal] = min(best[goal], total);
  }
  
  return best[goal];
}

void solve()
{
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int s;
    cin >> price[i] >> s;
    bundle[i].reset();
    for (int j = 0; j < s; j++) {
      int item;
      cin >> item;
      bundle[i].set(item-1);
    }
  }

  int goal = -1;
  for (int i = 0; i < m && goal < 0; i++) {
    bool all = true;
    for (int j = 0; j < n && all; j++) {
      all &= bundle[i].test(j);
    }
    if (all) {
      goal = i;
    }
  }

  // make an artificial node of all 1's
  if (goal < 0) {
    for (int i = 0; i < n; i++) {
      bundle[m].set(i);
    }
    price[m] = INT_MAX;
    goal = m++;
  }
  
  fill(best, best+m, -1);
  cout << f(goal) << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
