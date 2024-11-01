#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 20
#define MAXMC 100

int n, m, mc;
int a[MAXN], w[MAXN];
int C[MAXM];

typedef struct {
    int days;
    int confidence;
} State;

bool canDefeat(int C) {
    int dp[MAXN + 1][MAXMC + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= mc; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][mc] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= mc; j++) {
            if (dp[i][j] != -1) {
                int newConfidence = j - a[i];
                if (newConfidence < 0) continue;
                if (newConfidence > mc) newConfidence = mc;

                // Option 1: Do nothing
                if (dp[i + 1][newConfidence] < dp[i][j]) {
                    dp[i + 1][newConfidence] = dp[i][j];
                }

                // Option 2: Increase confidence
                int newConfidence2 = newConfidence + w[i];
                if (newConfidence2 > mc) newConfidence2 = mc;
                if (dp[i + 1][newConfidence2] < dp[i][j]) {
                    dp[i + 1][newConfidence2] = dp[i][j];
                }

                // Option 3: Increase level
                if (dp[i + 1][newConfidence] < dp[i][j] + 1) {
                    dp[i + 1][newConfidence] = dp[i][j] + 1;
                }

                // Option 4: Increase讽刺能力
                if (dp[i + 1][newConfidence] < dp[i][j] * (dp[i][j] + 1) / 2) {
                    dp[i + 1][newConfidence] = dp[i][j] * (dp[i][j] + 1) / 2;
                }

                // Option 5: 怼大佬
                if (dp[i][j] > 0 && dp[i + 1][newConfidence] < dp[i][j] - 1) {
                    dp[i + 1][newConfidence] = dp[i][j] - 1;
                }
            }
        }
    }

    for (int j = 0; j <= mc; j++) {
        if (dp[n][j] >= C) return true;
    }
    return false;
}

int main() {
    scanf("%d %d %d", &n, &m, &mc);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &C[i]);
    }

    for (int i = 0; i < m; i++) {
        if (canDefeat(C[i])) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}