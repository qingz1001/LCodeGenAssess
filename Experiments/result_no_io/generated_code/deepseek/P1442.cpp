#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int height;
    int left;
    int right;
} Platform;

int comparePlatforms(const void *a, const void *b) {
    return ((Platform *)a)->height - ((Platform *)b)->height;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    
    int x, y;
    scanf("%d %d", &x, &y);
    
    Platform platforms[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
    }
    
    // Sort platforms by height in descending order
    qsort(platforms, n, sizeof(Platform), comparePlatforms);
    
    // Initialize dp array with maximum possible time
    int dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    
    // Start from the ground
    dp[n] = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (dp[j] == INT_MAX) continue;
            
            int fall_height = platforms[i].height - (j == n ? 0 : platforms[j].height);
            if (fall_height > h) continue;
            
            int left_time = INT_MAX, right_time = INT_MAX;
            
            if (platforms[i].left >= platforms[j].left && platforms[i].left <= platforms[j].right) {
                left_time = dp[j] + platforms[i].left - platforms[j].left;
            }
            
            if (platforms[i].right >= platforms[j].left && platforms[i].right <= platforms[j].right) {
                right_time = dp[j] + platforms[j].right - platforms[i].right;
            }
            
            dp[i] = min(dp[i], min(left_time, right_time) + fall_height);
        }
    }
    
    int result = INT_MAX;
    for (int i = 0; i <= n; i++) {
        if (dp[i] == INT_MAX) continue;
        
        int fall_height = y - (i == n ? 0 : platforms[i].height);
        if (fall_height > h) continue;
        
        int left_time = INT_MAX, right_time = INT_MAX;
        
        if (x >= platforms[i].left && x <= platforms[i].right) {
            left_time = dp[i] + x - platforms[i].left;
            right_time = dp[i] + platforms[i].right - x;
        }
        
        result = min(result, min(left_time, right_time) + fall_height);
    }
    
    printf("%d\n", result);
    
    return 0;
}