#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_SOLUTIONS 10000

int n, m;
bool graph[MAX_N + 1][MAX_N + 1];
int path[MAX_N + 1];
bool visited[MAX_N + 1];
int solutions[MAX_SOLUTIONS][MAX_N + 1];
int solution_count = 0;

void dfs(int depth) {
    if (depth == n && graph[path[n]][1]) {
        for (int i = 1; i <= n; i++) {
            solutions[solution_count][i] = path[i];
        }
        solution_count++;
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && graph[path[depth]][i]) {
            visited[i] = true;
            path[depth + 1] = i;
            dfs(depth + 1);
            visited[i] = false;
        }
    }
}

int compare(const void *a, const void *b) {
    int *arr1 = (int *)a;
    int *arr2 = (int *)b;
    for (int i = 1; i <= n; i++) {
        if (arr1[i] != arr2[i]) {
            return arr1[i] - arr2[i];
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = true;
    }

    path[1] = 1;
    visited[1] = true;
    dfs(1);

    qsort(solutions, solution_count, sizeof(solutions[0]), compare);

    for (int i = 0; i < solution_count; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", solutions[i][j]);
        }
        printf("\n");
    }

    return 0;
}