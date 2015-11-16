#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include "checklib.h"

const int MAX_N = 1000;
const int MAX_R = 20;
const int MAX_P = 12;
const int MAX_D = 1000;
const int MAX_LEN = 20;

void check_file(FILE *in)
{
  int N, R, P, D, params[3];
  int i, j, k;
  char **list = alloc_strs(1, MAX_LEN);
  double dparams[2];
  int maincount = 0;
  
  init_checklib();
  read_int(in, 1, &N);
  check_EOL(in);
  check_int_range(N, 1, MAX_N, "N");

  for (i = 0; i < N; i++) {
    maincount = 0;
    
    read_int(in, 3, params);
    R = params[0];  P = params[1];  D = params[2];
    check_EOL(in);
    check_int_range(R, 1, MAX_R, "R");
    check_int_range(P, 1, MAX_P, "P");
    check_int_range(D, 1, MAX_D, "D");
    
    for (j = 0; j < R; j++) {
      read_str(in, 1, MAX_LEN, list);
      for (k = 0; k < strlen(list[0]); k++) {
	if (!isalpha(list[0][k])) {
	  fprintf(stderr, "Line %d: bad ingredient '%s'\n", get_line(), list[0]);
	  exit(1);
	}
      }
      if (strlen(list[0]) == 0) {
	fprintf(stderr, "Line %d: empty ingredient\n", get_line());
	exit(1);
      }
      match_char(in, ' ');
      
      read_double(in, 2, -1, dparams);
      if (dparams[0] < 0 || dparams[1] < 0) {
	fprintf(stderr, "Line %d: negative values %.1f %.1f\n", get_line(),
		dparams[0], dparams[1]);
	exit(1);
      }
      if (fabs(dparams[1] - 100.0) < 0.001) {
	maincount++;
      }
      check_EOL(in);
    }
    if (maincount != 1) {
      fprintf(stderr, "Case %d: found %d main ingredients.\n", get_case(),
	      maincount);
      exit(1);
    }
    inc_case();
  }

  check_EOF(in);
  free_strs(list, 1);
}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
