#ifndef POOL_N_SENTRY
#define POOL_N_SENTRY 1

typedef struct pool_free_node_t {
	struct pool_free_node_t *next;
} pool_free_node;

typedef struct pool_t {
	unsigned char *buf;
	size_t buf_len;
	size_t chunk_size;
	pool_free_node *head;
} pool;

void pool_init(pool * p, void *buf, size_t buf_len, size_t chunk_size, size_t chunk_align);
void *pool_get(pool * p);
void pool_put(pool * p, void *ptr);

#endif
