#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_M 30
#define MAX_N 30
#define INF 0x3f3f3f3f

int P, M, N;
int pond[MAX_M][MAX_N];
int dist[MAX_M][MAX_N];
long long ways[MAX_M][MAX_N];
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

typedef struct {
    int x, y;
} Point;

Point queue[MAX_M * MAX_N];
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

void bfs(int sx, int sy) {
    memset(dist, 0x3f, sizeof(dist));
    memset(ways, 0, sizeof(ways));
    front = rear = 0;

    dist[sx][sy] = 0;
    ways[sx][sy] = 1;
    enqueue(sx, sy);

    while (!is_empty()) {
        Point cur = dequeue();
        int x = cur.x, y = cur.y;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || pond[nx][ny] == 2) continue;

            int new_dist = dist[x][y] + (pond[nx][ny] == 5 ? 2 : (pond[nx][ny] == 0 ? 1 : 0));
            if (new_dist < dist[nx][ny]) {
                dist[nx][ny] = new_dist;
                ways[nx][ny] = ways[x][y];
                enqueue(nx, ny);
            } else if (new_dist == dist[nx][ny]) {
                ways[nx][ny] += ways[x][y];
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &P, &M, &N);
    int sx, sy, ex, ey;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) sx = i, sy = j;
            if (pond[i][j] == 4) ex = i, ey = j;
        }
    }

    bfs(sx, sy);

    if (dist[ex][ey] > P) {
        printf("-1\n");
        return 0;
    }

    int S = dist[ex][ey];
    long long W_S = ways[ex][ey];
    printf("%d %lld\n", S, W_S);

    int G = 0;
    long long W_G = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (pond[i][j] == 5 && dist[i][j] <= S) {
                G++;
            }
        }
    }

    if (G == 0) {
        printf("-1\n");
    } else {
        W_G = ways[ex][ey];
        printf("%d %lld\n", G, W_G);
    }

    return 0;
}