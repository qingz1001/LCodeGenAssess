#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000

int n, k;
int r[MAX_N];
int graph[MAX_N][MAX_N];

void init(int _k, int* _r, int _n) {
    k = _k;
    n = _n;
    memcpy(r, _r, n * sizeof(int));
    
    memset(graph, 0, sizeof(graph));
    
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 1; j < k; j++) {
            int next = (i + j) % n;
            if (count < r[i]) {
                graph[i][next] = -1;
                graph[next][i] = 1;
                count++;
            } else {
                graph[i][next] = 1;
                graph[next][i] = -1;
            }
        }
    }
}

int dfs(int start, int end, int* visited) {
    if (start == end) return 1;
    visited[start] = 1;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[start][i] == 1) {
            if (dfs(i, end, visited)) return 1;
        }
    }
    
    return 0;
}

int compare_plants(int x, int y) {
    int visited[MAX_N] = {0};
    if (dfs(x, y, visited)) return -1;
    
    memset(visited, 0, sizeof(visited));
    if (dfs(y, x, visited)) return 1;
    
    return 0;
}