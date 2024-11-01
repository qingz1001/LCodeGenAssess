#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int graph[MAX_N][MAX_N];
int switch_state[MAX_N];
int visited[MAX_N];

void dfs(int start, int end, int current_switch, int *min_switches) {
    if (start == end) {
        if (*min_switches > current_switch) {
            *min_switches = current_switch;
        }
        return;
    }

    for (int i = 0; i < graph[start][0]; i++) {
        int next = graph[start][i + 1];
        if (!visited[next]) {
            visited[next] = 1;
            dfs(next, end, current_switch + (switch_state[next] != i), min_switches);
            visited[next] = 0;
        }
    }
}

int main() {
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &graph[i][0]);
        for (int j = 1; j <= graph[i][0]; j++) {
            scanf("%d", &graph[i][j]);
        }
        switch_state[i] = 0;
        visited[i] = 0;
    }

    int min_switches = -1;
    visited[A] = 1;
    dfs(A, B, 0, &min_switches);
    visited[A] = 0;

    printf("%d\n", min_switches);

    return 0;
}