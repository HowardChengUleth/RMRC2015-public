/*
 * This library contains a collection of routines useful in checking the
 * validity of the input.
 *
 */

#include <stdio.h>
#ifndef _CHECKLIB_H_
#define _CHECKLIB_H_

/* drive the validation of many test files given the command-line arguments */
/* The check_file routine is called for each file                           */
extern int driver(int argc, char *argv[], void (*check_file)(FILE *));

/* initialize some internal variables used in checklib.  Called once for */
/* each input file                                                       */
extern void init_checklib(void);

/* query the case number */
extern int get_case(void);

/* increment the case number */
extern void inc_case(void);

/* get the line number */
extern int get_line(void);

/* eat as much whitespace as possible from the current position     */
/* The number of whitespace read is returned as the function value  */
/* The number of newline characters read is returned as a parameter */
/* Whether EOF is reached is also returned as a parameter           */
/*                                                                  */
/* Note: we only count ' ' and '\n' as whitespace.                  */
extern int eat_space(FILE *in, int *newline, int *end);

/* consume one character.  It's an error if the next character is not  */
/* the specified character.                                            */
extern void match_char(FILE *in, char s);

/* check that we have EOL, and eat the newline */
extern void check_EOL(FILE *in);

/* ensure that we have no more input */
extern void check_EOF(FILE *in);

/* read n integers separated by one space.  It's an error if there is any */
/* leading space.  Trailing spaces are not read/consumed                  */
extern void read_int(FILE *in, int n, int *list);

/* read n long long separated by one space.  It's an error if there is any */
/* leading space.  Trailing spaces are not read/consumed                   */
extern void read_longlong(FILE *in, int n, long long *list);

/* read n doubles separated by one space.  It's an error if there is any  */
/* leading space.  Trailing spaces are not read/consumed.  The max number */
/* of decimal places allowed is specified in dp.  If dp is negative, then */
/* the number of decimal places must be exactly -dp.                      */
extern void read_double(FILE *in, int n, int dp, double *list);

/* read n strings separated by one space.  It's an error if there is any  */
/* leading space, or if any string is longer than len.  Trailing spaces   */
/* are not consumed                                                       */
extern void read_str(FILE *in, int n, int len, char **list);

/* read one line of text (may have spaces).  The last \n character is not */
/* stored.  Up to len character is read.  If the line of text is longer,  */
/* an error is reported.                                                  */
/* Assumes that line is an array of len+1 characters.                     */
extern void read_line(FILE *in, int len, char *line);

/* check that an integer is in range */
extern void check_int_range(int val, int min_val, int max_val,
			    const char *label);

/* check that a long long integer is in range */
extern void check_longlong_range(long long val, long long min_val,
				 long long max_val, const char *label);

/* check that a double is in range */
extern void check_double_range(double val, double min_val, double max_val,
			       const char *label);

/* allocate an array of n strings each of length at most len */
char **alloc_strs(int n, int len);

/* deallocate an array of n strings allocated by alloc_strs */
void free_strs(char **list, int n);

#endif
