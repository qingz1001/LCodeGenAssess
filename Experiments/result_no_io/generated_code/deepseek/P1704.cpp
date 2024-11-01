#include <stdio.h>
#include <stdlib.h>

#define MAXN 500000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int *p = (int *)malloc(K * sizeof(int));
    int *c = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    // Sort the days that must be used
    qsort(p, K, sizeof(int), compare);

    // Check if the sequence is strictly increasing
    for (int i = 1; i < K; i++) {
        if (c[p[i] - 1] <= c[p[i - 1] - 1]) {
            printf("impossible\n");
            free(p);
            free(c);
            return 0;
        }
    }

    // Calculate the maximum number of days
    int max_days = K;
    int last_c = c[p[K - 1] - 1];
    for (int i = p[K - 1]; i < N; i++) {
        if (c[i] > last_c) {
            max_days++;
            last_c = c[i];
        }
    }

    printf("%d\n", max_days);

    free(p);
    free(c);
    return 0;
}