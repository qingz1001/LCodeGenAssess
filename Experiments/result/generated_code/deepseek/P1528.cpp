#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d", &n);
    int *cakes = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }

    scanf("%d", &m);
    int *mouths = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }

    qsort(cakes, n, sizeof(int), compare);
    qsort(mouths, m, sizeof(int), compare);

    int count = 0;
    int j = 0;
    for (int i = 0; i < m; i++) {
        while (j < n && cakes[j] < mouths[i]) {
            j++;
        }
        if (j < n) {
            count++;
            j++;
        }
    }

    printf("%d\n", count);

    free(cakes);
    free(mouths);
    return 0;
}