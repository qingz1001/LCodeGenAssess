#include <stdio.h>

int n, p;
int tree[301][301];
int visited[301];

int dfs(int node) {
    visited[node] = 1;
    int count = 1;
    for (int i = 1; i <= n; i++) {
        if (tree[node][i] && !visited[i]) {
            count += dfs(i);
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < p; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        tree[x][y] = tree[y][x] = 1;
    }

    int infected = dfs(1);
    printf("%d\n", n - infected);

    return 0;
}