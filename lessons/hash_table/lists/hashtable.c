#include <string.h>				/* strlen, strcmp */
#include <stdlib.h>				/* malloc, calloc, free */
#include <math.h>				/* sqrt */
#include <assert.h>				/* assert */
#include "hashtable.h"
#include "pool.h"

#define HASH_TABLE_SIZE 65537
#define LOAD_FACTOR_THRESHOLD 0.75
#define DEFAULT_ALIGNMENT 8

static long next_prime(unsigned long n)
{
	long i;
	int fprime;
	long bound;

	if (n <= 1)
		return 2;

	if (n == 2)
		return n;

	for (fprime = 1; fprime; n++) {
		fprime = 0;

		if (n % 2 == 0) {
			fprime = 1;
			continue;
		}

		bound = sqrt(n);
		for (i = 3; i <= bound; i += 2) {
			if (n % i == 0) {
				fprime = 1;
				break;
			}
		}
	}

	return n - 1;
}

static unsigned long djb2(const char *str)
{
	unsigned char c;
	unsigned long hash = 5381;

	assert(str);
	while ((c = *str) != '\0') {
		hash = ((hash << 5) + hash) + c;
		str++;
	}

	return hash;
}

static void ht_increase(hash_table * h)
{
	item **new_ht, **tmp_ht;
	unsigned char *nbuf;
	unsigned char *oldp;
	int i, old_size;
	item *tmp;

	assert(h);
	old_size = h->size;
	h->size = next_prime(h->size * 2);

	new_ht = calloc(h->size, sizeof(item *));
	tmp_ht = h->ht;
	h->ht = new_ht;
	h->count = 0;

	nbuf = malloc(h->size * sizeof(item));
	oldp = h->p->buf;
	pool_init(h->p, nbuf, h->size * sizeof(item), sizeof(item), DEFAULT_ALIGNMENT);

	for (i = 0; i < old_size; i++) {
		tmp = tmp_ht[i];
		while (tmp != NULL) {
			ht_insert(h, tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}

	free(oldp);
	free(tmp_ht);
}

void ht_insert(hash_table * h, const char *key, int value)
{
	item *new_item, *tmp;
	unsigned long index;

	assert(h);
	assert(key);

	if ((double) h->count / h->size >= LOAD_FACTOR_THRESHOLD)
		ht_increase(h);

	index = djb2(key) % h->size;

	tmp = h->ht[index];
	while (tmp != NULL) {
		if (strcmp(key, tmp->key) == 0) {
			tmp->value = value;
			return;
		}
		tmp = tmp->next;
	}

	new_item = pool_get(h->p);
	assert(new_item && "pool is exceeded");
	new_item->key = key;
	new_item->value = value;
	new_item->next = h->ht[index];

	h->ht[index] = new_item;
	h->count++;
}

void ht_free(hash_table * h)
{
	assert(h);

	free(h->ht);
	free(h->p->buf);
	free(h->p);
	free(h);
}

item *ht_search(const hash_table * h, const char *key)
{
	item *it;
	unsigned long index;

	assert(h);
	assert(key);

	index = djb2(key) % h->size;
	it = h->ht[index];
	while (it != NULL) {
		if (strcmp(it->key, key) == 0)
			return it;
		it = it->next;
	}

	return NULL;
}

void ht_delete(hash_table * h, const char *key)
{
	item *it, *prev_it = NULL;
	unsigned long index;

	assert(h);
	assert(key);

	index = djb2(key) % h->size;
	it = h->ht[index];
	while (it != NULL) {
		if (strcmp(it->key, key) == 0) {
			if (prev_it != NULL)
				prev_it->next = it->next;
			else
				h->ht[index] = it->next;
			pool_put(h->p, it);
			break;
		}
		prev_it = it;
		it = it->next;
	}
	h->count--;
}

hash_table *ht_init(void)
{
	unsigned char *buf;
	int buf_len = HASH_TABLE_SIZE * sizeof(item);
	hash_table *h;

	h = malloc(sizeof(hash_table));
	h->p = malloc(sizeof(pool));
	h->ht = calloc(HASH_TABLE_SIZE, sizeof(item *));
	h->size = next_prime(HASH_TABLE_SIZE);
	h->count = 0;
	buf = malloc(buf_len);
	pool_init(h->p, buf, buf_len, sizeof(item), DEFAULT_ALIGNMENT);
	return h;
}
