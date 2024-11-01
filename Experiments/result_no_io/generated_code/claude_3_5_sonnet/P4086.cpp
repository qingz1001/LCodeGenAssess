#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int scores[MAX_N];
double max_score = 0;
int best_k[MAX_N];
int best_k_count = 0;

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &scores[i]);
    }

    long long sum = 0;
    int min_score = 10001;

    for (int i = N - 1; i >= 2; i--) {
        sum += scores[i];
        if (scores[i] < min_score) {
            min_score = scores[i];
        }

        int k = N - i - 1;
        double avg = (double)(sum - min_score) / (N - k - 2);

        if (avg > max_score) {
            max_score = avg;
            best_k_count = 1;
            best_k[0] = k;
        } else if (avg == max_score) {
            best_k[best_k_count++] = k;
        }
    }

    for (int i = best_k_count - 1; i >= 0; i--) {
        printf("%d\n", best_k[i]);
    }

    return 0;
}