#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 600005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], edgeCount;
int dist[MAXN], n, q;
int grid[6][MAXN];

void init() {
    memset(head, -1, sizeof(head));
    edgeCount = 0;
}

void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void addBidirectionalEdge(int u, int v, int w) {
    addEdge(u, v, w);
    addEdge(v, u, w);
}

void dijkstra(int start) {
    for (int i = 0; i < MAXN; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    // Dijkstra's algorithm
    // ...
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 6; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    scanf("%d", &q);
    init();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 6; j++) {
            if (j < 5) {
                addBidirectionalEdge((i - 1) * 6 + j, (i - 1) * 6 + j + 1, grid[j + 1][i] - grid[j][i]);
            }
            if (i < n) {
                addBidirectionalEdge((i - 1) * 6 + j, i * 6 + j, grid[j][i + 1] - grid[j][i]);
            }
        }
    }
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            // Update the grid and the corresponding edges
            // ...
        } else if (op == 2) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int start = (y1 - 1) * 6 + x1 - 1;
            int end = (y2 - 1) * 6 + x2 - 1;
            dijkstra(start);
            printf("%d\n", dist[end]);
        }
    }
    return 0;
}