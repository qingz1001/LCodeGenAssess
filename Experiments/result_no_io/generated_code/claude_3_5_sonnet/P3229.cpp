#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 500005
#define MAX_M 200005

int n, m;
int A[MAX_N], B[MAX_N];
int dp[MAX_N][2];
int path[MAX_N][2];
int result[MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = dp[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            int happy = 0, tired = 0;
            for (int k = i; k > 0 && (i - k + 1) <= n / m; k--) {
                if (B[k]) happy++;
                else tired++;
                int diff = abs(happy - tired);
                
                if (dp[k-1][j^1] + max(diff, dp[k-1][j^1]) < dp[i][j]) {
                    dp[i][j] = dp[k-1][j^1] + max(diff, dp[k-1][j^1]);
                    path[i][j] = k-1;
                }
            }
        }
    }

    int cur = n, flag = dp[n][0] < dp[n][1] ? 0 : 1;
    for (int i = m; i > 0; i--) {
        result[i] = A[cur];
        cur = path[cur][flag];
        flag ^= 1;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    solve();

    for (int i = 1; i <= m; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}