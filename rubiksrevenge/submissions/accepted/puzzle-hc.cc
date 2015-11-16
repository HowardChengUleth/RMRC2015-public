#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

typedef unsigned int uint;

struct State
{
  string s;
  
  void read()
  {
    char c;

    s = "";
    for (int i = 0; i < 16; i++) {
      cin >> c;
      s += c;
    }
  }

  void goal()
  {
    s = "RRRRGGGGBBBBYYYY";
  }

  void rotate_r(int row, int dir)
  {
    int p = row*4;

    if (dir > 0) {
      char t = s[p];
      s[p] = s[p+1];
      s[p+1] = s[p+2];
      s[p+2] = s[p+3];
      s[p+3] = t;
    } else {
      char t = s[p+3];
      s[p+3] = s[p+2];
      s[p+2] = s[p+1];
      s[p+1] = s[p];
      s[p] = t;
    }
  }

  void rotate_c(int col, int dir)
  {
    int p = col;
    if (dir > 0) {
      char t = s[p];
      s[p] = s[p+4];
      s[p+4] = s[p+8];
      s[p+8] = s[p+12];
      s[p+12] = t;
    } else {
      char t = s[p+12];
      s[p+12] = s[p+8];
      s[p+8] = s[p+4];
      s[p+4] = s[p];
      s[p] = t;
    }
  }

  bool operator==(const State &s2) const
  {
    return s == s2.s;
  }

  bool operator<(const State &s2) const
  {
    return s < s2.s;
  }
};

namespace std {
  template<> struct hash<State> {
    size_t operator()(const State &s) const {
      return hash<string>()(s.s);
    }
  };
}

bool expand(State s, int curr_d, queue<State> &q,
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
	  cout << curr_d+1+dist2[next] << endl;
	  return false;
	}
      }

      next = s;
      next.rotate_c(i, d);

      if (dist.find(next) == dist.end()) {
	dist[next] = curr_d+1;
	q.push(next);
	if (dist2.find(next) != dist2.end()) {
	  cout << curr_d+1+dist2[next] << endl;
	  return false;
	}
      }
    }
  }

  return true;
}

void solve()
{
  State start, goal;

  start.read();
  goal.goal();

  if (start == goal) {
    cout << 0 << endl;
    return;
  }
  
  unordered_map<State, int> dist_f, dist_b;
  queue<State> q_f, q_b;
  int d_f, d_b;
  
  q_f.push(start);   dist_f[start] = 0;
  q_b.push(goal);    dist_b[goal] = 0;
  d_f = d_b = 0;

  while (!q_f.empty() || !q_b.empty()) {

    // let's move forward by 1 step
    while (!q_f.empty() && dist_f[q_f.front()] == d_f) {
      State s = q_f.front();  q_f.pop();
      if (!expand(s, d_f, q_f, dist_f, dist_b)) {
	return;
      }
    }
    d_f++;

    // let's move backward by 1 step
    while (!q_b.empty() && dist_b[q_b.front()] == d_b) {
      State s = q_b.front();  q_b.pop();
      if (!expand(s, d_b, q_b, dist_b, dist_f)) {
	return;
      }
    }
    d_b++;
  }
}

int main()
{
  // int N;
  // cin >> N;
  // while (N--)
    solve();

  return 0;
}
