#include <stdio.h>
#include <stdlib.h>

int parent[100001];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    int a, b, p;
    scanf("%d%d%d", &a, &b, &p);

    for (int i = a; i <= b; i++) {
        parent[i] = i;
    }

    for (int i = a; i <= b; i++) {
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                if (j >= p) {
                    union_sets(i, j);
                }
                if (j * j != i && i / j >= p) {
                    union_sets(i, i / j);
                }
            }
        }
    }

    int set_count = 0;
    for (int i = a; i <= b; i++) {
        if (parent[i] == i) {
            set_count++;
        }
    }

    printf("%d\n", set_count);
    return 0;
}