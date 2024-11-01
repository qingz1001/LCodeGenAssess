#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

int n;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int team[MAX_N];

void dfs(int node, int t) {
    if (visited[node]) return;
    visited[node] = 1;
    team[node] = t;
    for (int i = 0; graph[node][i]; ++i) {
        dfs(graph[node][i], t);
    }
}

int check() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; graph[i][j]; ++j) {
            if (team[i] == team[graph[i][j]]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int friend_id;
        while ((scanf("%d", &friend_id)) && friend_id != 0) {
            graph[i][friend_id - 1] = 1;
        }
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, count++);
        }
    }

    if (check()) {
        int a = 0, b = 0;
        for (int i = 0; i < n; ++i) {
            if (team[i] == 0) a++;
            else b++;
        }
        printf("%d %d\n", a, b);
    } else {
        printf("No solution\n");
    }

    return 0;
}