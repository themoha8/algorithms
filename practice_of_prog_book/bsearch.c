#include <stdio.h>
#include <string.h> /* strcmp */
#include <stdlib.h> /* bsearch */

struct htmlchars_t {
	char *name;
	int code;
};

enum { num_of_htmlchars = 20 };

struct htmlchars_t htmlchars[num_of_htmlchars] = {
	{ "&Aacute;", 193 },
	{ "&aacute;", 225 },
	{ "&Acirc;",  194 },
	{ "&acirc;",  226 },
	{ "&Ccedil;", 199 },
	{ "&ccedil;", 231 },
	{ "&Eacute;", 201 },
	{ "&eacute;", 233 },
	{ "&Ecirc;",  202 },
	{ "&ecirc;",  234 },
	{ "&Iacute;", 205 },
	{ "&iacute;", 237 },
	{ "&Icirc;",  206 },
	{ "&icirc;",  238 },
	{ "&Ntilde;", 209 },
	{ "&ntilde;", 241 },
	{ "&Oacute;", 211 },
	{ "&oacute;", 243 },
	{ "&Uacute;", 218 },
	{ "&uacute;", 250 }
};

int htmlchars_cmp(const void *h1, const void *h2)
{
	struct htmlchars_t *ht1, *ht2;

	ht1 = (struct htmlchars_t *) h1;
	ht2 = (struct htmlchars_t *) h2;

	return strcmp(ht1->name, ht2->name);
}

int main()
{
	struct htmlchars_t key;
	struct htmlchars_t *ntilde_i;

	key.name = "&ntilde;";

	ntilde_i = (struct htmlchars_t *) bsearch(&key, htmlchars, num_of_htmlchars, sizeof(*htmlchars), htmlchars_cmp);

	key.code = ntilde_i->code;
	printf("'&ntilde;' code is &#%d\n", key.code);
	return 0;
}
