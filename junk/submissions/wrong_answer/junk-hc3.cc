// this version tries to use integer arithmetic as much as possible
//
// add +/- 0.02 randomly at the end

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <cstdlib>

using namespace std;

void solve()
{
  int x1, y1, z1, r1, vx1, vy1, vz1;
  int x2, y2, z2, r2, vx2, vy2, vz2;

  // formula is basically
  //
  // |p1(t) - p2(t)|^2 <= (r1+r2)^2

  cin >> x1 >> y1 >> z1 >> r1 >> vx1 >> vy1 >> vz1;
  cin >> x2 >> y2 >> z2 >> r2 >> vx2 >> vy2 >> vz2;
  
  int dx = x1-x2, dy = y1-y2, dz=z1-z2;
  int dvx = vx1-vx2, dvy = vy1-vy2, dvz = vz1-vz2;

  // (dx + t*vx)^2 + (dy + t*vy)^2 + (dz + t*vz)^2 <= (r1+r2)^2
  //
  // convert to at^2 + bt + c <= 0
  int a = dvx*dvx + dvy*dvy + dvz*dvz,
    b = 2*(dx*dvx + dy*dvy + dz*dvz),
    c = dx*dx + dy*dy + dz*dz - (r1+r2)*(r1+r2);
  int disc = b*b - 4*a*c;
  double root1;
  
  if (a == 0) {
    // not quadratic 
    // i.e. exactly the same

    // note that in this case b is also 0.
    
    assert(b == 0);
    
    // not linear either, so either c <= 0 (so we always intersect),
    // or c > 0 and we never intersect.  But c <= 0 is not an option
    // because the spheres don't touch initially

    goto no;
  }

  // quadratic case
  if (disc < 0) {
    goto no;
  }

  if ((b >= 0 && disc < b*b)) {
    // happened before start
    goto no;
  }

  // can't straddle because no collision at the start
  assert(b < 0 && b*b > disc);

  root1 = (-b - sqrt(disc))/(2*a);

  root1 += (rand() % 5 - 2)/100.0;

  cout << fixed << setprecision(3) << root1 << endl;
  return;
  
 no:
  cout << "No collision" << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
