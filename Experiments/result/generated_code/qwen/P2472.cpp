#include <stdio.h>
#include <stdlib.h>

#define MAXR 20
#define MAXC 20

int r, c, d;
int grid[MAXR][MAXC];
char lizards[MAXR][MAXC];

void bfs(int x, int y) {
    int queue[MAXR * MAXC][2];
    int front = 0, rear = 0;
    queue[rear][0] = x;
    queue[rear++][1] = y;
    while (front != rear) {
        int cx = queue[front][0];
        int cy = queue[front++][1];
        for (int dx = -d; dx <= d; dx++) {
            for (int dy = -d; dy <= d; dy++) {
                if (dx * dx + dy * dy > d * d) continue;
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] > 0) {
                    grid[nx][ny]--;
                    if (grid[nx][ny] == 0) {
                        lizards[nx][ny] = '.';
                    } else {
                        queue[rear][0] = nx;
                        queue[rear++][1] = ny;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    for (int i = 0; i < r; i++) {
        scanf("%s", lizards[i]);
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (lizards[i][j] == 'L') {
                bfs(i, j);
            }
        }
    }

    int result = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (lizards[i][j] == 'L') {
                result++;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}