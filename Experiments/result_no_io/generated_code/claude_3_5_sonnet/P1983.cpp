#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 1001

int n, m;
int graph[MAX_N][MAX_N];
int level[MAX_N];

void dfs(int station, int current_level) {
    level[station] = current_level;
    for (int i = 1; i <= n; i++) {
        if (graph[station][i] && level[i] < current_level) {
            dfs(i, current_level);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    memset(graph, 0, sizeof(graph));
    memset(level, 0, sizeof(level));

    for (int i = 0; i < m; i++) {
        int s, prev, curr;
        scanf("%d %d", &s, &prev);
        for (int j = 1; j < s; j++) {
            scanf("%d", &curr);
            graph[prev][curr] = 1;
            graph[curr][prev] = 1;
            prev = curr;
        }
    }

    int max_level = 0;
    for (int i = 1; i <= n; i++) {
        if (level[i] == 0) {
            dfs(i, ++max_level);
        }
    }

    printf("%d\n", max_level);

    return 0;
}