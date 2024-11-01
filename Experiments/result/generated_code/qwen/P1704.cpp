#include <stdio.h>
#include <stdlib.h>

#define MAXN 500000

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int must[N + 1];
    for (int i = 0; i < K; ++i) {
        scanf("%d", &must[i]);
    }
    long long c[MAXN + 1];
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &c[i]);
    }

    // Sort the must array to process days in ascending order
    qsort(must, K, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // Initialize the answer and variables
    int max_days = 0;
    int current_day = 1;

    // Iterate through each day
    while (current_day <= N) {
        if (max_days == K) {
            break;
        }
        if (current_day == must[max_days]) {
            // If it's a mandatory day, check if we can do more than one problem
            if (c[current_day] > 1) {
                ++max_days;
                --current_day;
            } else {
                printf("impossible\n");
                return 0;
            }
        } else {
            // Otherwise, try to do as many problems as possible without exceeding capacity
            while (current_day <= N && c[current_day] > 0) {
                --c[current_day];
                ++max_days;
            }
        }
        ++current_day;
    }

    printf("%d\n", max_days);
    return 0;
}