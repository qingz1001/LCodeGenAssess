#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 10005
#define INF 0x3f3f3f3f

int n, m, k;
int D[MAXN], T[MAXM], A[MAXM], B[MAXM];
int dp[MAXN][MAXN];
int passengers[MAXN][MAXN];
int arrive[MAXN], leave[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    memset(passengers, 0, sizeof(passengers));
    
    for (int i = 1; i <= m; i++) {
        passengers[A[i]][B[i]]++;
    }
    
    dp[1][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= k && j <= D[i]; j++) {
            int time = D[i] - j;
            for (int l = 0; l <= k - j; l++) {
                dp[i + 1][j + l] = min(dp[i + 1][j + l], dp[i][l] + time);
            }
        }
    }
    
    int ans = INF;
    for (int i = 0; i <= k; i++) {
        ans = min(ans, dp[n][i]);
    }
    
    arrive[1] = 0;
    for (int i = 1; i < n; i++) {
        leave[i] = max(arrive[i], T[i]);
        for (int j = i + 1; j <= n; j++) {
            if (passengers[i][j] > 0) {
                leave[i] = max(leave[i], T[i]);
            }
        }
        arrive[i + 1] = leave[i] + D[i] - (ans - dp[i][0]);
    }
    
    long long total_time = 0;
    for (int i = 1; i <= m; i++) {
        total_time += arrive[B[i]] - T[i];
    }
    
    printf("%lld\n", total_time);
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