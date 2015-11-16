#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <set>
#include <cassert>

using namespace std;

typedef vector<int> VI;

const int MAX_N = 100;
const int MAX_M = 200;

const int INF = INT_MAX;    // is this big enough if MAX_N is larger?

struct Bundle
{
  int price;
  VI items;

  void read()
  {
    items.clear();
    int s;
    cin >> price >> s;
    for (int i = 0; i < s; i++) {
      int item;
      cin >> item;
      items.push_back(item-1);
    }
    sort(items.begin(), items.end());
  }

  bool operator<(const Bundle &b) const
  {
    if (items.size() != b.items.size())
      return items.size() < b.items.size();
    return items < b.items;
  }

  bool operator==(const Bundle &b) const
  {
    return items == b.items;
  }
};

Bundle bundle[MAX_M+1], bundle2[MAX_M+1];
int best[MAX_M+1];

// contains[i] = list of bundles containing item i
VI contains[MAX_N];


void compute(int index)
{
  best[index] = bundle[index].price;   // you can always just buy the bundle

  // now look at the sub-bundles
  set<int> parts;
  bool good = true;
  for (auto b : bundle[index].items) {
    int t = lower_bound(contains[b].begin(), contains[b].end(), index)
      - contains[b].begin();
    if (t == 0) {
      good = false;
      break;
    }
    assert(t < contains[b].size() && contains[b][t] == index);
    parts.insert(contains[b][t-1]);
  }

  int sum = 0;
  for (auto i : parts) {
    sum += best[i];
  }
  if (!good) sum = INF;

  best[index] = min(best[index], sum);
}

void solve()
{
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    bundle2[i].read();
  }

  // add artificial bundle
  bundle2[m].price = INF;
  bundle2[m].items.clear();
  for (int i = 0; i < n; i++) {
    bundle2[m].items.push_back(i);
  }
  m++;
  
  sort(bundle2, bundle2+m);

  // get rid of duplicates
  int k = 0, i, j;
  for (i = 0; i < m; i = j) {
    for (j = i+1; j < m && bundle2[i] == bundle2[j]; j++) {
      bundle2[i].price = min(bundle2[i].price, bundle2[j].price);
    }
    bundle[k++] = bundle2[i];
  }
    
  m = k;

  for (int i = 0; i < n; i++) {
    contains[i].clear();
  }
  for (int i = 0; i < m; i++) {
    for (auto b : bundle[i].items) {
      contains[b].push_back(i);
    }
  }

  fill(best, best+m, -1);
  for (int i = 0; i < m; i++) {
    compute(i);
  }
  cout << best[m-1] << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
