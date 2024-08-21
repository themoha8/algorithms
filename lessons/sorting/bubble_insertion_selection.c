#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <time.h>

typedef int bool;

enum { false = 0, true };

void insertion_sort1(int *nums, int size)
{
	int i, j;

	for (i = 1; i < size; i++)
		for (j = i; j > 0 && nums[j-1] > nums[j]; j--) {
			int tmp = nums[j-1];
			nums[j-1] = nums[j];
			nums[j] = tmp;
		}
}

/*
void insertion_sort1(int *nums, int size)
{
	int i, j, c = 0;

	for (i = 1; i < size; i++) {
		c++;
		for (j = i; j > 0 && nums[j-1] > nums[j]; j--) {
			c++;
			int tmp = nums[j-1];
			nums[j-1] = nums[j];
			nums[j] = tmp;
		}
	}
	printf("cound: %d\n", c);
}
*/

void insertion_sort2(int *nums, int size)
{
	int i, j;

	for (i = 1; i < size; i++) {
		int cur = nums[i];

		for (j = i-1; j >= 0 && nums[j] > cur; j--)
			nums[j+1] = nums[j];
		nums[j+1] = cur;
	}
}

/*
void insertion_sort2(int *nums, int size)
{
	int i, j, c = 0;

	for (i = 1; i < size; i++) {
		c++;
		int cur = nums[i];

		for (j = i-1; j >= 0 && nums[j] > cur; j--) {
			c++;
			nums[j+1] = nums[j];
		}
		nums[j+1] = cur;
	}
	printf("cound: %d\n", c);
}
*/

void bubble_sort1(int *nums, int size)
{
	int i, j;

	for (i = 0; i < size-1; i++)
		for (j = 0; j < size-i-1; j++)
			if (nums[j] > nums[j+1]) {
				int tmp = nums[j+1];
				nums[j+1] = nums[j];
				nums[j] = tmp;
			}
}

void bubble_sort2(int *nums, int size)
{
	int i, j;

	for (i = 0; i < size-1; i++) {
		bool swapped = false;
		
		for (j = 0; j < size-i-1; j++)
			if (nums[j] > nums[j+1]) {
				int tmp = nums[j+1];
				nums[j+1] = nums[j];
				nums[j] = tmp;
				swapped = true;
			}

		if (!swapped)
			break;
	}
}

void selection_sort(int *nums, int size)
{
	int i, j;

	for (i = 0; i < size-1; i++) {
		int tmp;
		int min_idx = i;
		
		for (j = i+1; j < size; j++)
			if (nums[min_idx] > nums[j])
				min_idx = j;
		
		tmp = nums[i];
		nums[i] = nums[min_idx];
		nums[min_idx] = tmp;
	}
}

/*
void selection_sort(int *nums, int size)
{
	int i, j, c = 0;

	for (i = 0; i < size-1; i++) {
		c++;
		int tmp;
		int min_idx = i;
		
		for (j = i+1; j < size; j++) {
			c++;
			if (nums[min_idx] > nums[j])
				min_idx = j;
		}
		
		tmp = nums[i];
		nums[i] = nums[min_idx];
		nums[min_idx] = tmp;
	}
	printf("count: %d\n", c);
}
*/

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

#define MAX_ARR_SIZE 200000

int main(void)
{
	/* completely sorted (6 elements)
	 * bubble_sort - O(N^2) (20)
	 * selection_sort - O(N^2) (20)
	 * bubble_sort2 O(N) (6)
	 * insertion_sort1 O(N) (5)
	 * int n[] = { 1, 2, 3, 4, 5, 6 };
	 */

	/* almost sorted (6 elements)
	 * bubble_sort - O(N^2) (20)
	 * selection_sort - O(N^2) (20)
	 * bubble_sort2 O(N^2) (15)
	 * insertion_sort1 O(N^2) (12)
	 * int n2[] = { 5, 3, 1, 2, 6, 4 };
	 */

	/* not sorted at all (6 elements)
	 * bubble_sort, bubble_sort2, insertion_sort, selection_sort - O(N^2) (20)
	 * int n3[] = { 6, 5, 4, 3, 2, 1 };
	 */

	int *arr = (int *) malloc(MAX_ARR_SIZE * sizeof(int));
	create_unordered_array(arr, MAX_ARR_SIZE, 0, MAX_ARR_SIZE-1);
	//print_array(arr, MAX_ARR_SIZE);
	insertion_sort2(arr, MAX_ARR_SIZE);
	//selection_sort(arr, MAX_ARR_SIZE);
	//print_array(arr, MAX_ARR_SIZE);

	free(arr);
	return 0;
}
