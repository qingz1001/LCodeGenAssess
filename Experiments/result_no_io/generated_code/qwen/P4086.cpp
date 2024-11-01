#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_SCORE 10000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int scores[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    qsort(scores, N, sizeof(int), compare);

    int max_score = 0;
    int best_Ks[MAX_N];
    int count = 0;

    for (int K = 0; K <= N - 3; K++) {
        int sum = 0;
        for (int i = K + 1; i < N; i++) {
            sum += scores[i];
        }
        int avg = sum / (N - K - 1);
        if (avg > max_score) {
            max_score = avg;
            count = 0;
        }
        if (avg == max_score) {
            best_Ks[count++] = K;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d\n", best_Ks[i]);
    }

    return 0;
}