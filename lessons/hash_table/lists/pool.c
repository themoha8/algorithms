#include <stdio.h>				/* fprintf */
#include <stdint.h>				/* types */
#include <string.h>				/* memset */
#include <assert.h>				/* assert */
#include <stdbool.h>			/* bool type */
#include "pool.h"

static bool is_power_of_two(size_t n)
{
	return (n & (n - 1)) == 0;
}

static uintptr_t align_forward(uintptr_t ptr, size_t align)
{
	uintptr_t p, a, modulo;

	assert(is_power_of_two(align));

	p = ptr;
	a = (uintptr_t) align;
	/* Same as (p % a) buf faster as 'a' is a power of two. */
	modulo = p & (a - 1);

	if (modulo != 0) {
		/* If 'p' address is not aligned, push address
		 * to the next value which is aligned.
		 */
		p += a - modulo;
	}
	return p;
}

static void pool_free_all(pool * p)
{
	size_t chunkc = p->buf_len / p->chunk_size;
	size_t i;

	for (i = 0; i < chunkc; i++) {
		void *ptr = &p->buf[i * p->chunk_size];
		pool_free_node *n = (pool_free_node *) ptr;

		n->next = p->head;
		p->head = n;
	}
}

void pool_init(pool * p, void *buf, size_t buf_len, size_t chunk_size, size_t chunk_align)
{
	// Align buffer to the specified chunk alignment.
	uintptr_t ini_start = (uintptr_t) buf;
	uintptr_t start = align_forward((uintptr_t) buf, chunk_align);
	buf_len = buf_len - (start - ini_start);

	// Align chunk size up to the required chunk_align.
	chunk_size = align_forward((uintptr_t) chunk_size, chunk_align);

	// assert(chunk_size >= sizeof(pool_free_node) && "Chunk size is too small.");
	assert(buf_len >= chunk_size && "Buffer length is smaller than the chunk size.");

	// Store the adjusted parameters.
	p->buf = (unsigned char *) buf;
	p->buf_len = buf_len;
	p->chunk_size = chunk_size;
	p->head = NULL;

	// Set up the free list for free chunks
	pool_free_all(p);
}

void *pool_get(pool * p)
{
	// Get the latest free node.
	pool_free_node *n = p->head;

	if (n == NULL) {
		fprintf(stderr, "Pool allocator has no free memory\n");
		return NULL;
	}
	// Pop free node.
	p->head = p->head->next;

	return memset(n, 0, p->chunk_size);
}

void pool_put(pool * p, void *ptr)
{
	pool_free_node *n;
	void *start = p->buf;
	void *end = &p->buf[p->buf_len];

	if (ptr == NULL) {
		return;
	}

	if (ptr < start || ptr > end)
		assert(0 && "Memory is out of bounds of the buffer in this pool");

	n = (pool_free_node *) ptr;
	n->next = p->head;
	p->head = n;
}
