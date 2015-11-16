// idea: if all the 1's are on the same row or same column, then the ones
// "shown" are pressed, and no one else.
//
// if there are multiple rows and columns involved, then each of the corners
// of the "rectangles" formed may be involved.  In fact all of them are
// "I".


#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

void solve()
{
  int r, c;
  cin >> r >> c;

  char grid[10][10];
  set<int> rows, cols;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> grid[i][j];
      if (grid[i][j] == '1') {
	rows.insert(i);
	cols.insert(j);
      }
    }
  }

  if (rows.size() <= 1 || cols.size() <= 1) {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
	cout << ((grid[i][j] == '1') ? 'P' : 'N');
      }
      cout << endl;
    }
    goto done;
  }

  for (auto i : rows) {
    for (auto j : cols) {
      if (grid[i][j] != '1') {
	cout << "impossible" << endl;
	goto done;
      }
    }
  }
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cout << ((grid[i][j] == '1') ? 'I' : 'N');
    }
    cout << endl;
  }

 done:
  cout << string(10, '-') << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) 
    solve();
    
  return 0;
}
