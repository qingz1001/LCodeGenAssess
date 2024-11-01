#include <stdio.h>
#include <string.h>

#define N 1000005
#define M 2000005
#define MOD 100003

int n, m;
int head[N], to[M], next[M], tot;
int dis[N], f[N];
int q[N], l, r;

void add(int x, int y) {
    to[tot] = y;
    next[tot] = head[x];
    head[x] = tot++;
}

void bfs() {
    l = r = 0;
    q[r++] = 1;
    dis[1] = 0;
    f[1] = 1;

    while (l < r) {
        int x = q[l++];
        for (int i = head[x]; i != -1; i = next[i]) {
            int y = to[i];
            if (dis[y] == -1) {
                dis[y] = dis[x] + 1;
                q[r++] = y;
            }
            if (dis[y] == dis[x] + 1) {
                f[y] = (f[y] + f[x]) % MOD;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    memset(dis, -1, sizeof(dis));
    tot = 0;

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }

    bfs();

    for (int i = 1; i <= n; i++) {
        printf("%d\n", f[i]);
    }

    return 0;
}