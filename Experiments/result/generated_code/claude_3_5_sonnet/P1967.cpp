#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 50001
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], cnt;
int n, m, q;
int fa[MAX_N], rank[MAX_N];
int maxw[MAX_N][MAX_N];

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        rank[i] = 1;
    }
    memset(maxw, 0, sizeof(maxw));
}

void addEdge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int find(int x) {
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        fa[x] = y;
    } else {
        fa[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

void kruskal() {
    for (int i = 0; i < cnt; i++) {
        int u = edges[i].to;
        int v = edges[i ^ 1].to;
        int w = edges[i].weight;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            unite(fu, fv);
            for (int j = 1; j <= n; j++) {
                if (find(j) == fu) {
                    for (int k = 1; k <= n; k++) {
                        if (find(k) == fv) {
                            maxw[j][k] = maxw[k][j] = w;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    init();
    
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        addEdge(x, y, z);
        addEdge(y, x, z);
    }
    
    kruskal();
    
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (find(x) != find(y)) {
            printf("-1\n");
        } else {
            printf("%d\n", maxw[x][y]);
        }
    }
    
    return 0;
}