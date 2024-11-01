#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000
#define MAX_M 1000

int n, m;
int a[MAX_N], b[MAX_N];
int c1[MAX_M], c2[MAX_M];
int k[MAX_M];
int crops[MAX_M][MAX_N];

int max(int x, int y) {
    return x > y ? x : y;
}

int dp[MAX_N + 1][MAX_N + 1];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &k[i]);
        scanf("%d %d", &c1[i], &c2[i]);
        for (int j = 0; j < k[i]; j++) {
            scanf("%d", &crops[i][j]);
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INT_MIN;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            int x = j;
            int y = i - j;
            if (dp[x][y] == INT_MIN) continue;

            // Plant in A
            dp[x + 1][y] = max(dp[x + 1][y], dp[x][y] + a[i]);

            // Plant in B
            dp[x][y + 1] = max(dp[x][y + 1], dp[x][y] + b[i]);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int l = 0; l <= n; l++) {
                if (dp[j][l] == INT_MIN) continue;

                int countA = 0, countB = 0;
                for (int p = 0; p < k[i]; p++) {
                    if (crops[i][p] <= j) countA++;
                    if (crops[i][p] <= l) countB++;
                }

                if (countA == k[i]) {
                    dp[j][l] += c1[i];
                }
                if (countB == k[i]) {
                    dp[j][l] += c2[i];
                }
            }
        }
    }

    int result = INT_MIN;
    for (int i = 0; i <= n; i++) {
        result = max(result, dp[i][n - i]);
    }

    printf("%d\n", result);
    return 0;
}