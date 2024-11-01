#include <stdio.h>
#include <stdlib.h>

#define MAXN 101
#define MAXM 3001

int n, m;
int enemies[MAXN][MAXN];
int in_team[MAXN];

void dfs(int u, int team) {
    if (in_team[u] != -1)
        return;
    in_team[u] = team;
    for (int v = 1; v <= n; ++v) {
        if (enemies[u][v]) {
            dfs(v, 1 - team);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            enemies[i][j] = 0;
        }
        in_team[i] = -1;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        enemies[u][v] = 1;
        enemies[v][u] = 1;
    }

    dfs(1, 0);

    int team_size = 0;
    for (int i = 1; i <= n; ++i) {
        if (in_team[i] == 0) {
            team_size++;
        }
    }

    printf("%d\n", team_size);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", in_team[i]);
    }
    printf("\n");

    return 0;
}