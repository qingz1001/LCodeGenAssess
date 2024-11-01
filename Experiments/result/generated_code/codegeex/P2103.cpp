#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 501
#define INF 0x3f3f3f3f

int g[MAXN][MAXN], dis[MAXN][MAXN], cnt[MAXN][MAXN];
int N, M;

void floyd() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i != j && j != k && i != k) {
                    if (dis[i][j] > dis[i][k] + dis[k][j]) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                        cnt[i][j] = cnt[i][k] * cnt[k][j];
                    } else if (dis[i][j] == dis[i][k] + dis[k][j]) {
                        cnt[i][j] += cnt[i][k] * cnt[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    memset(g, INF, sizeof(g));
    memset(dis, INF, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= N; i++) {
        dis[i][i] = 0;
        cnt[i][i] = 1;
    }

    for (int i = 0; i < M; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        g[x][y] = g[y][x] = z;
        dis[x][y] = dis[y][x] = z;
        cnt[x][y] = cnt[y][x] = 1;
    }

    floyd();

    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            printf("%d ", cnt[i][j]);
        }
    }

    return 0;
}