#include <stdio.h>
#include <stdlib.h> /* malloc, realloc, free */

typedef struct vector_t {
	int *data;
	size_t size;
	size_t capacity;
} vector;

enum {
	index_is_outside = 1
};

static int v_errno = 0;

void v_init(vector *v, int capacity)
{
	v->data = (int *) malloc(capacity * sizeof(int));
	v->size = 0;
	v->capacity = capacity;
}

void v_free(vector *v)
{
	free(v->data);
	v->size = 0;
	v->capacity = 0;
}

int v_get(vector *v, size_t idx)
{
	if (idx < v->size) {
		v_errno = 0;
		return v->data[idx];
	}

	v_errno = index_is_outside;
	return -1;
}

void v_push_back(vector *v, int value)
{
	if (v->size >= v->capacity) {
		v->capacity *= 2;
		v->data = (int *) realloc(v->data, v->capacity * sizeof(int));
	}
	v->data[v->size] = value;
	v->size++;
}

void v_pop_back(vector *v)
{
	if (v->size > 0)
		v->size--;
}

void v_set(vector *v, size_t idx, int value)
{
	if (idx < v->size)
		v->data[idx] = value;
}

int main(void)
{
	vector vect;

	v_init(&vect, 4);

	v_push_back(&vect, 1);
	v_push_back(&vect, 3);
	v_push_back(&vect, 5);
	v_push_back(&vect, 3);

	printf("vector size: %ld\n", vect.size);
	printf("vector capacity: %ld\n", vect.capacity);
	printf("index: %d, value: %d\n", 2, v_get(&vect, 2));

	v_set(&vect, 2, 50);
	printf("index: %d, value: %d\n", 2, v_get(&vect, 2));

	v_pop_back(&vect);	
	printf("vector size after deleting: %ld\n", vect.size);

	v_push_back(&vect, 12);
	v_push_back(&vect, 97);
	v_push_back(&vect, 3245);
	
	printf("vector size: %ld\n", vect.size);
	printf("vector capacity: %ld\n", vect.capacity);
	v_free(&vect);

	return 0;
}