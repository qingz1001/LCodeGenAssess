#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 15

int m, n;
int maze[MAX_SIZE][MAX_SIZE];
int startX, startY, endX, endY;
int path[MAX_SIZE * MAX_SIZE][2];
int pathLength = 0;
bool visited[MAX_SIZE][MAX_SIZE];
bool foundPath = false;

int dx[] = {0, -1, 0, 1};  // 左上右下
int dy[] = {-1, 0, 1, 0};

void printPath() {
    printf("(%d,%d)", startX, startY);
    for (int i = 0; i < pathLength; i++) {
        printf("->(%d,%d)", path[i][0], path[i][1]);
    }
    printf("\n");
}

void dfs(int x, int y) {
    if (x == endX && y == endY) {
        foundPath = true;
        printPath();
        return;
    }

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < m && newY >= 0 && newY < n && maze[newX][newY] == 1 && !visited[newX][newY]) {
            visited[newX][newY] = true;
            path[pathLength][0] = newX;
            path[pathLength][1] = newY;
            pathLength++;

            dfs(newX, newY);

            visited[newX][newY] = false;
            pathLength--;
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

    visited[startX][startY] = true;
    dfs(startX, startY);

    if (!foundPath) {
        printf("-1\n");
    }

    return 0;
}