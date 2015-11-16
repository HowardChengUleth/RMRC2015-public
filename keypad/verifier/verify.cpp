#include <iostream>
#include <string>
#include <cassert>
#include <cctype>

using namespace std;

const int MAXT = 200;
const int MAXD = 10;

void eat(char c) {
  assert(cin.peek() == c);
  cin.ignore();
}

string getstr() {
  assert(!cin.eof() && !isspace(cin.peek()));
  string s;
  assert(cin >> s);
  return s;
}

int getint() {
  assert(isdigit(cin.peek()));
  int t;
  assert(cin >> t);
  return t;
}

int main() {
  int t = getint();
  eat('\n');
  assert(1 <= t && t <= MAXT);

  while (t--) {
    int r = getint();
    eat(' ');
    int c = getint();
    eat('\n');

    assert(1 <= r && r <= MAXD && 1 <= c && c <= MAXD);

    while (r--) {
      string s = getstr();
      eat('\n');
      assert(s.length() == c);
      for (auto x : s) assert(x == '0' || x == '1');
    }
  }
  assert(cin.peek() == EOF);
  
  return 0;
}
