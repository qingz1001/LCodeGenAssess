#include <stdio.h>
#include <string.h>

#define MAXN 205

int n, m, a[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN], cnt, ans;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void dfs(int x, int y) {
    f[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] != 2 && !f[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != 2 && !f[i][j]) {
                cnt++;
                dfs(i, j);
                for (int k = 1; k <= m; k++) {
                    if (a[i][k] != 2 && !f[i][k]) {
                        g[cnt][++ans] = k;
                    }
                }
            }
        }
    }

    int flow = 0;
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= ans; j++) {
            if (!g[i][j]) {
                g[i][j] = 1;
                break;
            }
        }
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= ans; j++) {
            if (!g[i][j]) {
                g[i][j] = 0;
                continue;
            }
            for (int k = i + 1; k <= cnt; k++) {
                if (!g[k][j]) {
                    g[i][j] = 0;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= ans; j++) {
            if (g[i][j]) {
                flow++;
            }
        }
    }

    printf("%d\n", flow);
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= ans; j++) {
            if (g[i][j]) {
                printf("%d %d\n", i, j);
            }
        }
    }

    return 0;
}