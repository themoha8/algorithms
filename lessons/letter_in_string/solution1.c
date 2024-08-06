/* the most common letter in a string
 * algorithm complexity O(N^2)
 */

#include <stdio.h>
#include <string.h> /* strlen */
#include <time.h> /* clock_gettime */
#include <stdlib.h> /* malloc, free */
#include "benchmark.h" /* diff_timestamps */

#define MAX_STRING 65536

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
	for (i = 0; i < slen; i++) {
		int c2 = 0;
		if (s[i] > 32 && s[i] < 126) {
			for (j = 0; j < slen; j++)
				if (s[i] == s[j])
					c2++;
			if (c2 > c1) {
				ch = s[i];
				c1 = c2;
			}
		}
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);

	res = diff_timestamps(&t1, &t2);
	printf("Execution time in seconds: %lf\n", res);
	printf("char: '%c', number of %d\n", ch, c1);
	free(s);
	return 0;
}
