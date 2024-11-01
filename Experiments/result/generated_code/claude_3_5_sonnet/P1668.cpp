#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25001
#define MAX_T 1000001

typedef struct {
    int start;
    int end;
} Shift;

int compare(const void *a, const void *b) {
    return ((Shift *)a)->start - ((Shift *)b)->start;
}

int main() {
    int N, T;
    Shift shifts[MAX_N];
    int dp[MAX_T] = {0};
    
    scanf("%d %d", &N, &T);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &shifts[i].start, &shifts[i].end);
    }
    
    qsort(shifts, N, sizeof(Shift), compare);
    
    for (int i = 0; i <= T; i++) {
        dp[i] = MAX_T;
    }
    dp[0] = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = shifts[i].end; j >= shifts[i].start; j--) {
            if (dp[shifts[i].start - 1] != MAX_T && dp[j] > dp[shifts[i].start - 1] + 1) {
                dp[j] = dp[shifts[i].start - 1] + 1;
            }
        }
    }
    
    if (dp[T] == MAX_T) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[T]);
    }
    
    return 0;
}