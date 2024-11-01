#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 33
#define MAX_M 1001

int N, M;
int graph[MAX_N][MAX_N];
int cost[MAX_N][MAX_N];
int visited[MAX_N];
int minCost = INT_MAX;
int minCount = INT_MAX;

void dfs(int node, int currentCost, int currentCount) {
    if (node == N) {
        if (currentCost < minCost || (currentCost == minCost && currentCount < minCount)) {
            minCost = currentCost;
            minCount = currentCount;
        }
        return;
    }

    visited[node] = 1;

    for (int i = 1; i <= N; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i, currentCost, currentCount);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (graph[node][i] && !visited[i]) {
            graph[node][i] = 0;
            dfs(i, currentCost + cost[node][i], currentCount + 1);
            graph[node][i] = 1;
        }
    }

    visited[node] = 0;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        int s, e, c;
        scanf("%d %d %d", &s, &e, &c);
        graph[s][e] = 1;
        cost[s][e] = c;
    }

    dfs(1, 0, 0);

    printf("%d %d\n", minCost, minCount);

    return 0;
}