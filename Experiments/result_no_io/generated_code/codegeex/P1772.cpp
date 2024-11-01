#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 20
#define MAX_E 200
#define MAX_K 500
#define INF 0x3f3f3f3f

int n, m, k, e, d;
int dis[MAX_M + 1][MAX_M + 1];
int a[MAX_N + 1], b[MAX_N + 1], p[MAX_N + 1];
int dp[MAX_N + 1][1 << MAX_M];

void floyd() {
    for (int k = 1; k <= m; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &e);
    memset(dis, INF, sizeof(dis));
    for (int i = 1; i <= e; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        dis[x][y] = dis[y][x] = z;
    }
    scanf("%d", &d);
    for (int i = 1; i <= d; i++) {
        scanf("%d%d%d", &p[i], &a[i], &b[i]);
    }

    floyd();

    memset(dp, INF, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            for (int l = 1; l <= m; l++) {
                if (j & (1 << (l - 1))) continue;
                int flag = 1;
                for (int x = 1; x <= d; x++) {
                    if (p[x] == l && i >= a[x] && i <= b[x]) {
                        flag = 0;
                        break;
                    }
                }
                if (!flag) continue;
                dp[i][j | (1 << (l - 1))] = 
                    (dis[1][l] + dis[l][m] < INF ? dis[1][l] + dis[l][m] : INF) *
                    (i == n ? 0 : i) + 
                    k * (i == 1 ? 0 : 1) + 
                    (dp[i - 1][j] < INF ? dp[i - 1][j] : INF);
            }
        }
    }

    int ans = INF;
    for (int j = 0; j < (1 << m); j++) {
        ans = (dp[n][j] < INF ? dp[n][j] : INF);
    }

    printf("%d\n", ans);
    return 0;
}