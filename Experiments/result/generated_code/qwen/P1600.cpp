#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int tree[MAXN][2], weight[MAXN], player_start[MAXN], player_end[MAXN];
int result[MAXN];

void dfs(int node, int parent, int time) {
    if (weight[node] >= time) {
        result[node]++;
    }
    for (int i = 0; i < 2; i++) {
        int child = tree[node][i];
        if (child != -1 && child != parent) {
            dfs(child, node, time + 1);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        tree[u - 1][v - 1] = v - 1;
        tree[v - 1][u - 1] = u - 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &player_start[i], &player_end[i]);
    }

    for (int i = 0; i < m; i++) {
        dfs(player_end[i] - 1, -1, 0);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    return 0;
}