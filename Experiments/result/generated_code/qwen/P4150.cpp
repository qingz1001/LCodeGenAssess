#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100010
#define INF INT_MAX

int n, Q;
int grid[6][MAXN];
int dist[6][MAXN];

void dijkstra(int start_x, int start_y) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = INF;
        }
    }
    dist[start_x][start_y] = 0;

    typedef struct {
        int x, y, cost;
    } Node;

    Node pq[MAXN * 6];
    int pq_size = 0;
    void push(int x, int y, int cost) {
        pq[pq_size++] = (Node){x, y, cost};
        int i = pq_size - 1;
        while (i > 0 && pq[(i - 1) / 2].cost > pq[i].cost) {
            Node tmp = pq[(i - 1) / 2];
            pq[(i - 1) / 2] = pq[i];
            pq[i] = tmp;
            i = (i - 1) / 2;
        }
    }
    Node pop() {
        Node res = pq[0];
        pq[0] = pq[--pq_size];
        int i = 0;
        while ((i * 2 + 1 < pq_size && pq[i].cost > pq[i * 2 + 1].cost) || (i * 2 + 2 < pq_size && pq[i].cost > pq[i * 2 + 2].cost)) {
            if (i * 2 + 2 >= pq_size || pq[i * 2 + 1].cost <= pq[i * 2 + 2].cost) {
                Node tmp = pq[i * 2 + 1];
                pq[i * 2 + 1] = pq[i];
                pq[i] = tmp;
                i = i * 2 + 1;
            } else {
                Node tmp = pq[i * 2 + 2];
                pq[i * 2 + 2] = pq[i];
                pq[i] = tmp;
                i = i * 2 + 2;
            }
        }
        return res;
    }

    push(start_x, start_y, 0);
    int dx[] = {0, 0, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1};

    while (pq_size > 0) {
        Node u = pop();
        if (dist[u.x][u.y] != u.cost) continue;
        for (int k = 0; k < 6; ++k) {
            int nx = u.x + dx[k], ny = u.y + dy[k];
            if (nx >= 1 && nx <= 6 && ny >= 1 && ny <= n) {
                int new_cost = u.cost + abs(grid[nx - 1][ny - 1]);
                if (new_cost < dist[nx - 1][ny - 1]) {
                    dist[nx - 1][ny - 1] = new_cost;
                    push(nx, ny, new_cost);
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }
    scanf("%d", &Q);

    for (int q = 0; q < Q; ++q) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            grid[x - 1][y - 1] = c;
        } else {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            dijkstra(x1, y1);
            printf("%d\n", dist[x2 - 1][y2 - 1]);
        }
    }

    return 0;
}