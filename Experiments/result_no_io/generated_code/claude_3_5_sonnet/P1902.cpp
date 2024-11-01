#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000
#define INF 0x3f3f3f3f

int n, m;
int p[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Point;

Point queue[MAX_N * MAX_M];
int front, rear;

void enqueue(int x, int y) {
    queue[rear].x = x;
    queue[rear].y = y;
    rear++;
}

Point dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void bfs() {
    memset(dist, 0x3f, sizeof(dist));
    front = rear = 0;

    for (int j = 0; j < m; j++) {
        dist[n-1][j] = 0;
        enqueue(n-1, j);
    }

    while (!isEmpty()) {
        Point curr = dequeue();
        int x = curr.x, y = curr.y;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int new_dist = max(dist[x][y], p[nx][ny]);
                if (new_dist < dist[nx][ny]) {
                    dist[nx][ny] = new_dist;
                    enqueue(nx, ny);
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i][j]);
        }
    }

    bfs();

    int result = INF;
    for (int j = 0; j < m; j++) {
        result = min(result, dist[0][j]);
    }

    printf("%d\n", result);

    return 0;
}