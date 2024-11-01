#include <stdio.h>
#include <stdlib.h>

#define MAX_S 200

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, s, c;
    int stalls[MAX_S];
    int gaps[MAX_S - 1];
    int total_length = 0;

    scanf("%d %d %d", &m, &s, &c);

    for (int i = 0; i < c; i++) {
        scanf("%d", &stalls[i]);
    }

    qsort(stalls, c, sizeof(int), compare);

    for (int i = 0; i < c - 1; i++) {
        gaps[i] = stalls[i + 1] - stalls[i] - 1;
    }

    qsort(gaps, c - 1, sizeof(int), compare);

    total_length = stalls[c - 1] - stalls[0] + 1;

    for (int i = 0; i < c - 1 && i < m - 1; i++) {
        total_length -= gaps[c - 2 - i];
    }

    printf("%d\n", total_length);

    return 0;
}