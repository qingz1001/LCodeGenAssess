#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_MASK 1024
#define INF 0x3f3f3f3f

int n;
int t[MAX_N], a[MAX_N], b[MAX_N];
int dp[MAX_MASK][MAX_N][2];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = dp[0][0][1] = 0;

    int type3_count = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == 3) type3_count++;
    }

    for (int mask = 0; mask < (1 << type3_count); mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                if (dp[mask][i][j] == INF) continue;

                int next_i = i + 1;
                if (next_i == n) continue;

                if (t[next_i] == 1 || (t[next_i] == 3 && !(mask & (1 << (next_i - (n - type3_count)))))) {
                    dp[mask][next_i][0] = min(dp[mask][next_i][0], max(dp[mask][i][j] + a[next_i], b[i] + a[next_i] + b[next_i]));
                }

                if (t[next_i] == 2 || (t[next_i] == 3 && (mask & (1 << (next_i - (n - type3_count)))))) {
                    dp[mask][next_i][1] = min(dp[mask][next_i][1], max(dp[mask][i][j] + b[next_i], a[i] + a[next_i] + b[next_i]));
                }

                if (t[next_i] == 3) {
                    int new_mask = mask | (1 << (next_i - (n - type3_count)));
                    dp[new_mask][next_i][1] = min(dp[new_mask][next_i][1], max(dp[mask][i][j] + b[next_i], a[i] + a[next_i] + b[next_i]));
                }
            }
        }
    }

    int result = INF;
    for (int mask = 0; mask < (1 << type3_count); mask++) {
        result = min(result, min(dp[mask][n-1][0], dp[mask][n-1][1]));
    }

    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &t[i], &a[i], &b[i]);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}