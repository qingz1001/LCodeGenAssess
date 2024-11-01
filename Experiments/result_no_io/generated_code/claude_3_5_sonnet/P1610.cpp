#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, dist;
    int positions[MAX_N];
    int dp[MAX_N];
    
    scanf("%d %d", &n, &dist);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }
    
    qsort(positions, n, sizeof(int), compare);
    
    dp[0] = 0;
    dp[1] = 0;
    
    for (int i = 2; i < n; i++) {
        if (positions[i] - positions[i-2] <= dist) {
            dp[i] = dp[i-1] + 1;
        } else {
            dp[i] = dp[i-1];
        }
    }
    
    printf("%d\n", dp[n-1]);
    
    return 0;
}