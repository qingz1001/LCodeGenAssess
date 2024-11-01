#include <stdio.h>
#include <string.h>

#define MOD 11192869

int n, m;
int t[4][51], l[51];
int dp[2][2][2][2][51][2];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &t[i][j]);
    for (int i = 0; i < n * m; i++)
        scanf("%d", &l[i]);

    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0][0][0] = 1;

    for (int i = 0; i < n * m; i++) {
        int cur = i & 1, pre = cur ^ 1;
        memset(dp[cur], 0, sizeof(dp[cur]));
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= m; y++)
                if (t[x][y] == l[i]) {
                    for (int px = 1; px <= n; px++)
                        for (int py = 1; py <= m; py++)
                            if (x != px || y != py) {
                                for (int z = 0; z < 2; z++)
                                    for (int w = 0; w < 2; w++)
                                        for (int q = 0; q < 2; q++)
                                            for (int r = 0; r < 2; r++)
                                                if ((x == 1 || x == n) + (y == 1 || y == m) == q + r) {
                                                    dp[cur][z][w][q][i + 1][z | (x == 1 || x == n)] =
                                                        (dp[cur][z][w][q][i + 1][z | (x == 1 || x == n)] +
                                                         (long long)dp[pre][z][w][q][i][w | (x == 1 || x == n)] *
                                                             (x == px + 1 || x == px - 1 ? (y == py ? 1 : 0) :
                                                              (x == px ? (y == py + 1 || y == py - 1 ? 1 : 0) : 0)) %
                                                             MOD) %
                                                        MOD;
                                                }
                            }
                }
    }

    int ans = 0;
    for (int z = 0; z < 2; z++)
        for (int w = 0; w < 2; w++)
            for (int q = 0; q < 2; q++)
                for (int r = 0; r < 2; r++)
                    if ((n == 1 || m == 1) + (n == 1 || m == 1) == q + r)
                        ans = (ans + dp[n * m & 1][z][w][q][n * m][z | (n == 1 || m == 1)]) % MOD;

    printf("%d\n", ans);
    return 0;
}