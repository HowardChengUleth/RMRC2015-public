#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int uint;

struct State
{
  // represent the colours as a 2-bit value, list them in row major order.
  // all together 32 bit
  uint rep;
  
  void read()
  {
    const string colours = "RGBY";
    char c;

    rep = 0;
    for (int i = 0; i < 16; i++) {
      cin >> c;
      rep <<= 2;
      rep += colours.find(c);
    }
  }

  void write()
  {
    const string colours = "RGBY";

    for (int i = 0; i < 16; i++) {
      cout << colours[(rep >> (15-i)*2) & 0x3];
      if (i % 4 == 3) cout << endl;
    }
  }

  void goal()
  {
    rep = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
	rep <<= 2;
	rep += i;
      }
    }
  }

  void rotate_r(int row, int dir)
  {
    int shift = (3-row)*8;
    uint r = (rep >> shift) & 0xFF;
    if (dir > 0) {
      r = (r >> 2) | ((r & 3) << 6);
    } else {
      r = ((r << 2) & 0xFF) | (r >> 6);
    }
    rep = (~(0xFF << shift) & rep) | (r << shift);
  }

  void rotate_c(int col, int dir)
  {
    if (dir > 0) {
      int shift = (3-col)*2;
      uint temp = (rep >> shift) & 0x3;
      for (int r = 3; r >= 0; r--) {
	int d_shift = (3-r)*8 + shift;
	uint from = (r > 0) ? ((rep >> (d_shift + 8)) & 0x3) : temp;
	rep = (~(0x3 << d_shift) & rep) | (from << d_shift);
      }
    } else {
      int shift = (3-col)*2 + 24;
      uint temp = (rep >> shift) & 0x3;
      for (int r = 0; r < 4; r++) {
	int d_shift = shift - r*8;
	uint from = (r < 3) ? ((rep >> (d_shift - 8)) & 0x3) : temp;
	rep = (~(0x3 << d_shift) & rep) | (from << d_shift);
      }
    }
  }

  bool operator==(const State &s) const
  {
    return rep == s.rep;
  }

  bool operator<(const State &s) const
  {
    return rep < s.rep;
  }
};

namespace std {
  template<> struct hash<State> {
    size_t operator()(const State &s) const {
      return s.rep;
    }
  };
}

int expand(State s, int curr_d, queue<State> &q,
	    unordered_map<State, int> &dist,
	    unordered_map<State, int> &dist2)
{
  for (int i = 0; i < 4; i++) {
    for (int d = 0; d < 2; d++) {
      State next = s;
      next.rotate_r(i, d);

      if (dist.find(next) == dist.end()) {
	dist[next] = curr_d+1;
	q.push(next);
	if (dist2.find(next) != dist2.end()) {
	  return curr_d+1+dist2[next];
	}
      }

      next = s;
      next.rotate_c(i, d);

      if (dist.find(next) == dist.end()) {
	dist[next] = curr_d+1;
	q.push(next);
	if (dist2.find(next) != dist2.end()) {
	  return curr_d+1+dist2[next];
	}
      }
    }
  }

  return -1;
}

unordered_map<State, int> dist_b;

void init()
{
  State goal;
  goal.goal();
  
  queue<State> q_b;
  q_b.push(goal);    dist_b[goal] = 0;

  unordered_map<State, int> dist_f;
  
  // let's move backward by 1 step
  while (!q_b.empty() && dist_b[q_b.front()] <= 5) {
    State s = q_b.front();  q_b.pop();
    expand(s, dist_b[s], q_b, dist_b, dist_f);
  }
}

void solve()
{
  State start;
  start.read();

  unordered_map<State, int> dist_f;
  queue<State> q_f;
  int df = 0;
  q_f.push(start);   dist_f[start] = 0;
  
  while (!q_f.empty()) {

    // let's move forward by 1 step
    while (!q_f.empty() && dist_f[q_f.front()] == df) {
      State s = q_f.front();  q_f.pop();
      if (dist_b.find(s) != dist_b.end()) {
	cout << dist_b[s] + dist_f[s] << endl;
	return;
      }
      
      expand(s, dist_f[s], q_f, dist_f, dist_b);
    }

    df++;
  }

  assert(false);
}

int main()
{
  init();
  
  // int N;
  // cin >> N;
  // while (N--)
    solve();

  return 0;
}
