#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100005
#define MAX_M 6
#define INF INT_MAX

int n, Q;
int grid[MAX_M][MAX_N];
int dist[MAX_M][MAX_N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y, d;
} Node;

Node heap[MAX_M * MAX_N];
int heap_size = 0;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Node node) {
    int i = heap_size++;
    heap[i] = node;
    while (i > 0 && heap[(i - 1) / 2].d > heap[i].d) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node pop() {
    Node res = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < heap_size && heap[left].d < heap[smallest].d)
            smallest = left;
        if (right < heap_size && heap[right].d < heap[smallest].d)
            smallest = right;
        if (smallest == i) break;
        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
    return res;
}

int dijkstra(int sx, int sy, int ex, int ey) {
    for (int i = 0; i < MAX_M; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = INF;
    
    heap_size = 0;
    dist[sx][sy] = grid[sx][sy];
    push((Node){sx, sy, dist[sx][sy]});
    
    while (heap_size > 0) {
        Node cur = pop();
        int x = cur.x, y = cur.y;
        
        if (x == ex && y == ey) return dist[x][y];
        if (cur.d > dist[x][y]) continue;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= MAX_M || ny < 0 || ny >= n) continue;
            int new_dist = dist[x][y] + grid[nx][ny];
            if (new_dist < dist[nx][ny]) {
                dist[nx][ny] = new_dist;
                push((Node){nx, ny, new_dist});
            }
        }
    }
    return -1;  // Should never reach here
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < MAX_M; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &grid[i][j]);
    
    scanf("%d", &Q);
    while (Q--) {
        int op, x, y, c, x1, y1, x2, y2;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %d", &x, &y, &c);
            grid[x-1][y-1] = c;
        } else {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%d\n", dijkstra(x1-1, y1-1, x2-1, y2-1));
        }
    }
    return 0;
}