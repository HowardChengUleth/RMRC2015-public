#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
  int n;
  while (cin >> n && n > 0) {
    // a couple of special cases to deal with when n-3 <= 0
    if (n <= 2) {
      cout << "No such base" << endl;
      continue;
    } else if (n == 3) {
      cout << 4 << endl;
      continue;
    }

    n -= 3;
    long long best = INT_MAX;
    best *= 2;
    
    for (long long b = 1; b*b <= n; b++) {
      if (n % b == 0) {
	if (b >= 4) {
	  best = min(best, b);
	}
	if (n/b >= 4) {
	  best = min(best, n/b);
	}
      }
    }
    if (best < INT_MAX) {
      cout << best << endl;
    } else {
      cout << "No such base" << endl;
    }
  }
  
  return 0;
}
