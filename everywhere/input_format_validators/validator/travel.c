#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "checklib.h"

void check_file(FILE *in)
{
  int T, n;
  int i, j, k;
  char **list = alloc_strs(100, 20);
  
  init_checklib();
  read_int(in, 1, &T);
  check_EOL(in);
  check_int_range(T, 1, 50, "T");

  for (i = 0; i < T; i++) {
    read_int(in, 1, &n);
    check_EOL(in);
    check_int_range(n, 1, 100, "n");
    for (j = 0; j < n; j++) {
      read_str(in, 1, 20, list);
      for (k = 0; k < strlen(list[0]); k++) {
	if (!islower(list[0][k])) {
	  fprintf(stderr, "Line %d: bad name '%s'\n", get_line(), list[0]);
	  exit(1);
	}
      }
      if (strlen(list[0]) == 0) {
	fprintf(stderr, "Line %d: empty name\n", get_line());
	exit(1);
      }
      check_EOL(in);
    }
    inc_case();
  }

  check_EOF(in);
  free_strs(list, 100);
}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
