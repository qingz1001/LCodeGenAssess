#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    int must_do[K];
    for (int i = 0; i < K; ++i) {
        scanf("%d", &must_do[i]);
    }
    
    int can_do[MAXN];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &can_do[i]);
    }
    
    // Sort the days that must be done
    qsort(must_do, K, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    // Initialize variables
    int max_days = 0;
    int current_day = 0;
    int must_index = 0;
    
    while (current_day < N && must_index < K) {
        if (current_day == must_do[must_index]) {
            // Must do on this day
            if (can_do[current_day] != can_do[must_do[must_index]]) {
                printf("impossible\n");
                return 0;
            }
            ++must_index;
        } else {
            // Can choose to do or not do
            if (can_do[current_day] > can_do[current_day + 1]) {
                printf("impossible\n");
                return 0;
            }
            ++max_days;
        }
        ++current_day;
    }
    
    // Check remaining days
    while (current_day < N) {
        if (can_do[current_day] <= can_do[current_day + 1]) {
            ++max_days;
        } else {
            printf("impossible\n");
            return 0;
        }
        ++current_day;
    }
    
    printf("%d\n", max_days);
    return 0;
}