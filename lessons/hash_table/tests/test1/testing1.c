#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_table.h"

#define MAX_KEYS 1000
#define MAX_LINE_LENGTH 64

static char arr_keys[MAX_KEYS][MAX_LINE_LENGTH];

int main(void)
{
	FILE *fd;
	int i;
	hash_table *ht;

	fd = fopen("thousand_keys.txt", "r");
	if (!fd) {
		perror("thousand_keys.txt");
		return 1;
	}

	for (i = 0; i < MAX_KEYS; i++) {
		if (fgets(arr_keys[i], MAX_LINE_LENGTH, fd) == NULL)
			break;
	}

	ht = ht_init();
	while(--i >= 0) {
		int val;
		srand(time(NULL));
		val = rand() + 123;
		ht_insert(ht, arr_keys[i], val);
	}

	printf("number of element in hash_table: %d\n", ht->ht_count);
	ht_free(ht);
	fclose(fd);
	return 0;
}