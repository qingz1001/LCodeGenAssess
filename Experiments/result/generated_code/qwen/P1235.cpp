#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300

int parent[MAX_N + 1];
double similarity[MAX_N + 1][MAX_N + 1];

void dfs(int node, int depth) {
    if (parent[node] == -1) return;
    dfs(parent[node], depth + 1);
    similarity[node][parent[node]] = 0.5 * (1 + similarity[parent[node]][parent[node]]);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
        for (int j = 1; j <= n; j++) {
            similarity[i][j] = 0.0;
        }
    }

    for (int i = 0; i < k; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        parent[c] = b;
    }

    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%.1f%%\n", similarity[x][y] * 100);
    }

    return 0;
}