#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 105
#define M 1005
#define INF 0x3f3f3f3f
using namespace std;

int n, m, e, t, a[N][M], b[M], c[M], d[M], f[M], ans;

struct edge {
    int v, next;
} edge[M];

void add(int u, int v) {
    edge[++e].v = v;
    edge[e].next = b[u];
    b[u] = e;
}

void dp(int s, int now, int sum) {
    if (now == (1 << m)) {
        if (sum < f[s]) return;
        f[s] = sum;
        for (int i = 1; i <= t; i++) {
            int flag = 1;
            for (int j = 1; j <= m; j++) {
                if (d[i] & (1 << (j - 1))) {
                    if (!c[i][j]) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) ans += b[i];
        }
        return;
    }
    dp(s, now | (1 << (now & 31)), sum + a[s][now & 31]);
    dp(s, now, sum);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        int v, c;
        scanf("%d%d", &v, &c);
        for (int j = 1; j <= c; j++) {
            int x;
            scanf("%d", &x);
            d[i] |= (1 << (x - 1));
            c[i][x] = 1;
        }
        b[i] = v;
    }
    memset(f, -INF, sizeof(f));
    dp(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}