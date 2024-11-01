#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_M 3000

int n, m;
bool enemy[MAX_N + 1][MAX_N + 1];
int team[MAX_N + 1];
int best_team[MAX_N + 1];
int max_count = 0;

void dfs(int person, int count) {
    if (person > n) {
        if (count > max_count) {
            max_count = count;
            memcpy(best_team, team, sizeof(team));
        } else if (count == max_count) {
            for (int i = n; i >= 1; i--) {
                if (team[i] != best_team[i]) {
                    if (team[i] > best_team[i]) {
                        memcpy(best_team, team, sizeof(team));
                    }
                    break;
                }
            }
        }
        return;
    }

    bool can_join = true;
    for (int i = 1; i < person; i++) {
        if (team[i] && enemy[person][i]) {
            can_join = false;
            break;
        }
    }

    if (can_join) {
        team[person] = 1;
        dfs(person + 1, count + 1);
    }

    team[person] = 0;
    dfs(person + 1, count);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        enemy[u][v] = enemy[v][u] = true;
    }

    dfs(1, 0);

    printf("%d\n", max_count);
    for (int i = 1; i <= n; i++) {
        printf("%d ", best_team[i]);
    }
    printf("\n");

    return 0;
}