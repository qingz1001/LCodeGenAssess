#include <stdio.h>
#include <stdlib.h>

#define MAX_W 501
#define MAX_L 501
#define MAX_HEIGHT 10000

int W, L;
int heights[MAX_L][MAX_W];
int visited[MAX_L][MAX_W];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

typedef struct {
    int x;
    int y;
} Point;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void dfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < L && ny >= 0 && ny < W && heights[nx][ny] < heights[x][y] && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &W, &L);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &heights[i][j]);
        }
    }

    // Sort heights in descending order
    int total_heights[MAX_W * MAX_L];
    int index = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            total_heights[index++] = heights[i][j];
        }
    }
    qsort(total_heights, index, sizeof(int), compare);

    // Initialize visited array
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            visited[i][j] = 0;
        }
    }

    int cable_cars = 0;
    for (int h = MAX_HEIGHT; h >= 0; h--) {
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < W; j++) {
                if (heights[i][j] == h && !visited[i][j]) {
                    dfs(i, j);
                    cable_cars++;
                }
            }
        }
    }

    printf("%d\n", cable_cars);
    return 0;
}