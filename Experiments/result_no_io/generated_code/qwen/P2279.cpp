#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n, a[MAXN];
int tree[MAXN][2];

void dfs(int node, int parent) {
    if (tree[node][0] == -1) {
        tree[node][0] = node;
    } else {
        tree[node][1] = node;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == node && i != parent) {
            dfs(i, node);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        tree[i][0] = -1;
        tree[i][1] = -1;
    }
    dfs(0, -1);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (tree[i][0] != -1) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}