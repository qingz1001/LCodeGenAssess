#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXW 505
#define MAXH 505

typedef struct {
    int x, y;
} Point;

int n, w, h;
char grid[MAXH][MAXW];
Point robots[MAXN];
int visited[MAXN];

void moveRobot(int id) {
    Point *r = &robots[id];
    while (1) {
        if (grid[r->y][r->x + 1] == 'x' || r->x + 1 >= w) break;
        r->x++;
    }
    if (visited[id]) return;
    visited[id] = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && abs(robots[i].x - r->x) == 1 && robots[i].y == r->y) {
            moveRobot(i);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 0; i < h; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < w; j++) {
            if ('1' <= grid[i][j] && grid[i][j] <= '9') {
                robots[grid[i][j] - '1'] = (Point){j, i};
            }
        }
    }

    int pushes = 0;
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        moveRobot(i);
        if (!visited[i]) {
            printf("-1\n");
            return 0;
        }
        pushes++;
    }

    printf("%d\n", pushes);
    return 0;
}