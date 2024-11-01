#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 10005
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAXM];
int n, m, k;
int fa[MAXN];

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i <= n; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    qsort(edges, m, sizeof(Edge), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    int ans = 0, cnt = 0;
    for (int i = 0; i < m && cnt < k - 1; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) != find(v)) {
            merge(u, v);
            ans += w;
            ++cnt;
        }
    }
    if (cnt == k - 1) printf("%d\n", ans);
    else printf("No Answer\n");
    return 0;
}