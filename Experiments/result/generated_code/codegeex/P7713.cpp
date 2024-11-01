#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *scores = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    // Sort the scores
    qsort(scores, n, sizeof(int), compare);

    // Distribute the operations to increase the lowest and highest scores
    for (int i = 0; i < m; i++) {
        scores[0]++;
        scores[n - 1]++;
    }

    // Sort again after distribution
    qsort(scores, n, sizeof(int), compare);

    // Calculate the final score
    long long result = 0;
    for (int i = 1; i < n - 1; i++) {
        result += scores[i];
    }

    printf("%lld\n", result);

    free(scores);
    return 0;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}