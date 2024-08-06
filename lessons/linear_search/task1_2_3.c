#include <stdio.h>

const int nums[] = { 1, 2, 3, 2, 5 };

/* find left occurence */
static int left_findx(const int *n, int nlen, int x) {
	int i;

	for (i = 0; i < nlen; i++) {
		if (n[i] == x)
			return i;
	}
	return -1;
}

/* find right occurence */
static int right_findx(const int *n, int nlen, int x) {
	while(--nlen) {
		if (n[nlen] == x)
			return nlen;
	}
	return -1;
}

/* find max value (index) */
static int max_value(const int *n, int nlen) {
	int i_max, i;

	if (nlen > 0)
		i_max = 0;
	else
		return -1;

	for (i = 1; i < nlen; i++)
		if (n[i] > n[i_max])
			i_max = i;

	return i_max;
}

/* find two max value (index) */
static int max2_value(const int *n, int nlen, int *i_max1, int *i_max2)
{
	int i;

	if (nlen > 1) {
		if (n[0] > n[1]) {
			*i_max1 = 0;
			*i_max2 = 1;
		}
		else {
			*i_max1 = 1;
			*i_max2 = 0;
		}
	}
	else
		return -1;

	for (i = 2; i < nlen; i++)
		if (n[i] > n[*i_max1]) {
			*i_max2 = *i_max1;
			*i_max1 = i;
		}
		else if (n[i] > n[*i_max2])
			*i_max2 = i;

	return 0;
}

/* find min even number */
static int min_even_num(const int *n, int nlen)
{
	int i_emin = -1, i;

	for (i = 0; i < nlen; i++)
		if (n[i] % 2 == 0 && (i_emin == -1 || n[i] < n[i_emin]))
			i_emin = i;

	return i_emin;
}

/* find min even number (version 2)*/
static int min_even_num2(const int *n, int nlen)
{
	int i_emin = -1, f_find = 0, i;

	for (i = 0; i < nlen; i++)
		if (n[i] % 2 == 0 && (!f_find || n[i] < n[i_emin])) {
			i_emin = i;
			f_find = 1;
		}

	return i_emin;
}

int main(void)
{
	int index2;

	int index = left_findx(nums, sizeof(nums)/4, 2);
	printf("index (left occurence): %d\tvalue: %d\n", index, nums[index]);

	index = right_findx(nums, sizeof(nums)/4, 2);
	printf("index (right occurence): %d\tvalue: %d\n", index, nums[index]);

	index = max_value(nums, sizeof(nums)/4);
	printf("index (max value): %d\tvalue: %d\n", index, nums[index]);

	max2_value(nums, sizeof(nums)/4, &index, &index2);
	printf("index1 (max2_value): %d\tvalue: %d\t\tindex2 (max2_value): %d\t"
		   "value: %d\n", index, nums[index], index2, nums[index2]);

	index = min_even_num2(nums, sizeof(nums)/4);
	printf("index (min_even_num): %d\tvalue: %d\n", index, nums[index]);
	return 0;
}
