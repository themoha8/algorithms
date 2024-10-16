#include <stdio.h>
#include <string.h>

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

int find_htmtchar_code(const char *name)
{
    int low, high, mid, cmp;
    low = 0;
    high = num_of_htmlchars - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        cmp = strcmp(name, htmlchars[mid].name);
        if (cmp < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else /* found match */
            return mid;
    }
    return -1; /* no match */
}

int main()
{
	int ntilde_i = find_htmtchar_code("&ntilde;");

	printf("'&ntilde;' code is &#%d\n", htmlchars[ntilde_i].code);
	return 0;
}
