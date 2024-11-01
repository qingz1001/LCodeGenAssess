#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXM 55

int n, m;
int grid[MAXN][MAXM];
int visited[MAXN][MAXM];
int rooms;
int max_room_size;
int best_wall_row, best_wall_col, best_wall_direction;

void dfs(int row, int col) {
    if (row < 0 || row >= n || col < 0 || col >= m || visited[row][col]) return;
    visited[row][col] = 1;
    int size = 1;
    if (!(grid[row][col] & 1)) dfs(row, col - 1); // West
    if (!(grid[row][col] & 2)) dfs(row - 1, col); // North
    if (!(grid[row][col] & 4)) dfs(row, col + 1); // East
    if (!(grid[row][col] & 8)) dfs(row + 1, col); // South
    size += visited[row][col - 1] + visited[row - 1][col] + visited[row][col + 1] + visited[row + 1][col];
    if (size > max_room_size) {
        max_room_size = size;
        best_wall_row = row;
        best_wall_col = col;
        best_wall_direction = 'W';
    }
}

void find_best_wall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!(grid[i][j] & 1)) { // Check west wall
                int new_size = 1;
                if (i >= 0 && i < n && j - 1 >= 0 && j - 1 < m) new_size += visited[i][j - 1];
                if (i >= 0 && i < n && j + 1 >= 0 && j + 1 < m) new_size += visited[i][j + 1];
                if (i + 1 >= 0 && i + 1 < n && j >= 0 && j < m) new_size += visited[i + 1][j];
                if (new_size > max_room_size) {
                    max_room_size = new_size;
                    best_wall_row = i;
                    best_wall_col = j;
                    best_wall_direction = 'W';
                }
            }
            if (!(grid[i][j] & 2)) { // Check north wall
                int new_size = 1;
                if (i - 1 >= 0 && i - 1 < n && j >= 0 && j < m) new_size += visited[i - 1][j];
                if (i + 1 >= 0 && i + 1 < n && j >= 0 && j < m) new_size += visited[i + 1][j];
                if (i >= 0 && i < n && j - 1 >= 0 && j - 1 < m) new_size += visited[i][j - 1];
                if (i >= 0 && i < n && j + 1 >= 0 && j + 1 < m) new_size += visited[i][j + 1];
                if (new_size > max_room_size) {
                    max_room_size = new_size;
                    best_wall_row = i;
                    best_wall_col = j;
                    best_wall_direction = 'N';
                }
            }
            if (!(grid[i][j] & 4)) { // Check east wall
                int new_size = 1;
                if (i >= 0 && i < n && j + 1 >= 0 && j + 1 < m) new_size += visited[i][j + 1];
                if (i >= 0 && i < n && j - 1 >= 0 && j - 1 < m) new_size += visited[i][j - 1];
                if (i + 1 >= 0 && i + 1 < n && j >= 0 && j < m) new_size += visited[i + 1][j];
                if (i - 1 >= 0 && i - 1 < n && j >= 0 && j < m) new_size += visited[i - 1][j];
                if (new_size > max_room_size) {
                    max_room_size = new_size;
                    best_wall_row = i;
                    best_wall_col = j;
                    best_wall_direction = 'E';
                }
            }
            if (!(grid[i][j] & 8)) { // Check south wall
                int new_size = 1;
                if (i + 1 >= 0 && i + 1 < n && j >= 0 && j < m) new_size += visited[i + 1][j];
                if (i - 1 >= 0 && i - 1 < n && j >= 0 && j < m) new_size += visited[i - 1][j];
                if (i >= 0 && i < n && j + 1 >= 0 && j + 1 < m) new_size += visited[i][j + 1];
                if (i >= 0 && i < n && j - 1 >= 0 && j - 1 < m) new_size += visited[i][j - 1];
                if (new_size > max_room_size) {
                    max_room_size = new_size;
                    best_wall_row = i;
                    best_wall_col = j;
                    best_wall_direction = 'S';
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                rooms++;
                max_room_size = 0;
                dfs(i, j);
            }
        }
    }

    printf("%d\n", rooms);
    printf("%d\n", max_room_size);

    find_best_wall();
    printf("%d %d %c\n", best_wall_row + 1, best_wall_col + 1, best_wall_direction);

    return 0;
}