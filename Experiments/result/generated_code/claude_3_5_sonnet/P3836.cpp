#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_M 1024
#define MAX_N 1024

char garden[MAX_M][MAX_N+1];
int m, n, k;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

int count_empty_neighbors(int x, int y) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny) && garden[nx][ny] == '.') {
            count++;
        }
    }
    return count;
}

void dfs(int x, int y) {
    garden[x][y] = 'X';
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny) && garden[nx][ny] == '.') {
            if (count_empty_neighbors(nx, ny) > 1) {
                dfs(nx, ny);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < m; i++) {
        scanf("%s", garden[i]);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (garden[i][j] == '.' && count_empty_neighbors(i, j) > 1) {
                dfs(i, j);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%s\n", garden[i]);
    }

    return 0;
}