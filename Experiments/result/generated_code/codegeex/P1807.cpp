#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 1501
#define MAXM 50001

int n, m;
int dist[MAXN];
bool visited[MAXN];

typedef struct {
    int to;
    int weight;
} Edge;

Edge edges[MAXM];
int graph[MAXN][MAXN];
int inDegree[MAXN];

void addEdge(int u, int v, int w) {
    edges[m].to = v;
    edges[m].weight = w;
    graph[u][v] = w;
    inDegree[v]++;
    m++;
}

void topologicalSort() {
    int count = 0;
    int queue[MAXN];
    int front = 0, rear = 0;

    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != 0) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (count != n) {
        printf("-1\n");
        exit(0);
    }
}

void longestPath() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MIN;
    }
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int u = 1; u <= n; u++) {
            if (dist[u] != INT_MIN) {
                for (int v = 1; v <= n; v++) {
                    if (graph[u][v] != 0 && dist[v] < dist[u] + graph[u][v]) {
                        dist[v] = dist[u] + graph[u][v];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    topologicalSort();
    longestPath();

    if (dist[n] == INT_MIN) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[n]);
    }

    return 0;
}