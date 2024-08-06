/* RLE (run-length ecoding) is a form of lossless data compression in which
 * runs of data (consecutive occurrences of the same data value) are stored 
 * as a single occurrence of that data value and a count of its consecutive 
 * occurrences, rather than as the original run.
 */

#include <stdio.h>
#include <string.h>

/* const char str[44] = "AAAABBBCCZYXDDDDEEEEFFFAAABBBBBBBBBBBBBBBBB"; */
const char str[44] = "AAAABBBCZZ";
/* const char str[] = "d"; */

/* Simplified version. Output occurrences of character without the number of 
 * repetitions
 */
static void rle(const char *s, int len)
{
	int i;

	if (!len)
		return;

	for (i = 0; i < len-1; i++) {
		if (s[i] != s[i+1])
			printf("%c", s[i]);
	}
	printf("\n");
}

static void rle2(const char *s, int len)
{
	int i, n = 0;

	if (!len)
		return;

	for (i = 0; i < len-1; i++)
		if (s[i] != s[i+1]) {
			if (n == 0)
				printf("%c", s[i]);
			else
				printf("%c%d", s[i], n+1);
			n = 0;
		} else
			n++;

	printf("\n");
}

static int rle3(const char *s, char *output, int o_len)
{
	int i, j = 0, n = 0, needed_size;
	size_t s_len = strlen(s)+1;

	if (s_len < 2)
		return 1;

	for (i = 0; i < s_len-1; i++)
		if (s[i] != s[i+1]) {
			if (n == 0) {
				if (j < o_len-1)
					output[j++] = s[i];
				else
					return 2;	
			} else if (j < o_len-1) {
				output[j++] = s[i];
				needed_size = snprintf(NULL, 0, "%d", n+1) + 1; /* 1 for '\0' */
				if (j + needed_size > o_len)
					return 2;
				j += sprintf(&output[j], "%d", n+1);
			}
			n = 0;
		} else
			n++;

	output[j] = '\0';
	return 0;
}

int main(void)
{
	char out[7], res;

	rle2(str, sizeof(str));
	
	res = rle3(str, out, 7);
	if (res == 1) {
		fprintf(stderr, "array lenght equal 1\n");
		return 1;
	} else if (res == 2) {
		fprintf(stderr, "Not enough space in array\n");
		return 2;
	}
	printf("string (rle3): %s\n", out);
	return 0;
}
