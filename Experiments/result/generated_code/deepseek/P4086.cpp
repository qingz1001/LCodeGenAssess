#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int scores[MAXN];
double max_avg = 0.0;

double calculate_average(int start, int end) {
    int min_score = scores[start];
    int sum = 0;
    for (int i = start; i <= end; i++) {
        if (scores[i] < min_score) {
            min_score = scores[i];
        }
        sum += scores[i];
    }
    sum -= min_score;
    return (double)sum / (end - start);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    for (int K = 1; K <= N - 2; K++) {
        double avg = calculate_average(K, N - 1);
        if (avg > max_avg) {
            max_avg = avg;
        }
    }

    for (int K = 1; K <= N - 2; K++) {
        double avg = calculate_average(K, N - 1);
        if (avg == max_avg) {
            printf("%d\n", K);
        }
    }

    return 0;
}