#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "checklib.h"

const int MAX_N = 50000;
const int MAX_T = 10;

void check_file(FILE *in)
{
  int T, n;
  int params[2];
  int i, j;
  
  init_checklib();
  read_int(in, 1, &T);
  check_int_range(T, 1, MAX_T, "T");
  check_EOL(in);

  for (i = 0; i < T; i++) {
    read_int(in, 1, &n);
    check_int_range(n, 1, MAX_N, "n");
    check_EOL(in);
    for (j = 0; j < n; j++) {
      read_int(in, 2, params);
      check_int_range(params[0], 1, 2*n, "p_i");
      check_int_range(params[1], 1, 2*n, "q_i");
      check_EOL(in);
    }
  }

  check_EOF(in);

}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
