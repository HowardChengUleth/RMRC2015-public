#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "checklib.h"

const int MAX_T = 500;
const int MIN_N = 2;
const int MAX_N = 10;
const int MAX_VOTE = 50000;

void check_file(FILE *in)
{
  int n;
  int T, i, j;
  int vote, total;
  
  init_checklib();
  read_int(in, 1, &T);
  check_int_range(T, 1, MAX_T, "T");
  check_EOL(in);

  for (i = 0; i < T; i++) {
    read_int(in, 1, &n);
    check_int_range(n, MIN_N, MAX_N, "n");
    check_EOL(in);
    total = 0;
    for (j = 0; j < n; j++) {
      read_int(in, 1, &vote);
      check_int_range(vote, 0, MAX_VOTE, "vote");
      check_EOL(in);
      total += vote;
    }

    if (total == 0) {
      fprintf(stderr, "Case %d: no vote for anyone\n", get_case());
      exit(1);
    }
    inc_case();
  }
  check_EOF(in);
}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
