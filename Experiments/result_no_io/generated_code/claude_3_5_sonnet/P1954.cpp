#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2005
#define MAXM 10005

int n, m;
int k[MAXN];
int graph[MAXN][MAXN];
int in_degree[MAXN];
int queue[MAXN], front, rear;
int topo[MAXN], topo_cnt;
int earliest[MAXN];

void topological_sort() {
    front = rear = 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    while (front < rear) {
        int u = queue[front++];
        topo[topo_cnt++] = u;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v]) {
                if (--in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (!graph[a][b]) {
            graph[a][b] = 1;
            in_degree[b]++;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = k[i] + 1; j <= n; j++) {
            if (!graph[i][j]) {
                graph[i][j] = 1;
                in_degree[j]++;
            }
        }
    }
    
    topological_sort();
    
    for (int i = 0; i < n; i++) {
        printf("%d ", topo[i]);
    }
    printf("\n");
    
    memset(earliest, 0, sizeof(earliest));
    for (int i = 0; i < n; i++) {
        int u = topo[i];
        earliest[u] = i + 1;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v]) {
                if (earliest[v] < earliest[u] + 1) {
                    earliest[v] = earliest[u] + 1;
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%d ", earliest[i]);
    }
    printf("\n");
    
    return 0;
}