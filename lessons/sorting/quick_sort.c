#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <time.h> /* time */

static void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *arr, int start, int end)
{
	int pivot = arr[end];
	int j, i = start-1;

	for (j = start; j < end; j++)
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}

	swap(&arr[i+1], &arr[end]);

	return i+1;
}

void quick_sort(int *arr, int start, int end)
{
	if (start < end) {
		int pivot = partition(arr, start, end);

		quick_sort(arr, start, pivot-1);
		quick_sort(arr, pivot+1, end);
	}
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

#define MAX_ARR_SIZE 8

int main(void)
{
	int *arr = (int *) malloc(MAX_ARR_SIZE * sizeof(int));

	create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);
	print_array(arr, MAX_ARR_SIZE);
	quick_sort(arr, 0, MAX_ARR_SIZE-1);
	print_array(arr, MAX_ARR_SIZE);

	free(arr);
	return 0;
}