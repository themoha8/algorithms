#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;

	if (agrc == 1)
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				printf("\n");
			}
}