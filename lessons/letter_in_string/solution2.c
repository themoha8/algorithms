/* the most common letter in a string
 * algorithm complexity O(N*k)
 */

#include <stdio.h>
#include <string.h> /* strlen */
#include <time.h> /* clock_gettime */
#include <stdlib.h> /* malloc, free */
#include "benchmark.h" /* diff_timestamps */

#define MAX_STRING 65536
#define ASCII_LEN 94

/* without space character */
const char ascii_printable[ASCII_LEN] = {
	'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*',
	'+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5',
	'6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
	'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
	'w', 'x', 'y', 'z', '{', '|', '}', '~'
};

int main(void)
{
	char *s = (char*)malloc(MAX_STRING), ch = '\0';
	int c1 = 0, i, j, slen;
	struct timespec t1, t2;
	double res;

	if(fgets(s, MAX_STRING, stdin) == NULL) {
		printf("Row missing\n");
		return 0;
	}

	slen = (int)strlen(s);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	for (i = 0; i < ASCII_LEN; i++) {
		int c2 = 0;
			for (j = 0; j < slen; j++)
				if (ascii_printable[i] == s[j])
					c2++;
			if (c2 > c1) {
				ch = ascii_printable[i];
				c1 = c2;
			}
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);

	res = diff_timestamps(&t1, &t2);
	printf("Execution time in seconds: %lf\n", res);
	printf("char: '%c', number of %d\n", ch, c1);
	free(s);
	return 0;
}
