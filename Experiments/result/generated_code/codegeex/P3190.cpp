#include <stdio.h>
#include <string.h>

int n, m, ans = -1e9;
int a[105][7], dp[105][1 << 6];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);

    for (int s = 0; s < (1 << m); s++) {
        int sum = 0, cnt = 0;
        for (int i = 0; i < m; i++) {
            if (s & (1 << i)) {
                sum += a[1][i + 1];
                cnt++;
            }
        }
        if (cnt & 1) sum = -1e9;
        dp[1][s] = sum;
    }

    for (int i = 2; i <= n; i++) {
        for (int s = 0; s < (1 << m); s++) {
            int sum = 0, cnt = 0;
            for (int j = 0; j < m; j++) {
                if (s & (1 << j)) {
                    sum += a[i][j + 1];
                    cnt++;
                }
            }
            if (cnt & 1) sum = -1e9;
            for (int k = 0; k < m; k++) {
                if (s & (1 << k)) {
                    dp[i][s] = dp[i - 1][s ^ (1 << k)] + sum;
                }
            }
        }
    }

    for (int s = 0; s < (1 << m); s++) {
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            if (s & (1 << i)) cnt++;
        }
        if (cnt >= 4 && cnt & 1) ans = ans > dp[n][s] ? ans : dp[n][s];
    }

    printf("%d", ans);
    return 0;
}