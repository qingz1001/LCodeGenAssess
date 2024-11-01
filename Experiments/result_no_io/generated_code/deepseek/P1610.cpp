#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int max_lights_to_remove(int n, int dist, int *positions) {
    qsort(positions, n, sizeof(int), compare);
    
    int dp[n];
    dp[0] = 0;
    dp[1] = 0;
    
    for (int i = 2; i < n - 1; i++) {
        if (positions[i] - positions[i - 2] <= dist) {
            dp[i] = dp[i - 1] + 1;
        } else {
            dp[i] = dp[i - 1];
        }
    }
    
    return dp[n - 2];
}

int main() {
    int n, dist;
    scanf("%d %d", &n, &dist);
    
    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }
    
    int result = max_lights_to_remove(n, dist, positions);
    printf("%d\n", result);
    
    return 0;
}