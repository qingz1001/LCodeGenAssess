#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100010
#define INF 0x3f3f3f3f

int grid[7][MAXN];
int dist[7][MAXN];
int n, Q;

void dijkstra(int x1, int y1) {
    memset(dist, 0x3f, sizeof(dist));
    dist[x1][y1] = 0;
    typedef struct { int x, y, d; } Node;
    Node q[MAXN * 2];
    int front = 0, rear = 0;
    q[rear++] = (Node){x1, y1, 0};
    while (front != rear) {
        Node u = q[front++];
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) == 1) {
                    int x = u.x + dx, y = u.y + dy;
                    if (x >= 1 && x <= 6 && y >= 1 && y <= n) {
                        int d = u.d + grid[x][y];
                        if (dist[x][y] > d) {
                            dist[x][y] = d;
                            q[rear++] = (Node){x, y, d};
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }
    scanf("%d", &Q);
    for (int i = 0; i < Q; ++i) {
        char op[2];
        scanf("%s", op);
        if (op[0] == '1') {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            grid[x][y] = c;
        } else {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            dijkstra(x1, y1);
            printf("%d\n", dist[x2][y2]);
        }
    }
    return 0;
}