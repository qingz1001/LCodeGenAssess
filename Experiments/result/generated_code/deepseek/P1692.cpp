#include <stdio.h>
#include <stdbool.h>

#define MAXN 101
#define MAXM 3001

int n, m;
bool enemies[MAXN][MAXN];
bool in_team[MAXN];
bool best_team[MAXN];
int best_count = 0;

void dfs(int idx, int count) {
    if (idx > n) {
        if (count > best_count) {
            best_count = count;
            for (int i = 1; i <= n; i++) {
                best_team[i] = in_team[i];
            }
        }
        return;
    }

    // Try adding the current resident to the team
    bool can_add = true;
    for (int i = 1; i < idx; i++) {
        if (in_team[i] && enemies[idx][i]) {
            can_add = false;
            break;
        }
    }

    if (can_add) {
        in_team[idx] = true;
        dfs(idx + 1, count + 1);
        in_team[idx] = false;
    }

    // Try not adding the current resident to the team
    dfs(idx + 1, count);
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

    printf("%d\n", best_count);
    for (int i = 1; i <= n; i++) {
        printf("%d ", best_team[i] ? 1 : 0);
    }
    printf("\n");

    return 0;
}