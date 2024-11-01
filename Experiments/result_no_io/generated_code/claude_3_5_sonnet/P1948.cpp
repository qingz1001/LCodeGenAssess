#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 1001
#define MAX_P 10001
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

int n, p, k;
Edge edges[MAX_P];
int parent[MAX_N], rank[MAX_N];
int dist[MAX_N];

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

void init() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

int kruskal(int mid) {
    init();
    int count = 0;
    for (int i = 0; i < p && count < n - 1; i++) {
        if (edges[i].w > mid) break;
        int x = find(edges[i].u);
        int y = find(edges[i].v);
        if (x != y) {
            unite(x, y);
            count++;
        }
    }
    return count >= n - k - 1;
}

int main() {
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 0; i < p; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, p, sizeof(Edge), cmp);

    int left = 0, right = 1000000, ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (kruskal(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}