#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000

int n;
int a[MAXN + 1];
int in_degree[MAXN + 1];
int visited[MAXN + 1];
int max_students = 0;

void dfs(int u, int depth) {
    visited[u] = 1;
    if (a[u] != 0 && !visited[a[u]]) {
        dfs(a[u], depth + 1);
    } else {
        max_students = depth;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] != 0) {
            in_degree[a[i]]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            dfs(i, 1);
        }
    }

    printf("%d\n", max_students);
    return 0;
}