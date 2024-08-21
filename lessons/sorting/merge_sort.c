#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <time.h>

static void merge(int *nums, int start, int mid, int end)
{
	int i, j, k;
	int lhalf_size = mid - start + 1;
	int rhalf_size = end - mid;

	int *lhalf = (int *) malloc(lhalf_size * sizeof(int));
	int *rhalf = (int *) malloc(rhalf_size * sizeof(int));

	/* copy elements of left part */
	for (i = 0; i < lhalf_size; i++)
		lhalf[i] = nums[start+i];
	/* copy elements of right part */
	for (j = 0; j < rhalf_size; j++)
		rhalf[j] = nums[mid+1+j];

	/* merge */
	i = 0;
	j = 0;
	k = start;
	while (i < lhalf_size && j < rhalf_size) {
		if (lhalf[i] <= rhalf[j]) {
			nums[k] = lhalf[i];
			i++;
		} else {
			nums[k] = rhalf[j];
			j++;
		}
		k++;
	}

	while (i < lhalf_size) {
		nums[k] = lhalf[i];
		i++;
		k++;
	}

	while (j < rhalf_size) {
		nums[k] = rhalf[j];
		j++;
		k++;
	}

	free(lhalf);
	free(rhalf);
}

void merge_sort(int *nums, int start, int end)
{
	if (start < end) {
		int mid = start + (end-start) / 2;
		merge_sort(nums, start, mid);
		merge_sort(nums, mid+1, end);
	
		merge(nums, start, mid, end);
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

	create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);
	//print_array(arr, MAX_ARR_SIZE);
	merge_sort(arr, 0, MAX_ARR_SIZE-1);
	//print_array(arr, MAX_ARR_SIZE);

	free(arr);
	return 0;
}
