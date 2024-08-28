#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <time.h> /* time */

#define INSERTION_SORT_THRESHOLD 16

static void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

static void insertion_sort(int *nums, int start, int end)
{
	int i, j;

	for (i = start + 1; i <= end; i++) {
		int cur = nums[i];

		for (j = i-1; j >= start && nums[j] > cur; j--)
			nums[j+1] = nums[j];
		nums[j+1] = cur;
	}
}

int median_of_three(int *arr, int start, int end)
{
	int mid = start + (end-start)/2;

	if (arr[start] > arr[mid])
		swap(&arr[start], &arr[mid]);
	if (arr[start] > arr[end])
		swap(&arr[start], &arr[end]);
	if (arr[mid] > arr[end])
		swap(&arr[mid], &arr[end]);

	return mid;
}

int partition(int *arr, int start, int end)
{
	int pivot, pivot_index = median_of_three(arr, start, end);
	swap(&arr[pivot_index], &arr[end]);
	pivot = arr[end];
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
	if (end - start + 1 <= INSERTION_SORT_THRESHOLD) {
	 	insertion_sort(arr, start, end);
	 	return;
	}

	if (start < end) {
		int pivot = partition(arr, start, end);

		quick_sort(arr, start, pivot-1);
		quick_sort(arr, pivot+1, end);
	}
}

void quick_sort2(int *arr, int start, int end)
{
	while (start < end) {
		if (end - start + 1 <= INSERTION_SORT_THRESHOLD) {
	 		insertion_sort(arr, start, end);
	 		return;
		}

		int pivot_index = partition(arr, start, end);

		if (pivot_index - start < end - pivot_index) {
			quick_sort2(arr, start, pivot_index-1);
			start = pivot_index + 1;
		} else {
			quick_sort2(arr, pivot_index+1, end);
		 	end	= pivot_index - 1;
		}
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

#define MAX_ARR_SIZE 30000000

int main(void)
{
	int *arr = (int *) malloc(MAX_ARR_SIZE * sizeof(int));

	create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);

	//print_array(arr, MAX_ARR_SIZE);
	quick_sort2(arr, 0, MAX_ARR_SIZE-1);
	//print_array(arr, MAX_ARR_SIZE);
	//printf("count: %d\n", c);

	free(arr);
	return 0;
}
