#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <time.h>

#define INSERTION_SORT_THRESHOLD 4

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

static void merge(int *nums, int *tmp, int start, int mid, int end)
{
	int i = start;
	int j = mid + 1;
	int k = start;

	while (i <= mid && j <= end) {
		if (nums[i] <= nums[j])
			tmp[k++] = nums[i++];
		else
			tmp[k++] = nums[j++];
	}

	while (i <= mid)
		tmp[k++] = nums[i++];

	while (j <= end)
		tmp[k++] = nums[j++];	

	for (int i = start; i <= end; i++)
		nums[i] = tmp[i];
}

void merge_sort(int *nums, int *tmp, int start, int end)
{
	if (end - start + 1 <= INSERTION_SORT_THRESHOLD) {
	 	insertion_sort(nums, start, end);
	 	return;
	}

	if (start < end) {
		int mid = start + (end-start) / 2;

		merge_sort(nums, tmp, start, mid);
		merge_sort(nums, tmp, mid+1, end);
	
		merge(nums, tmp, start, mid, end);
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

#define MAX_ARR_SIZE 2000000

int main(void)
{
	int *arr = (int *) malloc(MAX_ARR_SIZE * sizeof(int));
	int *tmp = (int *) malloc(MAX_ARR_SIZE * sizeof(int));

	create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);
	//print_array(arr, MAX_ARR_SIZE);
	merge_sort(arr, tmp, 0, MAX_ARR_SIZE-1);
	//print_array(arr, MAX_ARR_SIZE);

	free(arr);
	free(tmp);
	return 0;
}
