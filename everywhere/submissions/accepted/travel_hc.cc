#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

void solve()
{
  set<string> S;
  int n;

  cin >> n;
  while (n--) {
    string name;
    cin >> name;
    S.insert(name);
  }
  cout << S.size() << endl;
    
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
  
  return 0;
}
