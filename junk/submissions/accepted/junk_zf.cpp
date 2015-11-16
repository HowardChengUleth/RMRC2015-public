#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long LL;

struct point {
  LL x, y, z;
  point(LL xx = 0, LL yy = 0, LL zz = 0) : x(xx), y(yy), z(zz) {}
  point operator+(const point& rhs) const {
    return point(x+rhs.x, y+rhs.y, z+rhs.z);
  }
  point operator-(const point& rhs) const {
    return point(x-rhs.x, y-rhs.y, z-rhs.z);
  }
};

point p, q, vp, vq;
LL rp, rq;

LL dot(const point& p, const point& q) {
  return p.x*q.x + p.y*q.y + p.z*q.z;
}

bool collide(double& h) {
  point u = p-q, v = vp-vq;
  LL r = rp+rq;
  
  LL a = dot(v,v), b = 2*dot(u,v), c = dot(u,u) - r*r;

  if (a == 0) {
    if (b*c >= 0) return false;
    h = -double(c)/double(b);
    return true;
  }

  LL disc = b*b - 4*a*c;
  if (disc < 0 || b > 0 || b*b < disc) return false;
  h = (-b - sqrt(double(disc)))/(2*a);
  return true;
}

void read(point& p) { cin >> p.x >> p.y >> p.z; }

int main() {
  cout.setf(ios::fixed);
  cout.precision(3);

  int t;
  cin >> t;
  while (t--) {
    read(p);
    cin >> rp;
    read(vp);

    read(q);
    cin >> rq;
    read(vq);

    double h;
    if (!collide(h)) cout << "No collision" << endl;
    else cout << h << endl;
  }
  return 0;
}
