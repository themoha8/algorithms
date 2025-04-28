#include <stdio.h>

// capacity - the current size of hash table.
// size - a number of occupied elements in the hash table.
// max_size - load factory threshold. (capacity / size >= 0.75)
// flags - state of the element (0 - is freed, 1 - is occupied, 2 - is deleted)
// keys - array of the keys
// values - array of the values
struct hash_table_t {
	long size, max_size, capacity;
	char *flags;
	char *keys;
	int *values;
};

enum { freed = 0, occupied = 1, deleted = 2 };

void ht_init(hash_table *h)
{
	h->size = h->max_size = h->capacity = 0;
	h->flags = NULL;
	h->keys = NULL;	
	h->values = NULL;
}

void ht_destroy(hash_table *h)
{
	free(h->keys);
	free(h->values);
	free(h->flags);
}

void ht_clear(hash_table *h)
{
	h->size = 0;
	if (h->flags) {
		memset(h->flags, 0, h->capacity);
	}
}

int *ht_search(hash_table *h, const char *key)
{
	long ht_mask, index;

	if (!h->size) {
		return NULL;
	}

	ht_mask = h->capacity - 1;
	index = djb2 & ht_mask;

	while (h->flags[index] != freed) {
		if (h->flags[index] == occupied)
			if (strcmp(h->key, key) == 0)
				return index;
		vimW
	}
}

...
