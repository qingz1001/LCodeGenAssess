#include <stdio.h>
#include <stdlib.h>

#define MAXN 5001

int n, m;
int graph[MAXN][MAXN];
int in_degree[MAXN];
int ranks[MAXN];
int visited[MAXN];

void dfs(int node) {
    visited[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
    ranks[++ranks[0]] = node;
}

int main() {
    scanf("%d %d", &n, &m);
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        in_degree[y]++;
    }

    int has_multiple_rankings = 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            if (!has_multiple_rankings) {
                dfs(i);
                has_multiple_rankings = 1;
            } else {
                has_multiple_rankings = 0;
                break;
            }
        }
    }

    if (!has_multiple_rankings) {
        printf("0\n");
        return 0;
    }

    for (int i = n; i > 0; i--) {
        printf("%d\n", ranks[i]);
    }
    printf("1\n");

    return 0;
}