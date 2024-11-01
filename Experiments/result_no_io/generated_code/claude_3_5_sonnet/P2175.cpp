#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000

int N;
int trust[MAX_N + 1][MAX_N + 1];
int visited[MAX_N + 1];
int team[MAX_N + 1];
int team_size[2];

void dfs(int u, int t) {
    visited[u] = 1;
    team[u] = t;
    team_size[t]++;
    
    for (int v = 1; v <= N; v++) {
        if (trust[u][v] && !visited[v]) {
            dfs(v, t);
        }
    }
}

int main() {
    scanf("%d", &N);
    
    for (int i = 1; i <= N; i++) {
        int j;
        while (scanf("%d", &j) && j != 0) {
            trust[i][j] = trust[j][i] = 1;
        }
    }
    
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i, team_size[0] <= team_size[1] ? 0 : 1);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (trust[i][j] && team[i] != team[j]) {
                printf("No solution\n");
                return 0;
            }
        }
    }
    
    if (team_size[0] <= team_size[1]) {
        printf("%d %d\n", team_size[0], team_size[1]);
    } else {
        printf("%d %d\n", team_size[1], team_size[0]);
    }
    
    return 0;
}