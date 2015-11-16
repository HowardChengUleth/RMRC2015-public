#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "checklib.h"

const int MAX_T = 200;
const int MAX_DIM = 10;

void check_file(FILE *in)
{
  int T, r, c, params[2];
  int i, j, k;
  char **list = alloc_strs(1, MAX_DIM);
  
  init_checklib();
  read_int(in, 1, &T);
  check_EOL(in);
  check_int_range(T, 1, MAX_T, "T");

  for (i = 0; i < T; i++) {
    read_int(in, 2, params);
    r = params[0];  c = params[1];
    check_int_range(r, 1, MAX_DIM, "r");
    check_int_range(c, 1, MAX_DIM, "c");
    check_EOL(in);

    for (j = 0; j < r; j++) {
      read_str(in, 1, c, list);
      for (k = 0; k < strlen(list[0]); k++) {
	if (list[0][k] != '0' && list[0][k] != '1') {
	  fprintf(stderr, "Line %d: bad line '%s'\n", get_line(), list[0]);
	  exit(1);
	}
      }
      if (strlen(list[0]) != c) {
	fprintf(stderr, "Line %d: wrong length\n", get_line());
	exit(1);
      }
      check_EOL(in);
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
