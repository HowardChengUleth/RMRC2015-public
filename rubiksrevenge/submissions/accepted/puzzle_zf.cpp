#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <cassert>

using namespace std;

typedef unsigned int UI;

map<UI, int> rem;

int bits[256];
string ch = "RGBY";
UI goal = 0xffaa5500;
int depth = 6;

UI rot_r(UI s, int r) {
  r <<= 3;
  
  UI row = (s>>r)&0xff;
  s ^= (row << r);

  row = (row >> 2) | ((row&3) << 6);

  return s|(row<<r);
}

UI rot_c(UI s, int c) {
  c <<= 1;

  UI col = (s>>c)&0x03030303;

  s ^= (col << c);
  
  col = (col >> 8) | ((col&3) << 24);

  return s|(col<<c);
}

void endgame() {
  rem[goal] = 0;
  queue<UI> q;
  q.push(goal);

  while (!q.empty()) {
    UI curr = q.front();
    q.pop();

    int d = rem[curr];
    for (int i = 0; i < 4; ++i) {
      UI next = curr;
      for (int j = 0; j < 3; ++j) {
	next = rot_r(next, i);
	if (j == 1) continue;
	if (rem.find(next) == rem.end()) {
	  rem[next] = d+1;
	  if (d+1 < depth) q.push(next);
	}
      }

      next = curr;
      for (int j = 0; j < 3; ++j) {
	next = rot_c(next, i);
	if (j == 1) continue;
	if (rem.find(next) == rem.end()) {
	  rem[next] = d+1;
	  if (d+1 < depth) q.push(next);
	}
      }
    }
  }
}

void dump(UI s) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      cout << ch[s&0x3];
      s >>= 2;
    }
    cout << endl;
  }
  cout << endl;
}

int solve(UI start) {
  if (rem.find(start) != rem.end()) return rem[start];
  
  int best = 1000;
  
  queue<UI> q;
  map<UI, int> m;
  q.push(start);
  m[start] = 0;

  while (!q.empty()) {
    UI curr = q.front();
    q.pop();

    int d = m[curr];

    for (int i = 0; i < 4; ++i) {
      UI next = curr;

      for (int j = 0; j < 3; ++j) {
	next = rot_r(next, i);
	if (j == 1) continue;

	if (rem.find(next) != rem.end()) return d+1+depth;

	if (m.find(next) != m.end()) continue;
	
	if (d + depth + 2 >= best) continue;

	m[next] = d+1;
	q.push(next);
      }

      next = curr;

      for (int j = 0; j < 3; ++j) {
	next = rot_c(next, i);
	if (j == 1) continue;

	if (rem.find(next) != rem.end()) return d+1+depth;
	  
	if (m.find(next) != m.end()) continue;
	
	if (d + depth + 2 >= best) continue;

	m[next] = d+1;
	q.push(next);
      }
    }
  }

  assert(false);
}

int main() {
  for (int i = 0; i < 4; ++i) bits[ch[i]] = i;

  endgame();

  int t;
  char g[4][5];
  
  for (int i = 0; i < 4; ++i) cin >> g[i];
  UI start = 0;
  for (int i = 3; i >= 0; --i)
      for (int j = 3; j >= 0; --j)
	start = (start<<2)|bits[g[i][j]];
  
  cout << solve(start) << endl;
  
  return 0;
}
