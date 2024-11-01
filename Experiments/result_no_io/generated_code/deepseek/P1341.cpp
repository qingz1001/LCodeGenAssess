#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_CHAR 256

int graph[MAX_CHAR][MAX_CHAR];
int degree[MAX_CHAR];
int visited[MAX_CHAR];
char result[MAX_N + 2];
int result_index;

void dfs(int node) {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (graph[node][i]) {
            graph[node][i]--;
            graph[i][node]--;
            dfs(i);
        }
    }
    result[result_index++] = node;
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
        graph[a][b]++;
        graph[b][a]++;
        degree[a]++;
        degree[b]++;
    }

    int start = -1;
    int odd_count = 0;

    for (int i = 0; i < MAX_CHAR; i++) {
        if (degree[i] % 2 == 1) {
            odd_count++;
            if (start == -1) {
                start = i;
            }
        }
    }

    if (odd_count != 0 && odd_count != 2) {
        printf("No Solution\n");
        return 0;
    }

    if (start == -1) {
        for (int i = 0; i < MAX_CHAR; i++) {
            if (degree[i] > 0) {
                start = i;
                break;
            }
        }
    }

    result_index = 0;
    dfs(start);

    if (result_index != n + 1) {
        printf("No Solution\n");
        return 0;
    }

    for (int i = result_index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");

    return 0;
}