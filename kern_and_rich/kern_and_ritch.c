#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAXLINE 1000

//static char str[] = "Hello, world\n";
const static char pattern[] = "ould";

/* squeeze: deletes all characters n from string s */
void squeeze(char *s, int c)
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';

}

/* getbits: extracts n bits, starting from p position */
unsigned int getbits(unsigned int x, int p, int n)
{
	return (x >> (p+1-n)) && ~(~0 << n);
}

/* atoi: converts string s to an integer */ 
int atoi(char *s)
{
	int i, n = 0;

	for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
		n = n * 10 + (s[i] - '0');

	return n;
}

/* atoi2: converts string s to an integer */ 
int atoi2(char *s)
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (n = 0; isdigit(s[i]); i++)
		n = n * 10 + (s[i] - '0');

	return sign * n;
}

/* strlen: returns length of string variable s */
int strlength(char *s)
{
	int i;

	for(i = 0; s[i] != '\0'; i++)
		;
	/* i = 0;
		while(s[i] != '\0')
		i++;
	 */
	return i;
}

/* reverse: reverses characters order in string s */
void reverse_string(char *s)
{
	int c, i, j;

	for (i = 0, j = strlength(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa: coverts number n to characters string s */
void itoa(int n, char *s)
{
	int i = 0, sign = n;

	if (sign < 0)
		n = -n; /* make number positive*/

	do {
		s[i] = n % 10 + '0';
		i++;
		n /= 10;
	} while(n);

	if(sign < 0) {
		s[i] = '-';
		i++;
	}
	s[i] = '\0';
	reverse_string(s);
}

/* trim: deletes white space characters from the end of a string */
int trim(char *s)
{
	int n;

	for (n = strlen(s) - 1; n >= 0; n--)
		if (s[n] != ' ' || s[n] != '\t' || s[n] != '\n')
			break;
	s[n+1] = '\0';
	return n;
}

void leap_year(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		printf("%d is a leap year\n", year);
	else
		printf("%d is not a leap year\n", year);
}

/* bitcount: counts the ones in binary notation x */
int bitcount(unsigned int x)
{
	int b;

	for (b = 0; x != 0; x >>= 1)
		if (x & 1) {
			b++;
		}
	return b;
}

/* counts strings, words and characters from output */
void strcount(void)
{
	int nl, nw, nc, state;
	char c;
	state = OUT;
	nl = nw = nc = 0;

	while ((c = getchar()) != EOF) {
		nc++;
		if (c == '\n')
			nl++;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			nw++;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
}

/* power: raise base to n power */
int power(int base, int n)
{
	int i, p = 1;

	for (i = 0; i <= n; i++)
		p = p * base;

	return p;

	/* int p;
	for (p = 1; n > 0; n--)
		p = p * base;
	 */
}

/* binsearch: search x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;

		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* getline2: reads string in s, returns his length */
int getline2(char *s, int lim)
{
	int c, i = 0;

	while (lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i] = c;
		i++;
		lim--;
	}
	
	if (c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

/* strindex: returns the index of string t in s, -1 if absent. (almost an 
 * analogue of the function strstr)
 */
int strindex(char *s, const char *t)
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

/* atof: converts string s to double */
double atof(const char *s)
{
	double val, power;
	int i, sign;

	/* skip spaces */
	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}

static const char f[] = "  -5.9";

int main(void)
{
	char num_array[10];
	int number = -439;
	int numbers[] = { 4, 5, 8, 12, 56, 57, 70, 664, 5632 };
	char line[MAXLINE];

	printf("index: %d\n", binsearch(5632, numbers, 9));
	itoa(number, num_array);
	printf("itoa: %s\n", num_array);

	/*
	while (getline2(line, MAXLINE) > 0)
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
		}
	*/
	printf("%f\n", atof(f));
	return 0;
}
