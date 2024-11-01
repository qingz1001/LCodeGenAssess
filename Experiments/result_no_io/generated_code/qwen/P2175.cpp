#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2005

int N;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int team[MAX_N];

void dfs(int node, int t) {
    if (visited[node]) return;
    visited[node] = 1;
    team[node] = t;
    for (int i = 1; i <= N; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i, t);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 1; i <= N; i++) {
        int friend_id;
        while ((scanf("%d", &friend_id)) && friend_id != 0) {
            graph[i][friend_id] = 1;
            graph[friend_id][i] = 1;
        }
    }

    int found_solution = 0;
    int count[2] = {0};

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i, 1);
            count[0]++;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i, 2);
            count[1]++;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (team[i] == 1 && graph[i][i] == 0) {
            printf("No solution\n");
            return 0;
        }
    }

    if (abs(count[0] - count[1]) > 1) {
        printf("No solution\n");
    } else {
        if (count[0] < count[1]) {
            printf("%d %d\n", count[0], count[1]);
        } else {
            printf("%d %d\n", count[1], count[0]);
        }
    }

    return 0;
}