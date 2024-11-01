#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXM 200

int n, m;
char front[MAXN][MAXM];
char back[MAXN][MAXM];
int visited[MAXN][MAXM];

typedef struct {
    int x, y;
} Point;

Point directions[4] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

int isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y, int *count) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i].x;
        int ny = y + directions[i].y;
        if (isValid(nx, ny) && !visited[nx][ny]) {
            if ((front[x][y] == '/' && back[nx][ny] == '\\') || (front[x][y] == '\\' && back[nx][ny] == '/')) {
                dfs(nx, ny, count);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", back[i]);
    }

    int totalStitches = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                if ((front[i][j] == '/' && back[i][j] == '\\') || (front[i][j] == '\\' && back[i][j] == '/')) {
                    totalStitches++;
                    dfs(i, j, &totalStitches);
                }
            }
        }
    }

    printf("%d\n", totalStitches);
    return 0;
}