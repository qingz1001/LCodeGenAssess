#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 205
#define MAXM 4005

int n, m, x;
int head[MAXN], next[MAXM], ver[MAXM], edge[MAXM];
int d[MAXN], q[MAXN], l, r;

void add(int u, int v, int w) {
    static int tot = 0;
    ver[++tot] = v;
    edge[tot] = w;
    next[tot] = head[u];
    head[u] = tot;
}

void bfs() {
    memset(d, -1, sizeof(d));
    l = r = 0;
    d[1] = 0;
    q[++r] = 1;
    while (l < r) {
        int u = q[++l];
        for (int i = head[u]; i; i = next[i]) {
            int v = ver[i];
            if (d[v] == -1 && edge[i]) {
                d[v] = d[u] + 1;
                q[++r] = v;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &x);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    bfs();
    if (d[n] == -1) {
        printf("Orz Ni Jinan Saint Cow!\n");
    } else {
        int maxflow = 0, batch = 0;
        while (x > 0) {
            int flow = 0;
            for (int i = head[1]; i; i = next[i]) {
                if (d[ver[i]] == d[1] + 1 && edge[i] > 0) {
                    int minflow = x > edge[i] ? edge[i] : x;
                    x -= minflow;
                    edge[i] -= minflow;
                    flow += minflow;
                }
            }
            if (flow == 0) {
                break;
            }
            maxflow = flow;
            batch++;
            bfs();
        }
        printf("%d %d\n", maxflow, batch);
    }
    return 0;
}