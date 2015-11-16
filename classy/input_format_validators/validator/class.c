#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "checklib.h"

#define MAX_T 500
#define MAX_N 100
#define MAX_NAME 30
#define MAX_CLASS 10
#define MAX_CLASS_LEN (6*MAX_CLASS + MAX_CLASS-1)

void check_case(FILE *in)
{
  int n, i, j;
  char **list = alloc_strs(3, MAX_CLASS_LEN);
  char names[MAX_N][MAX_NAME+1];

  read_int(in, 1, &n);
  check_int_range(n, 1, MAX_N, "n");
  check_EOL(in);

  for (i = 0; i < n; i++) {
    read_str(in, 3, MAX_CLASS_LEN, list);
    check_EOL(in);
    int name_len = strlen(list[0]);
    if (list[0][name_len-1] != ':') {
      fprintf(stderr, "Case %d: name \"%s\" does not end with :\n",
	      get_case(), list[0]);
      exit(1);
    }
    list[0][--name_len] = 0;
    if (name_len > MAX_NAME) {
      fprintf(stderr, "Case %d: name \"%s\" too long\n",
	      get_case(), list[0]);
      exit(1);
    }      
    strcpy(names[i], list[0]);

    for (j = 0; j < i; j++) {
      if (!strcmp(names[i], names[j])) {
	fprintf(stderr, "Case %d: name \"%s\" duplicated\n",
		get_case(), list[0]);
	exit(1);
      }
    }

    if (list[1][0] == '-' || list[1][strlen(list[1])-1] == '-') {
      fprintf(stderr, "Case %d: bad class name \"%s\"\n", get_case(),
	      list[1]);
      exit(1);
    }
    for (j = 1; j < strlen(list[1])-1; j++) {
      if (list[1][j] == '-' && list[1][j+1] == '-') {
	fprintf(stderr, "Case %d: bad class name \"%s\"\n", get_case(),
		list[1]);
	exit(1);
      }
    }

    int count = 0;
    char *ptr;
    for (ptr = list[1]; (ptr = strtok(ptr, "-")); ptr = 0) {
      if (strcmp(ptr, "upper") && strcmp(ptr, "middle") &&
	  strcmp(ptr, "lower")) {
	fprintf(stderr, "Case %d: bad class name \"%s\"\n", get_case(),
		ptr);
	exit(1);
      }
      count++;
    }
    if (count <= 0 || count > MAX_CLASS) {
      fprintf(stderr, "Case %d: wrong number of classes\n", get_case());
      exit(1);
    }


    if (strcmp(list[2], "class")) {
      fprintf(stderr, "Case %d: last word is not \"class\"\n",
	      get_case());
      exit(1);
    }      
  }


  free_strs(list, 3);
}

void check_file(FILE *in)
{
  int T;
  int i;
  
  init_checklib();
  read_int(in, 1, &T);
  check_EOL(in);
  check_int_range(T, 1, MAX_T, "T");

  for (i = 0; i < T; i++) {
    check_case(in);
    inc_case();
  }

  check_EOF(in);
}

int main(int argc, char *argv[])
{
  driver(argc, argv, check_file);
  return 0;
}
