#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

typedef vector<string> vs;

int value(const string &s)
{
  if (s == "upper") return 2;
  if (s == "middle") return 1;
  if (s == "lower") return 0;
  return -1;
}

struct Person
{
  string name;
  vs cl;

  void read()
  {
    cin >> name;
    name.pop_back();

    string classname, garbage;
    cin >> classname >> garbage;
    replace(classname.begin(), classname.end(), '-', ' ');
    istringstream iss(classname);

    string s;
    while (iss >> s) {
      cl.push_back(s);
    }
    reverse(cl.begin(), cl.end());
  }

  bool operator<(const Person &p) const
  {
    for (int i = 0; i < max(cl.size(), p.cl.size()); i++) {
      int val1 = value((i < cl.size()) ? cl[i] : "middle");
      int val2 = value((i < p.cl.size()) ? p.cl[i] : "middle");
      if (val1 != val2) {
	return val1 > val2;
      }
    }
    return name < p.name;
  }
  
};

void solve()
{
  int n;
  cin >> n;

  Person p[100];
  for (int i = 0; i < n; i++) {
    p[i].read();
  }
  
  sort(p, p+n);
  
  for (int i = 0; i < n; i++) {
    cout << p[i].name << endl;
  }
  cout << string(30,'=') << endl;
  
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
  
  return 0;
}
