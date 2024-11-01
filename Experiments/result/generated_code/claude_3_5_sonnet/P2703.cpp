#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000005
#define INF 0x3f3f3f3f

int n;
int L[MAXN], R[MAXN];
int dp[MAXN][3];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = R[1] - L[1];
    dp[1][1] = R[1] - L[1] + 1;
    dp[1][2] = R[1] - L[1] + 2;

    for (int i = 2; i <= n; i++) {
        int width = R[i] - L[i] + 1;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                int cost = dp[i-1][k];
                int l = max(L[i-1] + k, L[i]);
                int r = min(R[i-1] + k, R[i] + j);
                if (l <= r) {
                    cost += width - (r - l + 1);
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
    }

    int ans = INF;
    for (int j = 0; j < 3; j++) {
        ans = min(ans, dp[n][j]);
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }
    solve();
    return 0;
}