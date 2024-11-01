#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 32
#define MAX_M 1000

int N, M;
int graph[MAX_N][MAX_N];
int cost[MAX_N][MAX_N];
int minCost = INT_MAX;
int minCount = INT_MAX;

void dfs(int node, int curCost, int curCount, int visited[]) {
    if (node == N) {
        if (curCost < minCost || (curCost == minCost && curCount < minCount)) {
            minCost = curCost;
            minCount = curCount;
        }
        return;
    }
    
    for (int i = 1; i <= N; i++) {
        if (graph[node][i] && !visited[i]) {
            visited[i] = 1;
            dfs(i, curCost, curCount, visited);
            visited[i] = 0;
        }
    }
    
    for (int i = 1; i <= N; i++) {
        if (graph[node][i]) {
            graph[node][i] = 0;
            int newCost = curCost + cost[node][i];
            if (newCost < minCost) {
                dfs(1, newCost, curCount + 1, visited);
            }
            graph[node][i] = 1;
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        int s, e, c;
        scanf("%d %d %d", &s, &e, &c);
        graph[s][e] = 1;
        cost[s][e] = c;
    }
    
    int visited[MAX_N] = {0};
    visited[1] = 1;
    dfs(1, 0, 0, visited);
    
    printf("%d %d\n", minCost, minCount);
    
    return 0;
}