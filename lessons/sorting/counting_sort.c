#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <time.h> /* time */

static int min_value(const int *n, int size) {
	int i_min, i;

	if (size > 0)
		i_min = 0;
	else
		return -1;

	for (i = 1; i < size; i++)
		if (n[i] < n[i_min])
			i_min = i;

	return i_min;
}

static int max_value(const int *n, int size) {
	int i_max, i;

	if (size > 0)
		i_max = 0;
	else
		return -1;

	for (i = 1; i < size; i++)
		if (n[i] > n[i_max])
			i_max = i;

	return i_max;
}

static int max_value2(const int *n, int size) {
	int i_max, i;
	
	i_max = 0;
	for (i = 1; i < size; i++)
		if (n[i] > n[i_max])
			i_max = i;

	return n[i_max];
}

static void counting_sort(int *n, int size)
{
	int i, j, k = 0;
	int arr_size, min_val;

	i = max_value(n, size);
	j = min_value(n, size);
	if (i != -1 && j != -1)
		arr_size = n[i] - n[j] + 1;
	else {
		fprintf(stderr, "counting_sort: error: array size equal 0\n");
		return;
	}

	int *nums = malloc(arr_size*4);
	for (i = 0; i < arr_size; i++)
		nums[i] = 0;

	min_val = n[j];
	for (i = 0; i < size; i++) {
		int now = n[i];
		nums[now - min_val]++;
	}

	for (i = 0; i < arr_size; i++)
		for (j = nums[i]; j > 0; j--)
			n[k++] = i+min_val;

	free(nums);
}

static void counting_sort2(int *n, int size)
{
	int i, j, k = 0;
	int arr_size;

	arr_size = max_value2(n, size) + 1;

	int *nums = (int*)malloc(arr_size*4);
	for (i = 0; i < arr_size; i++)
		nums[i] = 0;

	for (i = 0; i < size; i++)
		nums[n[i]]++;

	for (i = 0; i < arr_size; i++)
		for (j = nums[i]; j > 0; j--)
			n[k++] = i;

	free(nums);
}

void print_array(const int *nums, int size)
{
	int i;

	printf("array elements: ");
	for (i = 0; i < size; i++)
		printf("%d ", nums[i]);
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
	//int *arr = (int *) malloc(MAX_ARR_SIZE * sizeof(int));
	int arr[] = { 0, 5, 2, 2, 5, 8, 10, 23, 14, 55, 42, 22, 22, 2, 2, 4 };
	//create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);
	print_array(arr, sizeof(arr)/4);
	counting_sort2(arr, sizeof(arr)/4);
	print_array(arr, sizeof(arr)/4);

	//free(arr);
	return 0;
}
