#include <stdio.h>
#include <stdlib.h>

#define MAXS 201

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, s, c;
    int stalls[MAXS];
    int gaps[MAXS];
    int i, total = 0;

    scanf("%d %d %d", &m, &s, &c);

    for (i = 0; i < c; i++) {
        scanf("%d", &stalls[i]);
    }

    qsort(stalls, c, sizeof(int), cmp);

    for (i = 1; i < c; i++) {
        gaps[i-1] = stalls[i] - stalls[i-1] - 1;
    }

    qsort(gaps, c-1, sizeof(int), cmp);

    total = stalls[c-1] - stalls[0] + 1;

    for (i = c-2; i >= c-m && i >= 0; i--) {
        total -= gaps[i];
    }

    printf("%d\n", total);

    return 0;
}