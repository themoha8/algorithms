#include <stdio.h>
#include <string.h> /* strlen */

const char *words[] = { "Sky", "Sunny", "Lemon", "Approximatly", "Tea", "Hi" };

static int shortword(const char *s[])
{
	int min_len = strlen(s[0]), index = 0, i;

	for (i = 1; s[i]; i++) {
		int l = strlen(s[i]);
		if (l < min_len) {
			min_len = l;
			index = i;
		}
	}

	return index;
}

int main(void)
{
	int res = shortword(words);
	printf("short word (the most first) (index): %d\t, value: %s\n",  res, words[res]);
	return 0;
}
