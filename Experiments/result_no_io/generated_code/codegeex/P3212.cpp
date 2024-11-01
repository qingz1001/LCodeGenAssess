#include <stdio.h>
#include <string.h>

#define MAX_TASKS 20
#define MAX_TIME 10000

int n;
int a[MAX_TASKS + 1], b[MAX_TASKS + 1], type[MAX_TASKS + 1];
int dp[1 << MAX_TASKS][2][MAX_TIME];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &type[i], &a[i], &b[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 1; i <= n; i++) {
            if (mask & (1 << (i - 1))) {
                int prev_mask = mask ^ (1 << (i - 1));
                for (int j = 0; j < MAX_TIME; j++) {
                    if (dp[prev_mask][0][j] != 0x3f3f3f3f) {
                        dp[mask][0][j + a[i]] = (dp[mask][0][j + a[i]] < dp[prev_mask][0][j] + b[i]) ? dp[mask][0][j + a[i]] : dp[prev_mask][0][j] + b[i];
                    }
                    if (dp[prev_mask][1][j] != 0x3f3f3f3f) {
                        dp[mask][0][j + b[i]] = (dp[mask][0][j + b[i]] < dp[prev_mask][1][j] + a[i]) ? dp[mask][0][j + b[i]] : dp[prev_mask][1][j] + a[i];
                    }
                    if (dp[prev_mask][0][j] != 0x3f3f3f3f) {
                        dp[mask][1][j + b[i]] = (dp[mask][1][j + b[i]] < dp[prev_mask][0][j] + a[i]) ? dp[mask][1][j + b[i]] : dp[prev_mask][0][j] + a[i];
                    }
                    if (dp[prev_mask][1][j] != 0x3f3f3f3f) {
                        dp[mask][1][j + a[i]] = (dp[mask][1][j + a[i]] < dp[prev_mask][1][j] + b[i]) ? dp[mask][1][j + a[i]] : dp[prev_mask][1][j] + b[i];
                    }
                }
            }
        }
    }

    int min_time = 0x3f3f3f3f;
    for (int i = 0; i < MAX_TIME; i++) {
        min_time = (min_time < dp[(1 << n) - 1][0][i] && min_time < dp[(1 << n) - 1][1][i]) ? min_time : (dp[(1 << n) - 1][0][i] < dp[(1 << n) - 1][1][i] ? dp[(1 << n) - 1][0][i] : dp[(1 << n) - 1][1][i]);
    }

    printf("%d\n", min_time);
}

int main() {
    solve();
    return 0;
}