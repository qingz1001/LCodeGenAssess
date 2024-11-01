#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 505
#define MAXM 505
#define MAXNQ 2500005

int n, m;
char grid[MAXN][MAXM];
int dist[MAXN][MAXM][2];

typedef struct {
    int x, y, g;
} Node;

Node q[MAXNQ];
int front, rear;

void enqueue(int x, int y, int g) {
    q[rear].x = x;
    q[rear].y = y;
    q[rear].g = g;
    rear++;
}

Node dequeue() {
    front++;
    return q[front - 1];
}

int isValid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && grid[x][y] != '#';
}

int bfs(int startX, int startY) {
    memset(dist, -1, sizeof(dist));
    front = rear = 0;
    enqueue(startX, startY, 0);
    dist[startX][startY][0] = 0;

    while (front < rear) {
        Node node = dequeue();
        int x = node.x, y = node.y, g = node.g;

        if (grid[x][y] == 'D') {
            return dist[x][y][g];
        }

        int nextX, nextY;
        if (g == 0) {
            nextX = x + 1;
            nextY = y;
        } else {
            nextX = x - 1;
            nextY = y;
        }

        if (isValid(nextX, nextY)) {
            if (dist[nextX][nextY][g] == -1) {
                enqueue(nextX, nextY, g);
                dist[nextX][nextY][g] = dist[x][y][g];
            }
        } else {
            if (isValid(x, y + 1) && dist[x][y + 1][1 - g] == -1) {
                enqueue(x, y + 1, 1 - g);
                dist[x][y + 1][1 - g] = dist[x][y][g] + 1;
            }
            if (isValid(x, y - 1) && dist[x][y - 1][1 - g] == -1) {
                enqueue(x, y - 1, 1 - g);
                dist[x][y - 1][1 - g] = dist[x][y][g] + 1;
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    int startX, startY;

    for (int i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == 'C') {
                startX = i;
                startY = j;
            }
        }
    }

    int result = bfs(startX, startY);
    printf("%d\n", result);
    return 0;
}