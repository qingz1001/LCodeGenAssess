#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(double*)a - *(double*)b);
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    double lengths[N];
    for (int i = 0; i < N; i++) {
        scanf("%lf", &lengths[i]);
    }

    qsort(lengths, N, sizeof(double), compare);

    double max_length = 0.0;
    if (N >= K) {
        max_length = lengths[N - K] / K;
    }

    printf("%.2f\n", max_length);

    return 0;
}