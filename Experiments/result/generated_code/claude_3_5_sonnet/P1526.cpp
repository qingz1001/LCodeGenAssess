#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 101
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

Point weapons[MAX_N], bombs[MAX_N];
int M, n, k;
int dist[MAX_N][MAX_N];
int dp[1 << 20];
int pre[1 << 20];

int min(int a, int b) {
    return a < b ? a : b;
}

int square(int x) {
    return x * x;
}

int calcDist(Point a, Point b) {
    return square(a.x - b.x) + square(a.y - b.y);
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &M, &n, &k);
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (calcDist(bombs[i], bombs[j]) <= k * k) {
                dist[i][j] = 1;
            }
        }
        dist[i][i] = 0;
    }

    floyd();

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int s = 0; s < (1 << M); s++) {
        int p = __builtin_popcount(s);
        for (int i = 1; i <= n; i++) {
            int ns = s;
            for (int j = 1; j <= M; j++) {
                if (!(s & (1 << (j - 1))) && calcDist(bombs[i], weapons[j]) <= k * k) {
                    ns |= (1 << (j - 1));
                }
            }
            if (ns != s && dp[ns] > dp[s] + 1) {
                dp[ns] = dp[s] + 1;
                pre[ns] = i;
            }
        }
    }

    printf("%d\n", dp[(1 << M) - 1]);

    return 0;
}