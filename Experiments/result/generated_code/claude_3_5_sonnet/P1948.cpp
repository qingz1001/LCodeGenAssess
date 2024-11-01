#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_P 10001
#define INF 1000000001

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX_P];
int parent[MAX_N], size[MAX_N];
int n, p, k;

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) {
        parent[x] = y;
        size[y] += size[x];
    } else {
        parent[y] = x;
        size[x] += size[y];
    }
}

int kruskal(int limit) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
    for (int i = 0; i < p && edges[i].w <= limit; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            cnt++;
        }
    }
    return cnt >= n - 1 - k;
}

int main() {
    scanf("%d %d %d", &n, &p, &k);
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
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