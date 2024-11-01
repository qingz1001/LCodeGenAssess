#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000
#define MAX_M 1000

typedef struct {
    int k;
    int c1;
    int c2;
    int crops[MAX_N];
} Combination;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    int a[MAX_N], b[MAX_N];
    Combination combinations[MAX_M];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &combinations[i].k);
        scanf("%d", &combinations[i].c1);
        scanf("%d", &combinations[i].c2);
        for (int j = 0; j < combinations[i].k; j++) {
            scanf("%d", &combinations[i].crops[j]);
        }
    }

    int dp[MAX_N + 1][2];
    dp[0][0] = 0;
    dp[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + a[i - 1];
        dp[i][1] = dp[i - 1][1] + b[i - 1];
    }

    for (int i = 0; i < m; i++) {
        int sumA = 0, sumB = 0;
        for (int j = 0; j < combinations[i].k; j++) {
            int crop = combinations[i].crops[j] - 1;
            sumA += a[crop];
            sumB += b[crop];
        }

        for (int j = 0; j <= n; j++) {
            int newA = dp[j][0] - sumA + combinations[i].c1;
            int newB = dp[j][1] - sumB + combinations[i].c2;
            dp[j][0] = max(dp[j][0], newA);
            dp[j][1] = max(dp[j][1], newB);
        }
    }

    int max_profit = 0;
    for (int i = 0; i <= n; i++) {
        max_profit = max(max_profit, dp[i][0]);
        max_profit = max(max_profit, dp[i][1]);
    }

    printf("%d\n", max_profit);

    return 0;
}