#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001
#define MAXM 4000001
#define MOD 100003

int n, m;
int dis[MAXN], cnt[MAXN];
int head[MAXN], next[MAXM], to[MAXM];

void addEdge(int x, int y) {
    static int tot = 0;
    next[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}

void bfs() {
    static int q[MAXN], front = 0, rear = 0;
    q[rear++] = 1;
    dis[1] = 0;
    cnt[1] = 1;
    while (front < rear) {
        int x = q[front++];
        for (int i = head[x]; i; i = next[i]) {
            int y = to[i];
            if (dis[y] > dis[x] + 1) {
                dis[y] = dis[x] + 1;
                cnt[y] = cnt[x];
                q[rear++] = y;
            } else if (dis[y] == dis[x] + 1) {
                cnt[y] = (cnt[y] + cnt[x]) % MOD;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    memset(dis, 0x3f, sizeof(dis));
    bfs();
    for (int i = 1; i <= n; i++) {
        printf("%d\n", cnt[i]);
    }
    return 0;
}