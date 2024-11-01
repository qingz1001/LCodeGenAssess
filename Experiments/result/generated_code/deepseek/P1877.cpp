#include <stdio.h>
#include <stdbool.h>

#define MAX_LEVEL 1000

int main() {
    int n, beginLevel, maxLevel;
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    
    int changes[50];
    for (int i = 0; i < n; i++) {
        scanf("%d", &changes[i]);
    }

    bool dp[51][MAX_LEVEL + 1] = {false};
    dp[0][beginLevel] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= maxLevel; j++) {
            if (dp[i - 1][j]) {
                if (j + changes[i - 1] <= maxLevel) {
                    dp[i][j + changes[i - 1]] = true;
                }
                if (j - changes[i - 1] >= 0) {
                    dp[i][j - changes[i - 1]] = true;
                }
            }
        }
    }

    int maxVolume = -1;
    for (int j = maxLevel; j >= 0; j--) {
        if (dp[n][j]) {
            maxVolume = j;
            break;
        }
    }

    printf("%d\n", maxVolume);

    return 0;
}