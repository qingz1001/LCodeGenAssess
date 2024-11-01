#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

int n;
int a[MAXN];
int tree[MAXN][2];
int visited[MAXN];
int result[MAXN];

void dfs(int node, int parent) {
    visited[node] = 1;
    int child_count = 0;
    for (int i = 0; i < 2 && tree[node][i] != -1; ++i) {
        if (tree[node][i] != parent) {
            dfs(tree[node][i], node);
            child_count += result[tree[node][i]];
        }
    }
    if (child_count == 0) {
        result[node] = 1;
    } else {
        result[node] = child_count + 1;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        tree[i][0] = -1;
        tree[i][1] = -1;
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (tree[x][0] == -1) {
            tree[x][0] = y;
        } else {
            tree[x][1] = y;
        }
        if (tree[y][0] == -1) {
            tree[y][0] = x;
        } else {
            tree[y][1] = x;
        }
    }
    dfs(a[1], -1);
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", result[i]);
    }
    return 0;
}