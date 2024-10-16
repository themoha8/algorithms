#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quick_sort(int *arr, int size)
{
	int i, last;

	if (size <= 1)
		return;

	swap(&arr[0], &arr[size-1]);

	last = 0;
	for (i = 1; i < size; i++) {
		if (arr[i] < arr[0]) {
			last++;
			swap(&arr[last], &arr[i]);
		}
	}

	swap(&arr[0], &arr[last]);
	quick_sort(arr, last);
	quick_sort(arr+last+1, size-last-1);
}

void print_array(const int *nums, int size)
{
	int i;

	printf("array elements: ");
	for (i = 0; i < size; i++)
		printf("%d ", nums[i]);
	putchar('\n');
	putchar('\n');
}

static void shuffle_array(int *arr, int size)
{
	int i;

	srand(time(NULL));
	
	for (i = 0; i < size; i++) {
		int j = 1 + (int)((double)i * rand() / (RAND_MAX+1.0));
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
}

void create_unordered_array(int *arr, int size, int min_v, int max_v)
{
	int i;
	int range = max_v - min_v + 1;

	if (range < size) {
		fprintf(stderr, "The range of values is less than array size\n");
		exit(1);
	}

	for (i = 0; i < size; i++)
        arr[i] = min_v + i;

	shuffle_array(arr, size);
}

#define MAX_ARR_SIZE 100

int main()
{
	int *arr = (int *) malloc(MAX_ARR_SIZE * sizeof(int));

	create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);
	print_array(arr, MAX_ARR_SIZE);
	quick_sort(arr, MAX_ARR_SIZE);
	print_array(arr, MAX_ARR_SIZE);

	free(arr);
}
