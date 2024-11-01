#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100000
#define MAXQ 100000
#define MAX_VAL 10000

typedef struct {
    int x, y, c;
} Operation;

int grid[6][MAXN];
Operation ops[MAXQ];
int n, Q;

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int dijkstra(int x1, int y1, int x2, int y2) {
    int dist[6][n];
    int visited[6][n];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INT_MAX;
            visited[i][j] = 0;
        }
    }
    dist[x1][y1] = grid[x1][y1];

    for (int count = 0; count < 6 * n - 1; count++) {
        int minDist = INT_MAX;
        int minX = -1, minY = -1;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j] && dist[i][j] < minDist) {
                    minDist = dist[i][j];
                    minX = i;
                    minY = j;
                }
            }
        }

        if (minX == -1 || minY == -1) break;
        visited[minX][minY] = 1;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int nx = minX + dx[i];
            int ny = minY + dy[i];
            if (nx >= 0 && nx < 6 && ny >= 0 && ny < n) {
                if (!visited[nx][ny]) {
                    dist[nx][ny] = min(dist[nx][ny], dist[minX][minY] + grid[nx][ny]);
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
    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            x--; y--;
            ops[i].x = x;
            ops[i].y = y;
            ops[i].c = c;
        } else if (type == 2) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--; y1--; x2--; y2--;
            ops[i].x = x1;
            ops[i].y = y1;
            ops[i].c = x2 * n + y2;
        }
    }

    for (int i = 0; i < Q; i++) {
        if (ops[i].c >= 0) {
            int x1 = ops[i].x;
            int y1 = ops[i].y;
            int x2 = ops[i].c / n;
            int y2 = ops[i].c % n;
            printf("%d\n", dijkstra(x1, y1, x2, y2));
        } else {
            int x = ops[i].x;
            int y = ops[i].y;
            int c = -ops[i].c;
            grid[x][y] = c;
        }
    }

    return 0;
}