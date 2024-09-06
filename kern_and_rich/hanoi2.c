#include <stdio.h>
#include <stdlib.h> /* for atoi */

static void hanoi(int source, int target, int n)
{
    int tmp = 6 - source - target;

    if(n == 1)
        printf("%d: %d -> %d\n", n, source, target);
    else {
        hanoi(source, tmp, n-1);
        printf("%d: %d -> %d\n", n, source, target);
        hanoi(tmp, target, n-1);
    }
}

int main(int argc, char **argv)
{
    int n;
    if(argc < 2) {
        fprintf(stderr, "No parameter given\n");
        return 1;
    }
    n = atoi(argv[1]);
    if(n < 1) {
        fprintf(stderr, "Incorrect token count\n");
        return 2;
    }
    hanoi(1, 3, n);
    return 0;
}