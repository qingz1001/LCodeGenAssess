#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int parent[MAXN+1];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    int a, b, p;
    scanf("%d%d%d", &a, &b, &p);

    for (int i = 1; i <= b; i++) {
        parent[i] = i;
    }

    for (int i = a; i <= b; i++) {
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                if (j >= p) unite(i, j);
                if (i / j >= p) unite(i, i / j);
            }
        }
    }

    int count = 0;
    for (int i = a; i <= b; i++) {
        if (parent[i] == i) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}