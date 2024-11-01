#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 2001

int N;
bool trust[MAX_N][MAX_N];
int team[MAX_N];
int team_size[2];

bool dfs(int student, int t) {
    team[student] = t;
    team_size[t]++;

    for (int i = 1; i <= N; i++) {
        if (trust[student][i]) {
            if (team[i] == 1-t) return false;
            if (team[i] == -1 && !dfs(i, t)) return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &N);

    memset(trust, 0, sizeof(trust));
    for (int i = 1; i <= N; i++) {
        int j;
        while (scanf("%d", &j) && j != 0) {
            trust[i][j] = true;
        }
    }

    memset(team, -1, sizeof(team));
    memset(team_size, 0, sizeof(team_size));

    for (int i = 1; i <= N; i++) {
        if (team[i] == -1) {
            if (!dfs(i, 0)) {
                printf("No solution\n");
                return 0;
            }
        }
    }

    if (team_size[0] < team_size[1]) {
        printf("%d %d\n", team_size[0], team_size[1]);
    } else {
        printf("%d %d\n", team_size[1], team_size[0]);
    }

    return 0;
}