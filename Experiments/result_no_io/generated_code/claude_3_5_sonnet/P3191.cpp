#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_M 20
#define INF 0x3f3f3f3f

char map[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];
int n, m, people_count = 0;
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

bool is_empty() {
    return front == rear;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs() {
    front = rear = 0;
    memset(dist, INF, sizeof(dist));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 'D') {
                enqueue(i, j);
                dist[i][j] = 0;
            }
        }
    }

    while (!is_empty()) {
        Point curr = dequeue();
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (is_valid(nx, ny) && map[nx][ny] != 'X' && dist[nx][ny] == INF) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                enqueue(nx, ny);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < m; j++) {
            if (map[i][j] == '.') {
                people_count++;
            }
        }
    }

    bfs();

    int max_time = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == '.') {
                if (dist[i][j] == INF) {
                    printf("impossible\n");
                    return 0;
                }
                max_time = (max_time > dist[i][j]) ? max_time : dist[i][j];
            }
        }
    }

    printf("%d\n", max_time + people_count);
    return 0;
}