#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;

ll read_double()
{
  ll a, b;
  char ch;

  cin >> a >> ch >> b;
  assert(ch == '.');
  return a * 10 + b;
}

void solve()
{
  int R, P, D;
  cin >> R >> P >> D;

  string name[20];
  ll w[20], p[20];
  int main_ing = -1;
  for (int i = 0; i < R; i++) {
    cin >> name[i];
    w[i] = read_double();
    p[i] = read_double();
    if (p[i] == 1000) main_ing = i;
  }
  assert(main_ing >= 0);

  ll main_num = D*w[main_ing];
  ll main_denom = P;

  for (int i = 0; i < R; i++) {
    ll num = main_num * p[i];
    ll denom = main_denom * 1000;
    ll rounded = num / denom + ((num % denom >= (denom+1)/2) ? 1 : 0);
    cout << name[i] << ' ' << rounded / 10 << '.' << rounded % 10 << endl;
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
