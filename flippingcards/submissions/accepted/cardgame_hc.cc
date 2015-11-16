#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// idea:
//
// Let the 2n faces be nodes in a graph, and each card is represented by an
// undirected edge connecting the two faces.  There can be self loops and
// multiple edges between nodes.
//
// Faces that are not in the same connected component do not interact with
// each other and can be treated independently.
//
// In a connected component, there is no issue unless there is a cycle (self
// loop counts as a cycle).  A single cycle is okay (because you start from one
// of those edges), but not if there is more.

struct UnionFind
{
  vector<int> uf;
  vector<int> has_cycle;  // count whether there are 0, 1, >1 cycles
                          // note: >1 counts are not exact
  UnionFind(int n) : uf(n), has_cycle(n,0) {
    for (int i = 0; i < n; i++) uf[i] = i;
  }
  
  int find(int x) {
    return (uf[x] == x) ? x : (uf[x] = find(uf[x]));
  }
  
  bool merge(int x, int y) {
    int res1 = find(x), res2 = find(y);
    if (res1 == res2) {
      has_cycle[res1]++;
    }
    
    if (res1 == res2) return false;
    uf[res2] = res1;
    has_cycle[res1] += has_cycle[res2];
    return true;
  }
};


void solve()
{
  int n;
  cin >> n;

  UnionFind uf(2*n);
  
  for (int i = 0; i < n; i++) {
    int p, q;
    cin >> p >> q;
    uf.merge(p-1, q-1);
  }

  bool good = true;
  for (int i = 0; i < 2*n && good; i++) {
    good &= uf.has_cycle[i] <= 1;
  }
  cout << (good ? "possible" : "impossible") << endl;

}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
