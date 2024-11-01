#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005

int n, m, q;
int p[MAXN], rank[MAXN];
int parent[MAXN], size[MAXN];
int tree[MAXN][20];

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
        int j = 0;
        while (tree[x][j] != -1 && rank[tree[x][j]] < rank[tree[y][i]]) j++;
        if (j < 20) {
            for (int k = 19; k > j; k--) tree[x][k] = tree[x][k-1];
            tree[x][j] = tree[y][i];
        }
    }
}

int query(int x, int k) {
    x = find(x);
    if (k > size[x]) return -1;
    return tree[x][k-1];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        rank[p[i]] = i;
        parent[i] = i;
        size[i] = 1;
        memset(tree[i], -1, sizeof(tree[i]));
        tree[i][0] = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char op[2];
        int x, y;
        scanf("%s %d %d", op, &x, &y);
        if (op[0] == 'Q') {
            printf("%d\n", query(x, y));
        } else {
            unite(x, y);
        }
    }
    return 0;
}