#ifndef SENTRY_HASH_TABLE
#define SENTRY_HASH_TABLE

struct item_t {
	const char *key;
	int value;
	struct item_t *next;
};

typedef struct hash_table_t {
	struct item_t **ht;
	unsigned int ht_size;
	unsigned int ht_count;
} hash_table;

struct item_t *ht_search(const hash_table *h, const char *key);
void ht_insert(hash_table *h, const char *key, int value);
void ht_free(hash_table *h);
void ht_delete(hash_table *h, const char *key);
hash_table *ht_init(void);

#endif
