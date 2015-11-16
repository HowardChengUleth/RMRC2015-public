#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

#define MAXC 10

using namespace std;

struct person {
  string name, stat;

  bool operator<(const person& rhs) const {
    if (stat == rhs.stat)
      return name < rhs.name;

    for (int i = 0; i < MAXC; ++i)
      if (stat[i] > rhs.stat[i]) return true;
      else if (stat[i] < rhs.stat[i]) return false;
    assert(false);
  }
};

int sign(char c) {
  if (c == 'u') return 1;
  else if (c == 'l') return -1;
  else return 0;
}

string getstat() {
  string s;

  cin >> ws;
  while (cin.peek() != 'c') {
    s.insert(s.begin(), cin.peek());
    while (cin.peek() != '-' && cin.peek() != ' ') cin.ignore();
    cin.ignore();
  }
  string d;
  cin >> d;

  while (s.length() < MAXC) s += 'm';
  
  return s;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    
    vector<person> v(n);

    for (int i = 0; i < n; ++i) {
      cin >> v[i].name;
      v[i].name.pop_back();
      v[i].stat = getstat();
    }

    sort(v.begin(), v.end());

    for (auto &p : v) cout << p.name << endl;
    cout << string(30, '=') << endl;
  }
}
