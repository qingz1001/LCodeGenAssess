#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_K 100
#define MAX_W 100

bool isWinning(int n, int w, int whiteIndices[]) {
    bool dp[n + 1];
    memset(dp, false, sizeof(dp));

    for (int i = n; i >= 1; i--) {
        if (!dp[i]) {
            for (int j = 1; j * i <= n; j++) {
                dp[j * i] = true;
            }
        }
    }

    for (int i = 0; i < w; i++) {
        if (!dp[whiteIndices[i]]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    int whiteIndices[MAX_W];
    for (int i = 0; i < k; i++) {
        int w;
        scanf("%d", &w);
        for (int j = 0; j < w; j++) {
            scanf("%d", &whiteIndices[j]);
        }
        if (isWinning(n, w, whiteIndices)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}