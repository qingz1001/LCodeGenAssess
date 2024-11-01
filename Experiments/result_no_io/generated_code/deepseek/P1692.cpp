#include <stdio.h>
#include <stdbool.h>

#define MAXN 101
#define MAXM 3001

int n, m;
bool enemies[MAXN][MAXN];
int max_team_size = 0;
int best_team[MAXN];
int current_team[MAXN];

void dfs(int idx, int team_size) {
    if (idx > n) {
        if (team_size > max_team_size) {
            max_team_size = team_size;
            for (int i = 1; i <= n; i++) {
                best_team[i] = current_team[i];
            }
        }
        return;
    }

    // Check if we can add the current resident to the team
    bool can_add = true;
    for (int i = 1; i < idx; i++) {
        if (current_team[i] && enemies[idx][i]) {
            can_add = false;
            break;
        }
    }

    if (can_add) {
        current_team[idx] = 1;
        dfs(idx + 1, team_size + 1);
        current_team[idx] = 0;
    }

    // Try not adding the current resident to the team
    dfs(idx + 1, team_size);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        enemies[u][v] = true;
        enemies[v][u] = true;
    }

    dfs(1, 0);

    printf("%d\n", max_team_size);
    for (int i = 1; i <= n; i++) {
        printf("%d ", best_team[i]);
    }
    printf("\n");

    return 0;
}