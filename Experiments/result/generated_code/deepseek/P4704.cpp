#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int parent[MAXN * 2];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= 2 * n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        unionSet(a, b);
    }

    int components = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (parent[i] == i) {
            components++;
        }
    }

    printf("%d\n", components - 1);

    return 0;
}