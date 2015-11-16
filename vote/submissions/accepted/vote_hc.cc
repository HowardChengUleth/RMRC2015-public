#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

void solve()
{
  int n;
  cin >> n;

  int vote[10];
  for (int i = 0; i < n; i++) {
    cin >> vote[i];
  }

  int winner = max_element(vote, vote+n) - vote;
  int num_winner = count(vote, vote+n, vote[winner]);
  if (num_winner > 1) {
    cout << "no winner" << endl;
    return;
  }

  int total = accumulate(vote, vote+n, 0);
  if (vote[winner] > total/2) {
    cout << "majority winner ";
  } else {
    cout << "minority winner ";
  }
  cout << winner+1 << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
