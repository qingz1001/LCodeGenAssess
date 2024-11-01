#include <stdio.h>

int main() {
    int n, beginLevel, maxLevel;
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    
    int changes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &changes[i]);
    }
    
    int dp[maxLevel + 1];
    for (int i = 0; i <= maxLevel; i++) {
        dp[i] = 0;
    }
    dp[beginLevel] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = maxLevel; j >= 0; j--) {
            if (dp[j] && j + changes[i] <= maxLevel) {
                dp[j + changes[i]] = 1;
            }
            if (dp[j] && j - changes[i] >= 0) {
                dp[j - changes[i]] = 1;
            }
        }
    }
    
    for (int i = maxLevel; i >= 0; i--) {
        if (dp[i]) {
            printf("%d\n", i);
            return 0;
        }
    }
    
    printf("-1\n");
    return 0;
}