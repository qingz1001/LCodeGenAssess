#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1005
#define MAX_M 10005
#define INF 0x3f3f3f3f

int n, m, k;
int D[MAX_N];
int T[MAX_M], A[MAX_M], B[MAX_M];
int dp[MAX_N][MAX_N];
int sum[MAX_N];
int need[MAX_N];
int wait[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    memset(need, 0, sizeof(need));
    memset(wait, 0, sizeof(wait));

    for (int i = 1; i <= m; i++) {
        need[A[i]]++;
        wait[A[i]] = max(wait[A[i]], T[i]);
    }

    sum[0] = 0;
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i-1] + D[i];
    }

    dp[1][0] = wait[1];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i][j] == INF) continue;
            int cost = sum[i] - sum[i-1];
            for (int l = 0; l <= min(j, cost); l++) {
                int nxt = max(dp[i][j] + cost - l, wait[i+1]);
                dp[i+1][j-l] = min(dp[i+1][j-l], nxt);
            }
        }
    }

    long long ans = 0;
    int arrive = dp[n][k];
    for (int i = 1; i <= m; i++) {
        ans += arrive - T[i];
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i < n; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &T[i], &A[i], &B[i]);
    }
    solve();
    return 0;
}