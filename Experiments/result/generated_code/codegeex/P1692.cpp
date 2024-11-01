#include <stdio.h>
#include <stdbool.h>

int n, m;
bool enemy[101][101];
int team[101];
int maxTeamSize = 0;
int bestTeam[101];

void backtrack(int current, int size) {
    if (current > n) {
        if (size > maxTeamSize) {
            maxTeamSize = size;
            for (int i = 1; i <= n; i++) {
                bestTeam[i] = team[i];
            }
        }
        return;
    }
    bool canAdd = true;
    for (int i = 1; i < current; i++) {
        if (team[i] && enemy[current][i]) {
            canAdd = false;
            break;
        }
    }
    if (canAdd) {
        team[current] = 1;
        backtrack(current + 1, size + 1);
        team[current] = 0;
    }
    backtrack(current + 1, size);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        enemy[u][v] = true;
        enemy[v][u] = true;
    }
    backtrack(1, 0);
    printf("%d\n", maxTeamSize);
    for (int i = 1; i <= n; i++) {
        printf("%d ", bestTeam[i]);
    }
    printf("\n");
    return 0;
}