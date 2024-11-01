#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define INF 0x3f3f3f3f

int n, a, b;
int h[MAXN];
int dp[MAXN][4];

int min(int a, int b) {
    return a < b ? a : b;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }

    int g = gcd(a, b);
    for (int i = 1; i <= n; i++) {
        if (h[i] % g != 0) {
            printf("-1\n");
            return 0;
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            int prev = h[i] + (j & 1 ? a : 0) + (j & 2 ? b : 0);
            for (int k = 0; k < 4; k++) {
                int curr = (k & 1 ? a : 0) + (k & 2 ? b : 0);
                int diff = abs(prev - curr);
                if (diff % g == 0) {
                    dp[i][k] = min(dp[i][k], dp[i-1][j] + diff / g);
                }
            }
        }
    }

    int ans = INF;
    for (int j = 0; j < 4; j++) {
        ans = min(ans, dp[n][j]);
    }

    printf("%d\n", ans == INF ? -1 : ans);

    return 0;
}