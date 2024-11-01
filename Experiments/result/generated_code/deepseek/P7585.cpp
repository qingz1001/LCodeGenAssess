#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int canDistribute(int *counts, int m, int n, int max_jealousy) {
    int children_needed = 0;
    for (int i = 0; i < m; i++) {
        children_needed += (counts[i] + max_jealousy - 1) / max_jealousy;
        if (children_needed > n) return 0;
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *counts = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &counts[i]);
    }

    qsort(counts, m, sizeof(int), compare);

    int left = 1, right = counts[0], mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (canDistribute(counts, m, n, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);

    free(counts);
    return 0;
}