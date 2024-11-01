#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 25
#define INF 0x3f3f3f3f

int r, c, d;
int heights[MAXN][MAXN];
char lizards[MAXN][MAXN];
int graph[MAXN * MAXN * 2][MAXN * MAXN * 2];
int source, sink;

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

int min(int a, int b) {
    return a < b ? a : b;
}

int id(int x, int y, int in) {
    return (x * c + y) * 2 + in;
}

bool in_range(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

void build_graph() {
    source = r * c * 2;
    sink = source + 1;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (heights[i][j] > 0) {
                graph[id(i, j, 0)][id(i, j, 1)] = heights[i][j];
                if (lizards[i][j] == 'L') {
                    graph[source][id(i, j, 0)] = 1;
                }
                if (i < d || i >= r - d || j < d || j >= c - d) {
                    graph[id(i, j, 1)][sink] = INF;
                }
                for (int k = 0; k < r; k++) {
                    for (int l = 0; l < c; l++) {
                        if ((i != k || j != l) && heights[k][l] > 0) {
                            int dist = (i - k) * (i - k) + (j - l) * (j - l);
                            if (dist <= d * d) {
                                graph[id(i, j, 1)][id(k, l, 0)] = INF;
                            }
                        }
                    }
                }
            }
        }
    }
}

int bfs(int parent[]) {
    bool visited[MAXN * MAXN * 2 + 2];
    memset(visited, 0, sizeof(visited));
    int queue[MAXN * MAXN * 2 + 2];
    int front = 0, rear = 0;
    queue[rear++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v <= sink; v++) {
            if (!visited[v] && graph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[sink];
}

int edmonds_karp() {
    int parent[MAXN * MAXN * 2 + 2];
    int max_flow = 0;

    while (bfs(parent)) {
        int path_flow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, graph[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &heights[i][j]);
        }
    }
    for (int i = 0; i < r; i++) {
        scanf("%s", lizards[i]);
    }

    build_graph();
    int total_lizards = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (lizards[i][j] == 'L') {
                total_lizards++;
            }
        }
    }

    int max_escape = edmonds_karp();
    printf("%d\n", total_lizards - max_escape);

    return 0;
}