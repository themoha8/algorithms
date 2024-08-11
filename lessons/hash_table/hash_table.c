#include <stdio.h> /* printf */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc, calloc, free */
#include "hash_table.h"

#define HASH_TABLE_SIZE 65536
#define LOAD_FACTOR_THRESHOLD 0.75

static unsigned int djb2(const char *str)
{
	unsigned int hash = 5381;
	int size = (int) strlen(str), i;

	for (i = 0; i < size; i++)
		hash = ((hash << 5) + hash) + str[i];

	return hash;
}

static void ht_increase(hash_table *h)
{
	int i, old_ht_size = h->ht_size;
	struct item_t **new_ht, **tmp_ht;

	h->ht_size = h->ht_size * 2;

	new_ht = calloc(h->ht_size, sizeof(struct item_t *));
	tmp_ht = h->ht;
	h->ht = new_ht;

	for (i = 0; i < old_ht_size; i++) {
		struct item_t *tmp = tmp_ht[i], *tmp2;

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
	struct item_t *new_item, *tmp;
	unsigned int index; 
	
	h->ht_count++;
	if ((double) h->ht_count / h->ht_size >= LOAD_FACTOR_THRESHOLD)
		ht_increase(h);
	
	index = djb2(key) % h->ht_size;

	tmp = h->ht[index];
	while (tmp != NULL) {
		if (strcmp(key, tmp->key) == 0) {
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
}

void ht_free(hash_table *h)
{
	unsigned int i;

	for (i = 0; i < h->ht_size; i++) {
		struct item_t *item = h->ht[i];
		while (item != NULL) {
			struct item_t *tmp = item;
			item = item->next;
			free(tmp);
		}
	}
	free(h->ht);
	free(h);
}

struct item_t *ht_search(const hash_table *h, const char *key)
{
	struct item_t *item;
	unsigned int index = djb2(key) % h->ht_size;

	item = h->ht[index];
	while (item != NULL) {
		if (strcmp(item->key, key) == 0)
			return item;
		item = item->next;
	}

	return NULL;
}

hash_table *ht_init(void)
{
	hash_table *h;

	h = malloc(sizeof(hash_table));
	h->ht = calloc(HASH_TABLE_SIZE, sizeof(struct item_t *));
	h->ht_size = HASH_TABLE_SIZE;
	h->ht_count = 0;
	return h;
}

int main(void)
{
	struct item_t *item;
	hash_table *ht = ht_init();

	ht_insert(ht, "apple", 600);
	ht_insert(ht, "watermelon", 100);
	ht_insert(ht, "fuck", 222);
	ht_insert(ht, "lemon123", 300);
	ht_insert(ht, "fuck", 555);
	ht_insert(ht, "fucking", 666);
	item = ht_search(ht, "apple");
	if (item) {
		printf("key: %s, value: %d\n", item->key, item->value);
	}
	item = ht_search(ht, "watermelon");
	if (item) {
		printf("key: %s, value: %d\n", item->key, item->value);
	}
	item = ht_search(ht, "fuck");
	if (item) {
		printf("key: %s, value: %d\n", item->key, item->value);
	}
	ht_free(ht);
	return 0;
}
