#include <stdio.h>
#include <stdlib.h> /* malloc */

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

static void counting_sort(const int *n, int size)
{
	int i, j;
	int arr_size, min_val;

	i = max_value(n, size);
	j = min_value(n, size);
	if (i != -1 && j != -1)
		arr_size = n[i] - n[j] + 1;

	int *nums = malloc(arr_size*4);
	for (i = 0; i < arr_size; i++)
		nums[i] = 0;

	min_val = n[j];
	for (i = 0; i < size; i++) {
		int now = n[i];
		nums[now - min_val]++;
	}

	for (i = 0; i < arr_size; i++) {
		for (j = nums[i]; j > 0; j--)
			printf("%d ", i+min_val);
	}
	printf("\n");
	free(nums);

}

int main(void)
{
	int nums[] = { 5, 4, 3, 3, 3, 4, 2 };

	counting_sort(nums, sizeof(nums)/4);
	return 0;
}