#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n;
int watched_by[MAXN];
int visited[MAXN];

int dfs(int u) {
    if (visited[u]) return 0;
    visited[u] = 1;
    int count = 1;
    for (int v = 1; v <= n; v++) {
        if (watched_by[v] == u && !visited[v]) {
            count += dfs(v);
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &watched_by[i]);
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            result = fmax(result, dfs(i));
        }
    }

    printf("%d\n", result);

    return 0;
}