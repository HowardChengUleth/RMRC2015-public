#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "checklib.h"

#define MAX_N 100

// I'm not checking if the puzzles are solvable...

void check_file(FILE *in)
{
  /* int N; */
  int /*i,*/ j, k;
  char **list = alloc_strs(1, 4);

  int freq[256];
  
  init_checklib();
  /* read_int(in, 1, &N);
  check_int_range(N, 1, MAX_N, "N");
  check_EOL(in); */

 /* for (i = 0; i < N; i++) { */
    freq['R'] = freq['G'] = freq['B'] = freq['Y'] = 0;
    
    for (j = 0; j < 4; j++) {
      read_str(in, 1, 4, list);
      check_EOL(in);
      if (strlen(list[0]) != 4) {
	fprintf(stderr, "Case %d: grid wrong size\n", get_case());
	exit(1);
      }

      for (k = 0; k < 4; k++) {
	if (strchr("RGBY", list[0][k]) == NULL) {
	  fprintf(stderr, "Case %d: illegal character\n", get_case());
	  exit(1);
	}
	freq[(int)list[0][k]]++;
      }
    }

    if (freq['R'] != 4 || freq['G'] != 4 || freq['B'] != 4 ||
	freq['Y'] != 4) {
      fprintf(stderr, "Case %d: wrong number of characters\n", get_case());
      exit(1);
    }

    /* inc_case();
  } */
  
  check_EOF(in);
  free_strs(list, 1);
}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
