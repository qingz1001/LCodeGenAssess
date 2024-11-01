#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 201
#define MAX_P 40001
#define INF 1000000001

typedef struct {
    int u, v, w;
} Edge;

int N, P, T;
Edge edges[MAX_P];
int parent[MAX_N];
int size[MAX_N];

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
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

int kruskal(int k) {
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        size[i] = 1;
    }
    
    int count = 0;
    for (int i = 0; i < P && count < N - 1; i++) {
        if (edges[i].w > k) break;
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            count++;
        }
    }
    
    return find(1) == find(N) && count >= N - T;
}

int main() {
    scanf("%d %d %d", &N, &P, &T);
    
    for (int i = 0; i < P; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    
    qsort(edges, P, sizeof(Edge), cmp);
    
    int left = 0, right = INF, mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (kruskal(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", left);
    
    return 0;
}