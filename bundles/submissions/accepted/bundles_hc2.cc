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

  best[goal] = price[goal];    // just buy the bundle

  int largest[100];
  fill(largest, largest+n, -1);        // what is largest set containing i
  
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
    if ((bundle[i] & ~bundle[goal]).any()) continue;

    for (int j = 0; j < n; j++) {
      if (!bundle[i].test(j)) continue;
      if (largest[j] < 0 || bundle[largest[j]].count() < bundle[i].count()) {
	largest[j] = i;
      }
    }
  }

  int total = 0;
  bitset<100> bought;
  for (int i = 0; i < n; i++) {
    if (largest[i] < 0) continue;
    if ((bundle[largest[i]] & bought).any()) continue;
    bought |= bundle[largest[i]];
    total += f(largest[i]);
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

  // make an artificial node of all 1's
  bundle[m].reset();
  for (int i = 0; i < n; i++) {
    bundle[m].set(i);
  }
  price[m++] = INT_MAX;

  fill(best, best+m, -1);
  cout << f(m-1) << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
