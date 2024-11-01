#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *containers = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &containers[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &weights[i]);
    }

    // Sort containers and weights in descending order
    qsort(containers, n, sizeof(int), greater);
    qsort(weights, m, sizeof(int), greater);

    int count = 0;
    int containerIndex = 0;

    // Use a two-pointer technique to maximize the number of weights
    for (int i = 0; i < m; i++) {
        if (containerIndex < n && containers[containerIndex] >= weights[i]) {
            count++;
            containers[containerIndex] -= weights[i];
            // Sort containers again to maintain descending order
            qsort(containers, n, sizeof(int), greater);
            containerIndex++;
        }
    }

    printf("%d\n", count);

    free(containers);
    free(weights);

    return 0;
}

// Comparison function for qsort in descending order
int greater(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}