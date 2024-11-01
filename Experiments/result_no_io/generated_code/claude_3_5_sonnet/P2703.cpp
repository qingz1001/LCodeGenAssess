#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define INF 0x3f3f3f3f

int n, L[MAXN], R[MAXN];
int dp[MAXN][3];
int left[MAXN], right[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = dp[0][1] = dp[0][2] = 0;

    for (int i = 1; i <= n; i++) {
        left[i] = max(left[i-1], L[i]);
        right[i] = max(right[i-1], R[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            int l = left[i], r = right[i];
            if (j == 1) l = L[i];
            if (j == 2) r = R[i];

            for (int k = 0; k < 3; k++) {
                int prev_l = left[i-1], prev_r = right[i-1];
                if (k == 1) prev_l = L[i-1];
                if (k == 2) prev_r = R[i-1];

                if (l >= prev_l && r >= prev_r) {
                    dp[i][j] = min(dp[i][j], dp[i-1][k] + (r - l + 1) - (R[i] - L[i] + 1));
                }
            }
        }
    }

    int result = min(dp[n][0], min(dp[n][1], dp[n][2]));
    printf("%d\n", result);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }
    solve();
    return 0;
}