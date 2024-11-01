#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 505
#define MAXM 505

int n, m;
char grid[MAXN][MAXM];
int dist[MAXN][MAXM][2];

typedef struct {
    int x, y, dir;
} Point;

int min(int a, int b) {
    return a < b ? a : b;
}

int isValid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && grid[x][y] != '#';
}

int bfs(int startX, int startY) {
    memset(dist, -1, sizeof(dist));
    dist[startX][startY][0] = 0;
    Point q[MAXN * MAXM], *front = q, *rear = q;
    (*rear).x = startX;
    (*rear).y = startY;
    (*rear).dir = 0;
    rear++;

    while (front != rear) {
        Point cur = *front;
        front++;

        int x = cur.x;
        int y = cur.y;
        int dir = cur.dir;

        if (grid[x][y] == 'D') {
            return dist[x][y][dir];
        }

        if (dir == 0) { // Gravity pointing down
            if (isValid(x + 1, y)) {
                if (dist[x + 1][y][dir] == -1) {
                    (*rear).x = x + 1;
                    (*rear).y = y;
                    (*rear).dir = dir;
                    rear++;
                    dist[x + 1][y][dir] = dist[x][y][dir];
                }
            } else {
                if (isValid(x, y - 1) && dist[x][y - 1][1] == -1) {
                    (*rear).x = x;
                    (*rear).y = y - 1;
                    (*rear).dir = 1;
                    rear++;
                    dist[x][y - 1][1] = dist[x][y][0] + 1;
                }
                if (isValid(x, y + 1) && dist[x][y + 1][1] == -1) {
                    (*rear).x = x;
                    (*rear).y = y + 1;
                    (*rear).dir = 1;
                    rear++;
                    dist[x][y + 1][1] = dist[x][y][0] + 1;
                }
            }
        } else { // Gravity pointing up
            if (isValid(x - 1, y)) {
                if (dist[x - 1][y][dir] == -1) {
                    (*rear).x = x - 1;
                    (*rear).y = y;
                    (*rear).dir = dir;
                    rear++;
                    dist[x - 1][y][dir] = dist[x][y][dir];
                }
            } else {
                if (isValid(x, y - 1) && dist[x][y - 1][0] == -1) {
                    (*rear).x = x;
                    (*rear).y = y - 1;
                    (*rear).dir = 0;
                    rear++;
                    dist[x][y - 1][0] = dist[x][y][1] + 1;
                }
                if (isValid(x, y + 1) && dist[x][y + 1][0] == -1) {
                    (*rear).x = x;
                    (*rear).y = y + 1;
                    (*rear).dir = 0;
                    rear++;
                    dist[x][y + 1][0] = dist[x][y][1] + 1;
                }
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