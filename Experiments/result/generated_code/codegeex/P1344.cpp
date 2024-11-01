#include <stdio.h>
#include <string.h>

#define MAXN 33
#define MAXM 1003
#define INF 0x3f3f3f3f

int n, m;
int u[MAXM], v[MAXM], w[MAXM];
int map[MAXN][MAXN], pre[MAXN][MAXN], f[MAXN][1 << MAXN];

int main() {
    int i, j, k, s, t, ans1, ans2, maxn;
    scanf("%d%d", &n, &m);
    
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        map[u[i]][v[i]] = w[i];
    }

    for (s = 1; s <= n; s++) {
        for (t = 1; t <= n; t++) {
            if (s == t) {
                pre[s][t] = 0;
            } else if (map[s][t]) {
                pre[s][t] = map[s][t];
            } else {
                pre[s][t] = INF;
            }
        }
    }

    for (k = 1; k <= n; k++) {
        for (s = 1; s <= n; s++) {
            if (s == k) continue;
            for (t = 1; t <= n; t++) {
                if (t == k || s == t) continue;
                if (pre[s][k] + pre[k][t] < pre[s][t]) {
                    pre[s][t] = pre[s][k] + pre[k][t];
                }
            }
        }
    }

    maxn = 1 << n;
    for (s = 1; s <= n; s++) {
        for (t = 1; t <= n; t++) {
            f[s][1 << (t - 1)] = pre[s][t];
        }
    }

    for (i = 3; i < maxn; i++) {
        if (!(i & 1)) continue;
        for (j = 1; j <= n; j++) {
            if (!((1 << (j - 1)) & i)) continue;
            f[j][i] = f[j][i ^ (1 << (j - 1))];
            for (k = 1; k <= n; k++) {
                if (k == j || (i & (1 << (k - 1))) == 0) continue;
                if (f[j][i] > f[k][i ^ (1 << (j - 1))] + w[j][k]) {
                    f[j][i] = f[k][i ^ (1 << (j - 1))] + w[j][k];
                }
            }
        }
    }

    ans1 = INF;
    ans2 = INF;
    for (i = 1; i <= n; i++) {
        if (ans1 > f[i][maxn - 1]) {
            ans1 = f[i][maxn - 1];
            ans2 = 1;
        } else if (ans1 == f[i][maxn - 1]) {
            ans2++;
        }
    }

    printf("%d %d\n", ans1, ans2);
    return 0;
}