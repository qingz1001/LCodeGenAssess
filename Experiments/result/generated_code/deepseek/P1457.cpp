#include <stdio.h>
#include <stdlib.h>

#define MAXN 50
#define MAXM 50

int n, m;
int castle[MAXN][MAXM];
int visited[MAXN][MAXM];
int room_size[MAXN * MAXM];
int room_count = 0;
int max_room_size = 0;
int max_combined_room_size = 0;
int best_wall_row, best_wall_col;
char best_wall_dir;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
char dir[] = {'W', 'N', 'E', 'S'};

int dfs(int x, int y) {
    if (visited[x][y]) return 0;
    visited[x][y] = room_count;
    int size = 1;
    for (int i = 0; i < 4; i++) {
        if (!(castle[x][y] & (1 << i))) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                size += dfs(nx, ny);
            }
        }
    }
    return size;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &castle[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                room_count++;
                int size = dfs(i, j);
                room_size[room_count] = size;
                if (size > max_room_size) {
                    max_room_size = size;
                }
            }
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = n - 1; i >= 0; i--) {
            if (i > 0 && (castle[i][j] & 2) && visited[i][j] != visited[i - 1][j]) {
                int combined_size = room_size[visited[i][j]] + room_size[visited[i - 1][j]];
                if (combined_size > max_combined_room_size) {
                    max_combined_room_size = combined_size;
                    best_wall_row = i + 1;
                    best_wall_col = j + 1;
                    best_wall_dir = 'N';
                }
            }
            if (j < m - 1 && (castle[i][j] & 4) && visited[i][j] != visited[i][j + 1]) {
                int combined_size = room_size[visited[i][j]] + room_size[visited[i][j + 1]];
                if (combined_size > max_combined_room_size) {
                    max_combined_room_size = combined_size;
                    best_wall_row = i + 1;
                    best_wall_col = j + 1;
                    best_wall_dir = 'E';
                }
            }
        }
    }

    printf("%d\n", room_count);
    printf("%d\n", max_room_size);
    printf("%d\n", max_combined_room_size);
    printf("%d %d %c\n", best_wall_row, best_wall_col, best_wall_dir);

    return 0;
}