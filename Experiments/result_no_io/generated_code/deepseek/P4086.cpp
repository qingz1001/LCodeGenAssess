#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int scores[MAXN];
double max_avg = 0.0;

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    // Calculate the sum and minimum of the last N-2 scores
    long long sum = 0;
    int min_score = 10001;
    for (int i = 1; i < N; i++) {
        sum += scores[i];
        if (scores[i] < min_score) {
            min_score = scores[i];
        }
    }

    // Calculate the initial average for K = 1
    double current_avg = (double)(sum - min_score) / (N - 2);
    max_avg = current_avg;

    // Calculate the average for each K from 1 to N-2
    for (int K = 1; K <= N - 2; K++) {
        sum -= scores[K];
        if (scores[K] == min_score) {
            min_score = 10001;
            for (int i = K + 1; i < N; i++) {
                if (scores[i] < min_score) {
                    min_score = scores[i];
                }
            }
        }
        current_avg = (double)(sum - min_score) / (N - K - 1);
        if (current_avg > max_avg) {
            max_avg = current_avg;
        }
    }

    // Re-calculate the averages and print the K values that give the maximum average
    sum = 0;
    min_score = 10001;
    for (int i = 1; i < N; i++) {
        sum += scores[i];
        if (scores[i] < min_score) {
            min_score = scores[i];
        }
    }

    for (int K = 1; K <= N - 2; K++) {
        sum -= scores[K];
        if (scores[K] == min_score) {
            min_score = 10001;
            for (int i = K + 1; i < N; i++) {
                if (scores[i] < min_score) {
                    min_score = scores[i];
                }
            }
        }
        current_avg = (double)(sum - min_score) / (N - K - 1);
        if (current_avg == max_avg) {
            printf("%d\n", K);
        }
    }

    return 0;
}