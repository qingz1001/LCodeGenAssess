#include <stdio.h>
#include <string.h>

#define MAXN 110
#define MAXM 7

int n, m, a[MAXN][MAXM], dp[2][MAXN][1 << 8];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int now = 0, pre = 1;
    memset(dp[now], 0, sizeof(dp[now]));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < (1 << m); k++) {
                dp[pre][i * m + j][k] = -1e9;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < (1 << m); k++) {
                for (int l = 0; l < 4; l++) {
                    int nx = i + dx[l], ny = j + dy[l];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    int nk = k | (1 << ny);
                    if (nk == k) continue;
                    dp[pre][i * m + j][nk] = dp[now][i * m + j][k] + a[nx][ny];
                }
            }
            for (int k = 0; k < (1 << m); k++) {
                dp[now][i * m + j][k] = dp[pre][i * m + j][k];
            }
        }
        now ^= 1;
        pre ^= 1;
    }

    int ans = -1e9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = ans > dp[now][i * m + j][(1 << m) - 1] ? ans : dp[now][i * m + j][(1 << m) - 1];
        }
    }

    printf("%d\n", ans);
    return 0;
}