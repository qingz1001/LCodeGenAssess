#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXQ 100005
#define INF INT_MAX

int grid[6][MAXN];
int n, Q;

typedef struct {
    int x, y, dist;
} Node;

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int dijkstra(int x1, int y1, int x2, int y2) {
    int dist[6][n + 1];
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INF;
        }
    }
    dist[x1][y1] = grid[x1 - 1][y1 - 1];

    Node heap[6 * MAXN];
    int heapSize = 0;

    heap[heapSize++] = (Node){x1, y1, dist[x1][y1]};

    while (heapSize > 0) {
        // Find the node with the smallest distance
        int minIndex = 0;
        for (int i = 1; i < heapSize; i++) {
            if (heap[i].dist < heap[minIndex].dist) {
                minIndex = i;
            }
        }
        Node current = heap[minIndex];
        heap[minIndex] = heap[--heapSize];

        if (current.x == x2 && current.y == y2) {
            return current.dist;
        }

        // Explore neighbors
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 1 && nx <= 6 && ny >= 1 && ny <= n) {
                int newDist = current.dist + grid[nx - 1][ny - 1];
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    heap[heapSize++] = (Node){nx, ny, newDist};
                }
            }
        }
    }
    return dist[x2][y2];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    scanf("%d", &Q);
    for (int q = 0; q < Q; q++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            grid[x - 1][y - 1] = c;
        } else if (type == 2) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            int result = dijkstra(x1, y1, x2, y2);
            printf("%d\n", result);
        }
    }
    return 0;
}