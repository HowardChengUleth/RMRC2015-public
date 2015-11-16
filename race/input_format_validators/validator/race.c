#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "checklib.h"

const int MAX_N = 20;
const int MAX_T = 1440;

void check_file(FILE *in)
{
  int n, T;
  int params[50];
  int i, j;
  
  init_checklib();
  read_int(in, 2, params);
  n = params[0];
  T = params[1];
  check_int_range(n, 1, MAX_N, "n");
  check_int_range(T, 1, MAX_T, "T");
  check_EOL(in);
  for (i = 0; i < n; i++) {
    int p, t, d;
    read_int(in, 3, params);
    p = params[0];  t = params[1];  d = params[2];
    check_int_range(p, 1, 100, "p");
    check_int_range(t, 1, MAX_T, "t");
    check_int_range(d, -1, MAX_T, "d");
    check_EOL(in);
  }

  for (i = 0; i < n+2; i++) {
    read_int(in, n+2, params);
    for (j = 0; j < n+2; j++) {
      if (i == j) {
	check_int_range(params[j], 0, 0, "distance");
      } else {
	check_int_range(params[j], 0, MAX_T, "distance");
      }
    }
    check_EOL(in);
  }
  check_EOF(in);

}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
