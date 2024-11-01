#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int n, t, m;
int parent[MAXN];
int visited[MAXN];

void dfs(int node) {
    visited[node] = 1;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (parent[a] == 0) parent[a] = b;
        else if (parent[b] == 0) parent[b] = a;
    }
}

int find(int x) {
    while (x != parent[x]) {
        x = parent[x];
    }
    return x;
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    dfs(1);
    int operations = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            union_set(i, t);
            operations++;
        }
    }
    printf("%d\n", operations);
    return 0;
}