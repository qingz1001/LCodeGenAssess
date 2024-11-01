#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n;
int a[MAXN];
int in_degree[MAXN];
int visited[MAXN];

int max(int x, int y) {
    return x > y ? x : y;
}

int dfs(int u) {
    visited[u] = 1;
    if (visited[a[u]]) {
        return 1;
    }
    return 1 + dfs(a[u]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        in_degree[a[i]]++;
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            result += dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            result += dfs(i) / 2;
        }
    }

    printf("%d\n", result);
    return 0;
}