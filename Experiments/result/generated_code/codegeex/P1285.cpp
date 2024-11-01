#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

int n;
bool adj[MAXN][MAXN];
bool team[MAXN];
bool visited[MAXN];

void dfs(int node, int team_id) {
    team[node] = team_id;
    visited[node] = true;
    for (int i = 1; i <= n; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(i, team_id);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        while (x != 0) {
            adj[i][x] = true;
            scanf("%d", &x);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }

    int team0_count = 0, team1_count = 0;
    for (int i = 1; i <= n; i++) {
        if (team[i] == 0) {
            team0_count++;
        } else {
            team1_count++;
        }
    }

    if (team0_count == 0 || team1_count == 0) {
        printf("No solution\n");
        return 0;
    }

    printf("%d ", team0_count);
    for (int i = 1; i <= n; i++) {
        if (team[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("%d ", team1_count);
    for (int i = 1; i <= n; i++) {
        if (team[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}