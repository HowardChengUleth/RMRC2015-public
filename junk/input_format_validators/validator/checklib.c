/*
 * This library contains a collection of routines useful in checking the
 * validity of the input.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

static int case_no;
static int line_no;

/* drive the validation of many test files given the command-line arguments */
/* The check_file routine is called for each file                           */
int driver(int argc, char *argv[], void (*check_file)(FILE *))
{
/*
  FILE *in;
  int i;
*/

  (*check_file)(stdin);

  exit(42);  /* everything's okay for kattis format */
}

/* initialize some internal variables used in checklib.  Called once for */
/* each input file                                                       */
void init_checklib(void)
{
  case_no = 1;
  line_no = 1;
}

/* query the case number */
int get_case(void)
{
  return case_no;
}

/* increment the case number */
void inc_case(void)
{
  case_no++;
}

/* get the line number */
int get_line(void)
{
  return line_no;
}

static void print_char(FILE *out, char c)
{
  if (c == '\n') {
    fprintf(out, "'\\n'");
  } else if (c == EOF) {
    fprintf(out, "EOF");
  } else {
    fprintf(out, "'%c'", c);
  }
}

/* eat as much whitespace as possible from the current position     */
/* The number of whitespace read is returned as the function value  */
/* The number of newline characters read is returned as a parameter */
/* Whether EOF is reached is also returned as a parameter           */
/*                                                                  */
/* Note: we only count ' ' and '\n' as whitespace.                  */
int eat_space(FILE *in, int *newline, int *end)
{
  int c, count;
  
  count = *newline = 0;
  while ((c = fgetc(in)) != EOF && isspace(c)) {
    if (c == '\n') {
      (*newline)++;
      line_no++;
    } else if (c == '\t') {
      fprintf(stderr, "Case %d, line %d: \\t present\n", case_no, line_no);
      exit(1);
    }
    count++;
  }
  if (c != EOF) {
    ungetc(c, in);
    *end = 0;
  } else {
    *end = 1;
  }
  return count;
}

/* consume one character.  It's an error if the next character is not  */
/* the specified character.                                            */
void match_char(FILE *in, char s)
{
  int c;
  if ((c = fgetc(in)) != s) {
    fprintf(stderr, "Case %d, line %d: expecting ", case_no, line_no);
    print_char(stderr, s);
    fprintf(stderr, " but got ");
    print_char(stderr, c);
    fprintf(stderr, " instead.\n");
    exit(1);
  }
  if (s == '\n') {
    line_no++;
  }
}

/* check that we have EOL, and eat the newline */
extern void check_EOL(FILE *in)
{
  match_char(in, '\n');
}

/* ensure that we have no more input */
void check_EOF(FILE *in)
{
  int c, nl, e;
  char buffer[81];
  
  c = eat_space(in, &nl, &e);
  if (c > 0 || !e) {
    fgets(buffer, 81, in);
    if (buffer[strlen(buffer)-1] == '\n') {
      buffer[strlen(buffer)-1] = 0;
    }
    fprintf(stderr, "Case %d, line %d: extra input starting with \"%s\"\n", 
	    case_no, line_no, buffer);
    exit(1);
  }
}

/* read n integers separated by one space.  It's an error if there is any */
/* leading space.  Trailing spaces are not read/consumed                  */
void read_int(FILE *in, int n, int *list)
{
  int count, newline, end, i, c;
  char buffer[21], *p;

  for (i = 0; i < n; i++) {
    if (i) {
      match_char(in, ' ');
    }

    count = eat_space(in, &newline, &end);
    if (count > 0) {
      fprintf(stderr, "Case %d, line %d: there is extra whitespace before item %d in the list.\n", case_no, line_no, i+1);
      exit(1);
    }
    if (end) {
      fprintf(stderr, "Case %d, line %d: ran out of input.\n", case_no, 
	      line_no);
      exit(1);
    }

    fscanf(in, "%20s", buffer);     /* this reads something because !end */

    if ((!isspace((c = fgetc(in))) && c != EOF) || strlen(buffer) > 10) {
      fprintf(stderr, "Case %d, line %d: overflow: %s%c\n", case_no, line_no,
	      buffer, c);
      exit(1);
    }
    if (c != EOF) {
      ungetc(c, in);
    }
    errno = 0;
    list[i] = strtol(buffer, &p, 10);
    if (*p) {
      fprintf(stderr, "Case %d, line %d: not a valid number: %s\n", case_no, 
	      line_no, buffer);
      exit(1);
    }
    if (errno == ERANGE) {
      fprintf(stderr, "Case %d, line %d: overflow: %s\n", case_no, line_no,
	      buffer);
      exit(1);
    }
  }
}

/* read n long long separated by one space.  It's an error if there is any */
/* leading space.  Trailing spaces are not read/consumed                   */
void read_longlong(FILE *in, int n, long long *list)
{
  int count, newline, end, i, c;
  char buffer[31], *p;

  for (i = 0; i < n; i++) {
    if (i) {
      match_char(in, ' ');
    }

    count = eat_space(in, &newline, &end);
    if (count > 0) {
      fprintf(stderr, "Case %d, line %d: there is extra whitespace before item %d in the list.\n", case_no, line_no, i+1);
      exit(1);
    }
    if (end) {
      fprintf(stderr, "Case %d, line %d: ran out of input.\n", case_no, 
	      line_no);
      exit(1);
    }

    fscanf(in, "%30s", buffer);     /* this reads something because !end */

    if ((!isspace((c = fgetc(in))) && c != EOF) || strlen(buffer) > 19) {
      fprintf(stderr, "Case %d, line %d: overflow: %s%c\n", case_no, line_no,
	      buffer, c);
      exit(1);
    }
    if (c != EOF) {
      ungetc(c, in);
    }
    errno = 0;
    list[i] = strtoll(buffer, &p, 10);
    if (*p) {
      fprintf(stderr, "Case %d, line %d: not a valid number: %s\n", case_no, 
	      line_no, buffer);
      exit(1);
    }
    if (errno == ERANGE) {
      fprintf(stderr, "Case %d, line %d: overflow: %s\n", case_no, line_no,
	      buffer);
      exit(1);
    }
  }
}


/* read n doubles separated by one space.  It's an error if there is any  */
/* leading space.  Trailing spaces are not read/consumed.  The max number */
/* of decimal places allowed is specified in dp.                          */
extern void read_double(FILE *in, int n, int dp, double *list)
{
  int count, newline, end, i, c, len, d;
  char buffer[1001], *p;
  int exact = dp < 0;

  if (dp < 0) {
    dp = -dp;
  }

  for (i = 0; i < n; i++) {
    if (i) {
      match_char(in, ' ');
    }

    count = eat_space(in, &newline, &end);
    if (count > 0) {
      fprintf(stderr, "Case %d, line %d: there is extra whitespace before item %d in the list.\n", case_no, line_no, i+1);
      exit(1);
    }
    if (end) {
      fprintf(stderr, "Case %d, line %d: ran out of input.\n", case_no,
	      line_no);
      exit(1);
    }

    fscanf(in, "%1000s", buffer);     /* this reads something because !end */

    if ((!isspace((c = fgetc(in))) && c != EOF)) {
      fprintf(stderr, "Case %d, line %d: double too long %s%c\n", case_no, 
	      line_no, buffer, c);
      exit(1);
    }
    if (c != EOF) {
      ungetc(c, in);
    }
    list[i] = strtod(buffer, &p);
    if (*p) {
      fprintf(stderr, "Case %d, line %d: not a valid double: %s\n", case_no,
	      line_no, buffer);
      exit(1);
    }
    if (errno == ERANGE) {
      fprintf(stderr, "Case %d, line %d: overflow or underflow: %s\n", case_no,
	      line_no, buffer);
      exit(1);
    }
    p = strchr(buffer, '.');
    d = 0;
    if (p) {
      len = strlen(buffer);
      d = len - ((p - buffer) + 1);
    } else {
      d = 0;
    }
    if ((p && !d) ||
	(exact && d != dp) ||
	(!exact && d > dp)) {
      fprintf(stderr, "Case %d, line %d: incorrect number of decimal places: %s\n", 
	      case_no, line_no, buffer);
      exit(1);
    }

  }
}

/* read n strings separated by one space.  It's an error if there is any  */
/* leading space, or if any string is longer than len.  Trailing spaces   */
/* are not consumed                                                       */
void read_str(FILE *in, int n, int len, char **list)
{
  int count, newline, end, i, c;

  for (i = 0; i < n; i++) {
    if (i) {
      match_char(in, ' ');
    }

    count = eat_space(in, &newline, &end);
    if (count > 0) {
      fprintf(stderr, "Case %d, line %d: there is extra whitespace before item %d in the list.\n", case_no, line_no, i+1);
      exit(1);
    }
    if (end) {
      fprintf(stderr, "Case %d, line %d: ran out of input.\n", case_no,
	      line_no);
      exit(1);
    }

    count = 0;
    while (count < len && (c = fgetc(in)) != EOF && !isspace(c)) {
      list[i][count++] = c;
    }
    list[i][count] = 0;

    if (count < len) {
      if (c != EOF) {
	ungetc(c, in);
      }
    } else if (count == len) {
      c = fgetc(in);
      if (c != EOF && !isspace(c)) {
	fprintf(stderr, "Case %d, line %d: string too long: %s%c\n", case_no,
		line_no, list[i], c);
	exit(1);
      }
      if (c != EOF) {
	ungetc(c, in);
      }
    }
  }
}

/* read one line of text (may have spaces).  The last \n character is not */
/* stored.  Up to len character is read.  If the line of text is longer,  */
/* an error is reported.                                                  */
/* Assumes that line is an array of len+1 characters.                     */
void read_line(FILE *in, int len, char *line)
{
  int count = 0, c = 0;
  while (count < len && (c = fgetc(in)) != EOF && c != '\n') {
    line[count++] = c;
  }
  line[count] = 0;

  if (c == EOF) {
    fprintf(stderr, "Case %d, line %d: EOF seen\n", case_no, line_no);
    exit(1);
  }
  if (count >= len) {
    c = fgetc(in);
    if (c == EOF) {
      fprintf(stderr, "Case %d, line %d: EOF seen\n", case_no, line_no);
      exit(1);
    } else if (c != '\n') {
      fprintf(stderr, "Case %d, line %d: line too long: %s%c\n", case_no,
	      line_no, line, c);
      exit(1);
    }
  }
    
  line_no++;
}


/* check that an integer is in range */
void check_int_range(int val, int min_val, int max_val, const char *label)
{
  if (!(min_val <= val && val <= max_val)) {
    fprintf(stderr, "Case %d, line %d: %s \"%d\" outside of range.\n",
	    case_no, line_no, label, val);
    exit(1);
  }
}

/* check that a long long integer is in range */
void check_longlong_range(long long val, long long min_val,
			  long long max_val, const char *label)
{
  if (!(min_val <= val && val <= max_val)) {
    fprintf(stderr, "Case %d, line %d: %s \"%lld\" outside of range.\n",
	    case_no, line_no, label, val);
    exit(1);
  }
}

/* check that a double is in range */
void check_double_range(double val, double min_val, double max_val,
			const char *label)
{
  if (!(min_val <= val && val <= max_val)) {
    fprintf(stderr, "Case %d, line %d: %s \"%.4f\" outside of range.\n",
	    case_no, line_no, label, val);
    exit(1);
  }
}

/* allocate an array of n strings each of length at most len */
char **alloc_strs(int n, int len)
{
  char **ptr;
  int i;
  
  if (!(ptr = malloc(n * sizeof(*ptr)))) {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }
  for (i = 0; i < n; i++) {
    if (!(ptr[i] = malloc(len+1))) {
      fprintf(stderr, "Out of memory\n");
      exit(1);
    }
  }
  return ptr;
}

/* deallocate an array of n strings allocated by alloc_strs */
void free_strs(char **list, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    free(list[i]);
  }
  free(list);
}
