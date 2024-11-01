#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 201

int grid[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n;

void floodFill(int x, int y) {
    if (x < 0 || x >= MAX_SIZE || y < 0 || y >= MAX_SIZE || visited[x][y] || grid[x][y] != 0) {
        return;
    }
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        floodFill(x + dx[i], y + dy[i]);
    }
}

int countHoles() {
    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (!visited[i][j] && grid[i][j] == 0) {
                count++;
                floodFill(i, j);
            }
        }
    }
    return count;
}

void cut(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        for (int i = y1 < y2 ? y1 : y2; i <= y1 > y2 ? y1 : y2; i++) {
            grid[x1][i] = 1;
        }
    } else {
        for (int i = x1 < x2 ? x1 : x2; i <= x1 > x2 ? x1 : x2; i++) {
            grid[i][y1] = 1;
        }
    }
}

int main() {
    int x1, y1, x2, y2;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        cut(x1, y1, x2, y2);
    }
    int holeCount = countHoles();
    printf("%d\n", holeCount);
    return 0;
}