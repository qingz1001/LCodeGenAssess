#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    double k;
    scanf("%d %lf", &n, &k);

    int *d = (int *)malloc(n * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    int *used = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    qsort(d, n, sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        int parent = (int)(i / k);
        while (used[parent]) {
            parent++;
        }
        result[i] = d[parent];
        used[parent] = 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(d);
    free(result);
    free(used);

    return 0;
}