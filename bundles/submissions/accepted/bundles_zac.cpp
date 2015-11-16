#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> VI;

VI high, cost;
vector<VI> bundle, bucket;

void process(int i) {
  int tot = 0;
  for (auto item : bundle[i]) {
    if (high[item] == -1) {
      tot = cost[i];
      high[item] = i;
    }
    else if (high[item] != i) {
      tot += cost[high[item]];
      for (auto j : bundle[high[item]]) high[j] = i;
    }
  }
  cost[i] = min(cost[i], tot);
}

int main() {
  int t;
  cin >> t;
  
  while (t--) {
    int n, m;
    cin >> n >> m;
    
    high.assign(n, -1);
    cost.resize(m+1);
    bundle.assign(m+1, VI());
    bucket.assign(n+1, VI());

    for (int i = 0; i < m; ++i) {
      int k, x;
      cin >> cost[i] >> k;
      bucket[k].push_back(i);
      while (k--) {
	cin >> x;
	bundle[i].push_back(x-1);
      }
    }

    for (int i = 0; i < n; bundle[m].push_back(i++));
    cost[m] = 1000000000;
    bucket[n].push_back(m);

    for (auto& i : bucket)
      for (auto j : i)
	process(j);

    cout << cost[m] << endl;
  }

  return 0;
}
