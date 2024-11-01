#include <stdio.h>
#include <string.h>

#define MAX_LETTERS 26

int graph[MAX_LETTERS][MAX_LETTERS];
int degree[MAX_LETTERS];
int visited[MAX_LETTERS];
char result[MAX_LETTERS + 1];
int result_index;

void dfs(int node) {
    for (int i = 0; i < MAX_LETTERS; i++) {
        if (graph[node][i]) {
            graph[node][i]--;
            graph[i][node]--;
            dfs(i);
        }
    }
    result[result_index++] = node + 'A';
}

int main() {
    int n;
    scanf("%d", &n);

    memset(graph, 0, sizeof(graph));
    memset(degree, 0, sizeof(degree));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < n; i++) {
        char a, b;
        scanf(" %c%c", &a, &b);
        int u = a - 'A';
        int v = b - 'A';
        graph[u][v]++;
        graph[v][u]++;
        degree[u]++;
        degree[v]++;
    }

    int start = -1;
    for (int i = 0; i < MAX_LETTERS; i++) {
        if (degree[i] % 2 == 1) {
            if (start == -1) {
                start = i;
            } else {
                printf("No Solution\n");
                return 0;
            }
        }
    }

    if (start == -1) {
        for (int i = 0; i < MAX_LETTERS; i++) {
            if (degree[i] > 0) {
                start = i;
                break;
            }
        }
    }

    dfs(start);

    if (result_index != n + 1) {
        printf("No Solution\n");
    } else {
        for (int i = result_index - 1; i >= 0; i--) {
            printf("%c", result[i]);
        }
        printf("\n");
    }

    return 0;
}