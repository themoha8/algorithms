#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof(keytab) / sizeof(struct key))

struct key {
	char *word;
	int count;
}; 

static struct key keytab[] = {
	{ "break", 0, },
	{ "case", 0, },
	{ "char", 0, },
	{ "void", 0, }
};

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0; /* the next free position in buf */

/* enter character (maybe, returned to the stream) */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* returns character to the input stream */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		buf[bufp] = c;
		bufp++;
	}
}

/* binsearch: search n in tab[] where n is number of elements */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch()))
		;

	if (c != EOF)
		*w++ = c;

	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for ( ; --lim > 0; w++) {
		*w = getch();
		if (!isalpha(*w)) {
			ungetch(*w);
			break;
		}
	}

	*w = '\0';
	return word[0];
}

int main()
{
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);

	return 0;
}
