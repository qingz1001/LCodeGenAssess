#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 100005

int N, M;
int graph[MAXN][MAXN];
int in_degree[MAXN];
int visited[MAXN];
int rank[MAXN];
int stack[MAXN], top;

void dfs(int u) {
    visited[u] = 1;
    for (int v = 1; v <= N; v++) {
        if (graph[u][v] && !visited[v]) {
            dfs(v);
        }
    }
    stack[top++] = u;
}

int main() {
    scanf("%d", &N);
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (!graph[y][x]) {
            graph[y][x] = 1;
            in_degree[x]++;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    int multiple_rankings = 0;
    for (int i = N - 1; i >= 0; i--) {
        rank[stack[i]] = N - i;
        if (i < N - 1 && in_degree[stack[i]] == in_degree[stack[i+1]]) {
            multiple_rankings = 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (rank[i] < rank[j] && !graph[j][i]) {
                multiple_rankings = 1;
                break;
            }
        }
        if (multiple_rankings) break;
    }

    int order[MAXN];
    for (int i = 1; i <= N; i++) {
        order[rank[i]] = i;
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", order[i]);
    }
    printf("%d\n", multiple_rankings);

    return 0;
}