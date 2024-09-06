#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

const static char name1[] = "Acer";
const static char name2[] = "Asus";
const static char name3[] = "Lenovo";
const static char defn1[] = "Notebook";
const static char defn2[] = "Notebook";
const static char defn3[] = "Notebook";
const static char defn4[] = "Notebook2";

/* form hash value for string s */
unsigned int hash(const char *s)
{
	unsigned int hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

/* look for s in hashtab */
struct nlist *lookup(const char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; /* found */
	
	return NULL; /* not found */
}

/* put (name, defn) in hashtab */
struct nlist *install(const char *name, const char *defn)
{
	struct nlist *np;
	unsigned int hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist*) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else /* already there is in table */
		free((void *) np->defn); /*free previous defn */

	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

	return np;
}

int main()
{
	struct nlist *list;

	list = install(name1, defn1);
	printf("category: %s\t product_name: %s\n", list->defn, list->name);
	list = install(name2, defn2);
	printf("category: %s\t product_name: %s\n", list->defn, list->name);
	list = install(name3, defn3);
	printf("category: %s\t product_name: %s\n", list->defn, list->name);

	printf("Change category for acer\n");

	list = install(name1, defn4);
	printf("category: %s\t product_name: %s\n", list->defn, list->name);
	return 0;
}