#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

void solve()
{
  int R, P, D;
  cin >> R >> P >> D;

  string name[20];
  double w[20], p[20];
  int main_ing = -1;
  for (int i = 0; i < R; i++) {
    cin >> name[i] >> w[i] >> p[i];
    if (fabs(p[i]-100.0) < 0.01) main_ing = i;
  }
  assert(main_ing >= 0);

  double main_weight = (double)D/P * w[main_ing];
  for (int i = 0; i < R; i++) {
    cout << name[i] << ' ' << fixed << setprecision(1)
	 << main_weight * p[i] / 100.0 << endl;
  }
  cout << string(40, '-') << endl;
  
}

int main()
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cout << "Recipe # " << i << endl;
    solve();
  }

  return 0;
}
