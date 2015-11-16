#include <iostream>

using namespace std;

int main()
{
  int n;
  while (cin >> n && n > 0) {
    int b = 4;
    while (n % b != 3 && b < n) b++;
    if (n % b == 3) {
      cout << b << endl;
    } else {
      cout << "No such base" << endl;
    }
  }
  
  return 0;
}
