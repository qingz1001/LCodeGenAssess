#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 200005

int n, m;
int A[MAXN], B[MAXN];
int dp[MAXN][2];
int pre[MAXN][2];
int ans[MAXM];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = dp[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            int happy = B[i] ? 1 : -1;
            if (dp[i-1][0] + happy < dp[i][j]) {
                dp[i][j] = dp[i-1][0] + happy;
                pre[i][j] = 0;
            }
            if (j == 1 && dp[i-1][1] < dp[i][j]) {
                dp[i][j] = dp[i-1][1];
                pre[i][j] = 1;
            }
        }
    }

    int cur = 1, pos = n;
    for (int i = m; i >= 1; i--) {
        ans[i] = A[pos];
        cur = pre[pos][cur];
        while (pos > 1 && cur == 1) {
            pos--;
            cur = pre[pos][cur];
        }
        pos--;
    }

    for (int i = 1; i <= m; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}