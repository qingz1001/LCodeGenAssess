#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int u, v;
} Edge;

int n, m;
Edge edges[MAXM];
int parent[MAXN], rank[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void merge(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    if (rank[px] > rank[py]) {
        parent[py] = px;
    } else if (rank[px] < rank[py]) {
        parent[px] = py;
    } else {
        parent[py] = px;
        rank[px]++;
    }
}

int check() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) == find(v)) {
            return 0;
        }
        merge(u, v + 5);
        merge(v, u + 5);
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int k, t, u, v;
        scanf("%d %d", &k, &t);
        if (k == 0) {
            scanf("%d %d", &u, &v);
        } else {
            scanf("%d %d", &u, &v);
            u += (i - k) * 5;
            v += (i - k) * 5;
        }
        edges[i].u = u;
        edges[i].v = v;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            edges[j].u += (j - i) * 5;
            edges[j].v += (j - i) * 5;
        }
        if (check()) {
            printf("excited\n");
        } else {
            printf("naive\n");
        }
    }
    return 0;
}