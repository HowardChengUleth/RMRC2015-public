#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "checklib.h"

#define MAX_T 50
#define MAX_N 100
#define MAX_M 150
#define MAX_P 1000000

void check_case(FILE *in)
{
  int params[MAX_M];
  int n, m;
  int i, j;
  
  read_int(in, 2, params);
  n = params[0];
  m = params[1];
  check_int_range(n, 1, MAX_N, "n");
  check_int_range(m, 1, MAX_M, "m");
  check_EOL(in);

  char appeared[MAX_N+1];
  for (j = 1; j <= n; j++) {
    appeared[j] = 0;
  }
  
  for (i = 0; i < m; i++) {
    int p, s;
    read_int(in, 2, params);
    p = params[0];
    s = params[1];
    check_int_range(p, 1, MAX_P, "p");
    check_int_range(s, 1, n, "s");
    match_char(in, ' ');
    read_int(in, s, params);

    char used[MAX_N+1];
    for (j = 1; j <= n; j++) {
      used[j] = 0;
    }
    
    for (j = 0; j < s; j++) {
      check_int_range(params[j], 1, n, "si");
      if (used[params[j]]) {
	fprintf(stderr, "Case %d: bundle %d has duplicate items\n",
		get_case(), i+1);
	exit(1);
      }
      used[params[j]] = 1;
      appeared[params[j]] = 1;
    }

    check_EOL(in);
  }

  for (j = 1; j <= n; j++) {
    if (!appeared[j]) {
      fprintf(stderr, "Case %d: item %d does not appear in any bundle.\n",
	      get_case(), j);
      exit(1);
    }
  }
}

void check_file(FILE *in)
{
  int T;
  int i;
  
  init_checklib();
  read_int(in, 1, &T);
  check_int_range(T, 1, MAX_T, "T");
  check_EOL(in);

  for (i = 0; i < T; i++) {
    check_case(in);
  }
  check_EOF(in);
}

int main(int argc, char *argv[])
{
  return driver(argc, argv, check_file);
}
