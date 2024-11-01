#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int parent[MAXN];
int size[MAXN];

void init() {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void merge(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) return;
    if (size[px] > size[py]) {
        parent[py] = px;
        size[px] += size[py];
    } else {
        parent[px] = py;
        size[py] += size[px];
    }
}

int query(int x) {
    return size[find(x)];
}

int main() {
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n - 1; i++) {
        int dep;
        scanf("%d", &dep);
        merge(i + 1, dep);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        char op[10];
        int x;
        scanf("%s %d", op, &x);
        if (op[0] == 'i') {
            printf("%d\n", query(x));
            merge(0, x);
        } else {
            printf("%d\n", query(x));
            parent[x] = x;
            size[x] = 1;
        }
    }
    return 0;
}