#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, dist;
    int positions[MAX_N];
    
    scanf("%d %d", &n, &dist);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }
    
    qsort(positions, n, sizeof(int), compare);
    
    int dp[MAX_N] = {0};
    dp[0] = 0;
    dp[1] = 0;
    
    for (int i = 2; i < n; i++) {
        dp[i] = dp[i-1];
        int j = i - 1;
        while (j > 0 && positions[i] - positions[j] <= dist) {
            dp[i] = (dp[j-1] + i - j > dp[i]) ? dp[j-1] + i - j : dp[i];
            j--;
        }
    }
    
    printf("%d\n", dp[n-1]);
    
    return 0;
}