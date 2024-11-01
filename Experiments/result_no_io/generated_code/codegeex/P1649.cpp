#include <stdio.h>
#include <string.h>

int N;
char map[101][101];
int visited[101][101][4];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct node {
    int x, y, direction, turns;
};

int min_turns(int startX, int startY, int endX, int endY) {
    memset(visited, -1, sizeof(visited));
    struct node queue[10001];
    int front = 0, rear = 0;
    queue[rear++] = (struct node){startX, startY, -1, 0};
    visited[startX][startY][0] = 0;

    while (front < rear) {
        struct node current = queue[front++];
        int cx = current.x, cy = current.y, cd = current.direction, ct = current.turns;

        if (cx == endX && cy == endY) {
            return ct;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N || map[nx][ny] == 'x') {
                continue;
            }
            if (cd == -1 || cd == i) {
                if (visited[nx][ny][i] == -1) {
                    visited[nx][ny][i] = 1;
                    queue[rear++] = (struct node){nx, ny, i, ct};
                }
            } else {
                if (visited[nx][ny][i] == -1) {
                    visited[nx][ny][i] = 1;
                    queue[rear++] = (struct node){nx, ny, i, ct + 1};
                }
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d", &N);
    int startX, startY, endX, endY;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &map[i][j]);
            if (map[i][j] == 'A') {
                startX = i;
                startY = j;
            } else if (map[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }
    int result = min_turns(startX, startY, endX, endY);
    printf("%d\n", result);
    return 0;
}