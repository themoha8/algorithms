#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../hashtable.h"

enum { max_keys = 1024, max_line_length = 64 };

static char arr_keys[max_keys][max_line_length];

void search_collisions(hash_table * h)
{
	int collisions = 0;
	int deep_collision = 0;
	int max_deep_collision = 0;
	int max_deep_collision_idx;
	int i;
	item *it, *tmp;

	for (i = 0; i < h->size; i++) {
		it = h->ht[i];
		while (it != NULL) {
			tmp = it;
			it = it->next;
			if (it) {
				deep_collision++;
				collisions++;
				printf("collision index: %d (%s)\n", i, tmp->key);
				if (it->next == NULL)
					printf("collision index: %d (%s)\n", i, it->key);
			}
		}
		if (deep_collision > max_deep_collision) {
			max_deep_collision = deep_collision;
			max_deep_collision_idx = i;
		}
		deep_collision = 0;
	}

	printf("ht count: %d\n", h->count);
	printf("ht size: %d\n", h->size);
	printf("the number of collisions: %d\n", collisions);
	printf("max collision deep: %d (index: %d)\n", max_deep_collision, max_deep_collision_idx);
}

int main(void)
{
	FILE *fd;
	int i = 0, ch;
	char *nl;
	hash_table *ht;

	ht = ht_init();

	fd = fopen("tests/thousand_keys.txt", "r");
	if (!fd) {
		perror("thousand_keys.txt");
		return 2;
	}

	while (fgets(arr_keys[i], max_line_length, fd)) {

		if (i > max_keys) {
			fprintf(stderr, "Buf size is exceeded. Max_keys: %d", max_keys);
			break;
		}

		nl = strchr(arr_keys[i], '\n');
		if (!nl) {
			while ((ch = fgetc(fd)) != '\n' && ch != EOF);
			if (ch == EOF) {
				fprintf(stderr, "No newline at end of file\n");
				break;
			} else {
				fprintf(stderr, "Line (%d) too long\n", i);
				continue;
			}
		} else {
			*nl = '\0';
			ht_insert(ht, arr_keys[i], i);
		}
		i++;
	}

	ht_delete(ht, "day");
	ht_delete(ht, "colour");
	ht_delete(ht, "screen");
	ht_delete(ht, "hell");
	search_collisions(ht);
	fclose(fd);
	ht_free(ht);
	return 0;
}
