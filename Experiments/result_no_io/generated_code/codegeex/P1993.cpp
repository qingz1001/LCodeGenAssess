#include <stdio.h>
#include <stdbool.h>

#define MAXN 5005

int n, m;
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

bool sameSet(int x, int y) {
    return find(x) == find(y);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (!sameSet(a, b)) {
                unionSets(a, b);
            }
        } else if (type == 2) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (sameSet(a, b)) {
                printf("No\n");
                return 0;
            }
        } else if (type == 3) {
            int a, b;
            scanf("%d %d", &a, &b);
            if (!sameSet(a, b)) {
                printf("No\n");
                return 0;
            }
        }
    }

    printf("Yes\n");
    return 0;
}