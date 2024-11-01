#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int m, n;
int maze[MAX][MAX];
int startX, startY, endX, endY;
int visited[MAX][MAX];

int directions[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}}; // 左上右下

void printPath(int path[][2], int length) {
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            printf("(%d,%d)", path[i][0], path[i][1]);
        } else {
            printf("->(%d,%d)", path[i][0], path[i][1]);
        }
    }
    printf("\n");
}

void findPaths(int x, int y, int path[][2], int length) {
    if (x == endX && y == endY) {
        printPath(path, length);
        return;
    }

    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        if (newX >= 0 && newX < m && newY >= 0 && newY < n && maze[newX][newY] == 1 && !visited[newX][newY]) {
            visited[newX][newY] = 1;
            path[length][0] = newX;
            path[length][1] = newY;
            findPaths(newX, newY, path, length + 1);
            visited[newX][newY] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    scanf("%d %d", &startX, &startY);
    scanf("%d %d", &endX, &endY);

    if (maze[startX][startY] == 0 || maze[endX][endY] == 0) {
        printf("-1\n");
        return 0;
    }

    int path[MAX * MAX][2];
    path[0][0] = startX;
    path[0][1] = startY;
    visited[startX][startY] = 1;

    findPaths(startX, startY, path, 1);

    // Check if no path was found
    int found = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j]) {
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("-1\n");
    }

    return 0;
}