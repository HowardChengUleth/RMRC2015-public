#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "checklib.h"

void check_file(FILE *in)
{
  int n;
  int cases = 0;

  init_checklib();
  read_int(in, 1, &n);
  check_EOL(in);
  while (n != 0) {
    check_int_range(n, 1, INT_MAX, "n");
    cases++;
    read_int(in, 1, &n);
    check_EOL(in);
  }
  check_EOF(in);
  if (cases > 1000) {
    fprintf(stderr, "Too many cases: %d\n", cases);
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
