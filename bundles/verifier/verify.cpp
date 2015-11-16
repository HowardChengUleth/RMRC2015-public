#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

typedef set<int> SI;

const int MAXT = 50;
const int MAXN = 100;
const int MAXM = 100;
const int MAXP = 1000000;

void endline() {
  assert(cin.peek() == '\n');
  cin.ignore();
}

void space() {
  assert(cin.peek() == ' ');
  cin.ignore();
}

int getInt() {
  assert(!isspace(cin.peek()));
  int t;
  assert(cin >> t);
  return t;
}

void cross_check(const SI& a, const SI& b) {
  SI c;
  set_union(a.begin(), a.end(), b.begin(), b.end(),
	    inserter(c, c.begin()));
  assert(c.size() == max(a.size(),b.size()) || c.size() == a.size()+b.size());
}

int main() {
  int t = getInt();
  endline();

  assert(1 <= t && t <= MAXT);

  while (t--) {
    int n = getInt();
    space();
    int m = getInt();
    endline();

    assert(1 <= n && n <= MAXN);
    assert(1 <= m && m <= MAXM);

    vector<SI> bundles(m);
    unsigned long long tot = 0;

    for (int i = 0; i < m; ++i) {
      int p = getInt();
      space();
      assert(0 <= p && p <= MAXP);
      tot += p;

      int s = getInt();
      assert(1 <= s && s <= n);

      for (int k = 0; k < s; ++k) {
	space();
	int x = getInt();
	assert(1 <= x && x <= n);
	bundles[i].insert(x);
      }
      endline();

      assert(bundles[i].size() == s);

      for (int j = 0; j < i; ++j)
	cross_check(bundles[i], bundles[j]);
    }
    assert(tot <= 0x7fffffff);
  }

  assert(cin.peek() == EOF);

  return 0;
}
