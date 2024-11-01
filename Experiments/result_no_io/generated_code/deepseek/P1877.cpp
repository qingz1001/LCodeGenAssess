#include <stdio.h>
#include <stdbool.h>

#define MAX_LEVEL 1000
#define MAX_N 50

int main() {
    int n, beginLevel, maxLevel;
    int c[MAX_N];
    bool dp[MAX_N + 1][MAX_LEVEL + 1];

    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    // Initialize dp array
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxLevel; j++) {
            dp[i][j] = false;
        }
    }
    dp[0][beginLevel] = true;

    // Fill dp array
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= maxLevel; j++) {
            if (dp[i - 1][j]) {
                if (j + c[i - 1] <= maxLevel) dp[i][j + c[i - 1]] = true;
                if (j - c[i - 1] >= 0) dp[i][j - c[i - 1]] = true;
            }
        }
    }

    // Find the maximum volume at the last song
    int maxVolume = -1;
    for (int j = 0; j <= maxLevel; j++) {
        if (dp[n][j]) {
            maxVolume = j;
        }
    }

    printf("%d\n", maxVolume);

    return 0;
}