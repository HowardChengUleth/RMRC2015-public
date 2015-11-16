#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "checklib.h"

#define MAX_T 500
#define MIN_MAG -100
#define MAX_MAG 100
#define MIN_R 1
#define MAX_R MAX_MAG

void check_file(FILE *in)
{
  int T, i, j, k;
  int s[2][7];
  
  init_checklib();
  read_int(in, 1, &T);
  check_int_range(T, 1, MAX_T, "T");
  check_EOL(in);

  for (i = 0; i < T; i++) {
    read_int(in, 7, s[0]);
    check_EOL(in);
    read_int(in, 7, s[1]);
    check_EOL(in);

    for (j = 0; j < 2; j++) {
      for (k = 0; k < 7; k++) {
	if (k == 3) {
	  check_int_range(s[j][k], MIN_R, MAX_R, "radius");
	} else {
	  check_int_range(s[j][k], MIN_MAG, MAX_MAG, "sphere");
	}
      }
    }

    int dx = s[0][0] - s[1][0];
    int dy = s[0][1] - s[1][1];
    int dz = s[0][2] - s[1][2];
    int r = s[0][3] + s[1][3];

    if (dx*dx + dy*dy + dz*dz <= r*r) {
      fprintf(stderr, "Case %d: spheres are touching initially\n", get_case());
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
