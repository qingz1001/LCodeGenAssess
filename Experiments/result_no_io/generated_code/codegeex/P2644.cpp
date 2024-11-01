#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 31
#define INF 0x3f3f3f3f

int m, n, p;
int a[MAXN][MAXN];
int sx, sy, ex, ey;
int d[MAXN][MAXN], g[MAXN][MAXN], w[MAXN][MAXN];
long long dp[MAXN * MAXN][2];

void bfs() {
    memset(d, INF, sizeof(d));
    memset(g, INF, sizeof(g));
    memset(w, INF, sizeof(w));
    d[sx][sy] = 0;
    g[sx][sy] = 0;
    w[sx][sy] = 1;
    int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
    struct Node {
        int x, y;
    } q[MAXN * MAXN];
    int front = 0, rear = 0;
    q[rear++] = (struct Node){sx, sy};
    while (front < rear) {
        struct Node u = q[front++];
        for (int i = 0; i < 8; i++) {
            int nx = u.x + dx[i], ny = u.y + dy[i];
            if (nx >= 1 && nx <= m && ny >= 1 && ny <= n && a[nx][ny] != 2) {
                int cost = (a[nx][ny] == 5) ? 2 : 1;
                if (d[nx][ny] > d[u.x][u.y] + cost) {
                    d[nx][ny] = d[u.x][u.y] + cost;
                    g[nx][ny] = g[u.x][u.y] + (a[nx][ny] == 5);
                    w[nx][ny] = 1;
                    q[rear++] = (struct Node){nx, ny};
                } else if (d[nx][ny] == d[u.x][u.y] + cost) {
                    g[nx][ny] = (g[nx][ny] < g[u.x][u.y] + (a[nx][ny] == 5)) ? g[nx][ny] : g[u.x][u.y] + (a[nx][ny] == 5);
                    if (g[nx][ny] == g[u.x][u.y] + (a[nx][ny] == 5)) {
                        w[nx][ny] = (long long)w[nx][ny] * w[u.x][u.y] % 1000000007;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &p, &m, &n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 3) {
                sx = i;
                sy = j;
            } else if (a[i][j] == 4) {
                ex = i;
                ey = j;
            }
        }
    }
    bfs();
    if (d[ex][ey] > p) {
        printf("-1\n");
        return 0;
    }
    int s = d[ex][ey];
    long long ws = w[ex][ey];
    int g = 0, wg = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == s && g[i][j] > g) {
                g = g[i][j];
                wg = w[i][j];
            } else if (d[i][j] == s && g[i][j] == g) {
                wg = (long long)wg * w[i][j] % 1000000007;
            }
        }
    }
    if (g == 0) {
        printf("%d %lld\n-1\n", s, ws);
    } else {
        printf("%d %lld\n%d %lld\n", s, ws, g, wg);
    }
    return 0;
}