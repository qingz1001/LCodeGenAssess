#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 51
#define MAXM 1001
#define MAXQ 100001

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAXM];
double dp[MAXN][MAXN];
int n, m, q;

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][k] != -1 && dp[k][j] != -1) {
                    double new_dist = (dp[i][k] + dp[k][j]) / 2.0;
                    if (dp[i][j] == -1 || new_dist < dp[i][j]) {
                        dp[i][j] = new_dist;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    scanf("%d", &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        dp[u][v] = w;
    }

    floyd();

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (dp[x][y] == -1) {
            printf("OMG!\n");
        } else {
            printf("%.3lf\n", dp[x][y]);
        }
    }

    return 0;
}