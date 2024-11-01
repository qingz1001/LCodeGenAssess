#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 25001
#define MAX_T 1000001

typedef struct {
    int start;
    int end;
} Shift;

int cmp(const void *a, const void *b) {
    return ((Shift*)a)->start - ((Shift*)b)->start;
}

int main() {
    int N, T;
    Shift shifts[MAX_N];
    int dp[MAX_T];
    
    scanf("%d %d", &N, &T);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &shifts[i].start, &shifts[i].end);
    }
    
    qsort(shifts, N, sizeof(Shift), cmp);
    
    for (int i = 0; i <= T; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    
    for (int i = 0; i < N; i++) {
        if (shifts[i].start == 1) {
            dp[shifts[i].end] = 1;
        } else if (dp[shifts[i].start - 1] != INT_MAX) {
            for (int j = shifts[i].start; j <= shifts[i].end; j++) {
                if (dp[j] > dp[shifts[i].start - 1] + 1) {
                    dp[j] = dp[shifts[i].start - 1] + 1;
                }
            }
        }
    }
    
    if (dp[T] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[T]);
    }
    
    return 0;
}