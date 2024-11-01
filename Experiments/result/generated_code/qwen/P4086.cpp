#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int scores[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    qsort(scores, N, sizeof(int), compare);

    double max_avg = 0;
    for (int K = 0; K <= N - 3; K++) {
        double sum = 0;
        for (int i = K + 1; i < N; i++) {
            sum += scores[i];
        }
        if (sum / (N - K - 1) > max_avg) {
            max_avg = sum / (N - K - 1);
        }
    }

    for (int K = 0; K <= N - 3; K++) {
        double sum = 0;
        for (int i = K + 1; i < N; i++) {
            sum += scores[i];
        }
        if (sum / (N - K - 1) == max_avg) {
            printf("%d\n", K);
        }
    }

    return 0;
}