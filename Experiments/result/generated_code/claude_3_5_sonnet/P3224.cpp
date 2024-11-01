#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005

int n, m, q;
int p[MAXN], rank[MAXN];
int parent[MAXN], size[MAXN];
int tree[MAXN][20], depth[MAXN];

struct Edge {
    int u, v;
} edges[MAXM];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    parent[y] = x;
    size[x] += size[y];
    for (int i = 0; i < 20; i++) {
        if (tree[y][i] == -1) break;
        int idx = depth[tree[y][i]];
        while (tree[x][idx] != -1 && rank[tree[x][idx]] < rank[tree[y][i]]) idx++;
        for (int j = 19; j > idx; j--) tree[x][j] = tree[x][j-1];
        tree[x][idx] = tree[y][i];
    }
}

int query(int x, int k) {
    x = find(x);
    if (k > size[x]) return -1;
    int idx = 0;
    while (k > 0) {
        if (k & 1) x = tree[x][idx];
        k >>= 1;
        idx++;
    }
    return x;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        rank[p[i]] = i;
        parent[i] = i;
        size[i] = 1;
        tree[i][0] = i;
        depth[i] = 0;
        for (int j = 1; j < 20; j++) tree[i][j] = -1;
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &edges[i].u, &edges[i].v);
        unite(edges[i].u, edges[i].v);
    }
    
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char op;
        int x, y;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'Q') {
            printf("%d\n", query(x, y));
        } else {
            unite(x, y);
        }
    }
    
    return 0;
}