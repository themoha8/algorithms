#ifndef HASH_TABLE_H_SENTRY
#define HASH_TABLE_H_SENTRY 1

typedef struct item_t {
	const char *key;
	int value;
	struct item_t *next;
} item;

typedef struct hash_table_t {
	struct item_t **ht;
	int size;
	int count;
} hash_table;

item *ht_search(const hash_table *h, const char *key);
void ht_insert(hash_table *h, const char *key, int value);
void ht_delete(hash_table *h, const char *key);
hash_table *ht_init(void);
void ht_free(hash_table *h);

#endif
