#include <stdio.h>

void digit_count(int *digit_count, int n)
{
	while (n > 0) {
		int last_digit = n % 10;
		digit_count[last_digit]++;
		n = n / 10;
	}
}

int is_digit_permutation(int x, int y)
{
	int i;
	int digit_count_x[10]; /* 0 ... 9 */
	int digit_count_y[10];

	for (i = 0; i < 10; i++) {
		digit_count_x[i] = 0;
		digit_count_y[i] = 0;
	}

	digit_count(digit_count_x, x);
	digit_count(digit_count_y, y);
	for (i = 0; i < 10; i++)
		if (digit_count_x[i] != digit_count_y[i])
			return 0;

	return 1;
}

int main(void)
{
	int x = 2023;
	int y = 2320;

	if (is_digit_permutation(x, y))
		printf("digits permutation for numbers %d and %d: true\n", x, y);
	else
		printf("digits permutation for numbers %d and %d: false\n", x, y);

	return 0;
}