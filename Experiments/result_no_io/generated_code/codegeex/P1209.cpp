#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, s, c;
    scanf("%d%d%d", &m, &s, &c);

    int *positions = (int*)malloc(c * sizeof(int));
    for (int i = 0; i < c; i++) {
        scanf("%d", &positions[i]);
    }

    qsort(positions, c, sizeof(int), cmp);

    int gaps[c - 1];
    for (int i = 0; i < c - 1; i++) {
        gaps[i] = positions[i + 1] - positions[i] - 1;
    }

    qsort(gaps, c - 1, sizeof(int), cmp);

    int total_length = positions[c - 1] - positions[0] + 1;
    for (int i = 0; i < m - 1; i++) {
        total_length -= gaps[i];
    }

    printf("%d\n", total_length);

    free(positions);
    return 0;
}