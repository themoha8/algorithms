#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc, calloc, free */
#include <math.h> 	/* sqrt */
#ifdef PERFORM
#include <stdio.h>
#endif
#include "hashtable.h"
#include "pool.h"

#define HASH_TABLE_SIZE 65537
#define LOAD_FACTOR_THRESHOLD 0.75

#ifdef PERFORM
int collisions;
int deep_collision;
int max_deep_collision;
int max_deep_collision_idx;
#endif

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
		for (i = 3; i <= bound; i+=2) {
			if (n % i == 0) {
				fprime = 1;
				break;
			}
		}
	}

	return n-1;
}

static unsigned long djb2(const char *str)
{
	unsigned char c;
	unsigned long hash = 5381;

	while ((c = *str) != '\0') {
		hash = ((hash << 5) + hash) + c;
		str++;
	}

	return hash;
}

static void ht_increase(hash_table *h)
{
	item **new_ht, **tmp_ht;
	int i, old_size = h->size;

	h->size = next_prime(h->size * 2);

	new_ht = calloc(h->size, sizeof(item *));
	tmp_ht = h->ht;
	h->ht = new_ht;
	h->count = 0;

	for (i = 0; i < old_size; i++) {
		item *tmp, *tmp2;

		tmp = tmp_ht[i];
		while (tmp != NULL) {
			ht_insert(h, tmp->key, tmp->value);
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
	}

	free(tmp_ht);
}

void ht_insert(hash_table *h, const char *key, int value)
{
	item *new_item, *tmp;
	unsigned long index; 
	
	if ((double) h->count / h->size >= LOAD_FACTOR_THRESHOLD)
		ht_increase(h);
	
	index = djb2(key) % h->size;

	tmp = h->ht[index];
	while (tmp != NULL) {
		if (strcmp(key, tmp->key) == 0) {
#ifdef PERFORM
			printf("duplicate key: %s\n", key);
#endif
			tmp->value = value;
			return;
		}
		tmp = tmp->next;
	}

	new_item = malloc(sizeof(*new_item));
	new_item->key = key;
	new_item->value = value;
	new_item->next = h->ht[index];

	h->ht[index] = new_item;
	h->count++;
}

void ht_free(hash_table *h)
{
	int i;
	item *it, *tmp;

	for (i = 0; i < h->size; i++) {
		it = h->ht[i];
		while (it != NULL) {
			tmp = it;
			it = it->next;
#ifdef PERFORM
			if (it) {
				deep_collision++;
				collisions++;
				printf("collision index: %d (%s)\n", i, tmp->key);
				if (it->next == NULL)
					printf("collision index: %d (%s)\n", i, it->key);
				fflush(stdout);
			}
#endif
			free(tmp);
		}
#ifdef PERFORM
		if (deep_collision > max_deep_collision) {
			max_deep_collision = deep_collision;
			max_deep_collision_idx = i;
		}
		deep_collision = 0;
#endif
	}

#ifdef PERFORM
	printf("ht count: %d\n", h->count);
	printf("ht size: %d\n", h->size);
	printf("the number of collisions: %d\n", collisions);
	printf("max collision deep: %d (index: %d)\n", max_deep_collision, max_deep_collision_idx);
#endif
	free(h->ht);
	free(h);
}

item *ht_search(const hash_table *h, const char *key)
{
	item *it;
	unsigned long index = djb2(key) % h->size;

	it = h->ht[index];
	while (it != NULL) {
		if (strcmp(it->key, key) == 0)
			return it;
		it = it->next;
	}

	return NULL;
}

void ht_delete(hash_table *h, const char *key)
{
	item *it, *prev_it = NULL;
	unsigned long index = djb2(key) % h->size;

	it = h->ht[index];
	while (it != NULL) {
		if (strcmp(it->key, key) == 0) {
			if (prev_it != NULL)
				prev_it = it->next;
			else
				h->ht[index] = it->next;
			free(it);
			return;
		}
		prev_it = it;
		it = it->next;
	}
}

hash_table *ht_init(void)
{
	hash_table *h;

	h = malloc(sizeof(hash_table));
	h->ht = calloc(HASH_TABLE_SIZE, sizeof(item *));
	h->size = HASH_TABLE_SIZE;
	h->count = 0;
	return h;
}
