#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int scores[MAX_N];
double sum[MAX_N];
int min[MAX_N];

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    sum[N-1] = scores[N-1];
    min[N-1] = scores[N-1];

    for (int i = N-2; i >= 0; i--) {
        sum[i] = sum[i+1] + scores[i];
        min[i] = (scores[i] < min[i+1]) ? scores[i] : min[i+1];
    }

    double max_score = 0;
    for (int K = 1; K <= N-2; K++) {
        double current_score = (sum[K] - min[K]) / (N - K - 1);
        if (current_score > max_score) {
            max_score = current_score;
        }
    }

    for (int K = 1; K <= N-2; K++) {
        double current_score = (sum[K] - min[K]) / (N - K - 1);
        if (current_score == max_score) {
            printf("%d\n", K);
        }
    }

    return 0;
}