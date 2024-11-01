#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_M 10000

int main() {
    int N;
    scanf("%d", &N);
    int M[MAX_N];
    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &M[i]);
        sum += M[i];
    }

    double min_avg = sum / (double)(N - 1);
    for (int i = 1; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            long long sub_sum = 0;
            for (int k = 0; k < i; ++k) {
                sub_sum += M[k];
            }
            for (int k = j; k < N; ++k) {
                sub_sum += M[k];
            }
            double avg = sub_sum / (double)(N - (j - i + 1));
            if (avg < min_avg) {
                min_avg = avg;
            }
        }
    }

    printf("%.3f\n", min_avg);
    return 0;
}