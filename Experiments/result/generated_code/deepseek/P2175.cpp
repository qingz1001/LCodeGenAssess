#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000

int N;
int trust[MAXN + 1][MAXN + 1];
int team[MAXN + 1];
int visited[MAXN + 1];

int dfs(int u, int t) {
    visited[u] = 1;
    team[u] = t;
    for (int i = 1; i <= N; i++) {
        if (trust[u][i]) {
            if (team[i] == t) return 0;
            if (!visited[i]) {
                if (!dfs(i, 3 - t)) return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int x;
        while (scanf("%d", &x) && x != 0) {
            trust[i][x] = 1;
        }
    }

    memset(team, 0, sizeof(team));
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            if (!dfs(i, 1)) {
                printf("No solution\n");
                return 0;
            }
        }
    }

    int count1 = 0, count2 = 0;
    for (int i = 1; i <= N; i++) {
        if (team[i] == 1) count1++;
        else count2++;
    }

    if (count1 < count2) printf("%d %d\n", count1, count2);
    else printf("%d %d\n", count2, count1);

    return 0;
}