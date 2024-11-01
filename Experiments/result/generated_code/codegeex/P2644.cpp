#include <stdio.h>
#include <stdlib.h>

#define MAXN 31

int map[MAXN][MAXN];
int m, n, p;
long long minP = LLONG_MAX, minW = 0, maxG = 0, maxW = 0;

struct Node {
    int x, y, p, g;
    long long w;
};

void bfs() {
    struct Node queue[MAXN * MAXN];
    int front = 0, rear = 0;
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int visited[MAXN][MAXN];
    int platinum[MAXN][MAXN];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
            platinum[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 3) {
                queue[rear].x = i;
                queue[rear].y = j;
                queue[rear].p = 0;
                queue[rear].g = 0;
                queue[rear].w = 1;
                rear++;
                visited[i][j] = 1;
                break;
            }
        }
    }

    while (front < rear) {
        struct Node cur = queue[front];
        front++;
        for (int i = 0; i < 8; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                if (map[nx][ny] == 1 || map[nx][ny] == 4) {
                    if (cur.p + 2 <= p) {
                        if (map[nx][ny] == 4) {
                            if (cur.p + 2 < minP) {
                                minP = cur.p + 2;
                                minW = cur.w;
                                maxG = cur.g;
                                maxW = cur.w;
                            } else if (cur.p + 2 == minP) {
                                minW += cur.w;
                                if (cur.g > maxG) {
                                    maxG = cur.g;
                                    maxW = cur.w;
                                } else if (cur.g == maxG) {
                                    maxW += cur.w;
                                }
                            }
                        }
                        visited[nx][ny] = 1;
                        queue[rear].x = nx;
                        queue[rear].y = ny;
                        queue[rear].p = cur.p + 2;
                        queue[rear].g = cur.g;
                        queue[rear].w = cur.w;
                        rear++;
                    }
                } else if (map[nx][ny] == 5) {
                    if (cur.p + 4 <= p) {
                        visited[nx][ny] = 1;
                        platinum[nx][ny] = 1;
                        queue[rear].x = nx;
                        queue[rear].y = ny;
                        queue[rear].p = cur.p + 4;
                        queue[rear].g = cur.g + 1;
                        queue[rear].w = cur.w;
                        rear++;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &p, &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    bfs();

    if (minP == LLONG_MAX) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", minP, minW);
        if (maxG == 0) {
            printf("-1\n");
        } else {
            printf("%lld %lld\n", maxG, maxW);
        }
    }

    return 0;
}