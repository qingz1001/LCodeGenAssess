#include <stdio.h>
#include <string.h>

#define MAX_PATH 1000
#define MAX_SIZE 15

int maze[MAX_SIZE][MAX_SIZE];
int path[MAX_PATH][2];
int startX, startY, endX, endY;
int pathCount = 0;
int pathLength = 0;

void printPath() {
    for (int i = 0; i < pathLength; i++) {
        if (i > 0) printf("->");
        printf("(%d,%d)", path[i][0], path[i][1]);
    }
    printf("\n");
}

void findPath(int x, int y) {
    if (x < 0 || x >= MAX_SIZE || y < 0 || y >= MAX_SIZE || maze[x][y] == 0) {
        return;
    }
    path[pathLength][0] = x;
    path[pathLength][1] = y;
    pathLength++;
    if (x == endX && y == endY) {
        printPath();
    } else {
        // Left
        findPath(x, y - 1);
        // Up
        findPath(x - 1, y);
        // Right
        findPath(x, y + 1);
        // Down
        findPath(x + 1, y);
    }
    pathLength--;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    scanf("%d %d", &startX, &startY);
    scanf("%d %d", &endX, &endY);

    pathLength = 0;
    findPath(startX, startY);

    if (pathLength == 0) {
        printf("-1\n");
    }

    return 0;
}