#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 5001
#define INF 0x3f3f3f3f

int n, m;
int f[MAXN], in[MAXN], head[MAXN], nxt[MAXM], to[MAXM], w[MAXM], tot;
double dp[MAXN][MAXN];

void add(int x, int y, int z) {
    to[++tot] = y;
    w[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        in[y]++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -INF;
        }
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = head[j]; k; k = nxt[k]) {
                int v = to[k], c = w[k];
                if (i == v) continue;
                dp[i][j] = fmax(dp[i][j], dp[i][j - in[v]] + (double)f[v] / c);
            }
        }
    }

    double ans = -INF;
    for (int i = 1; i <= n; i++) {
        ans = fmax(ans, dp[i][i]);
    }

    if (ans < 0) {
        printf("0.00\n");
    } else {
        printf("%.2lf\n", ans);
    }

    return 0;
}