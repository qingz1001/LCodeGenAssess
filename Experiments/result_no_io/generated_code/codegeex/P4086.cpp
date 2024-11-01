#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int N;
    scanf("%d", &N);
    int scores[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    qsort(scores, N, sizeof(int), cmp);

    int max_avg = 0;
    int result[N-2];

    for (int k = 1; k < N-1; k++) {
        int avg = (scores[k] + scores[k+1] + scores[k+2]) / 3;
        if (avg > max_avg) {
            max_avg = avg;
        }
    }

    for (int k = 1; k < N-1; k++) {
        int avg = (scores[k] + scores[k+1] + scores[k+2]) / 3;
        if (avg == max_avg) {
            result[k-1] = k;
        }
    }

    qsort(result, N-2, sizeof(int), cmp);

    for (int i = 0; i < N-2; i++) {
        if (result[i] != 0) {
            printf("%d\n", result[i]);
        }
    }

    return 0;
}