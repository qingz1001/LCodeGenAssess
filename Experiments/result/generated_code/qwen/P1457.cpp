#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXM 55

int n, m;
int grid[MAXN][MAXM];
int visited[MAXN][MAXM];
int rooms[MAXM * MAXN];

void dfs(int x, int y, int room_id) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y]) return;
    visited[x][y] = 1;
    rooms[room_id]++;
    if (!(grid[x][y] & 1)) dfs(x, y - 1, room_id); // West
    if (!(grid[x][y] & 2)) dfs(x - 1, y, room_id); // North
    if (!(grid[x][y] & 4)) dfs(x, y + 1, room_id); // East
    if (!(grid[x][y] & 8)) dfs(x + 1, y, room_id); // South
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int room_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                dfs(i, j, room_count++);
            }
        }
    }

    int max_room_size = 0;
    for (int i = 0; i < room_count; i++) {
        if (rooms[i] > max_room_size) {
            max_room_size = rooms[i];
        }
    }

    int best_wall_x, best_wall_y, best_wall_dir;
    int best_new_room_size = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!(grid[i][j] & 1)) { // West wall
                int new_room_size = rooms[find_room_id(i, j)] + rooms[find_room_id(i, j - 1)];
                if (new_room_size > best_new_room_size) {
                    best_new_room_size = new_room_size;
                    best_wall_x = i;
                    best_wall_y = j;
                    best_wall_dir = 'W';
                }
            }
            if (!(grid[i][j] & 2)) { // North wall
                int new_room_size = rooms[find_room_id(i, j)] + rooms[find_room_id(i - 1, j)];
                if (new_room_size > best_new_room_size) {
                    best_new_room_size = new_room_size;
                    best_wall_x = i;
                    best_wall_y = j;
                    best_wall_dir = 'N';
                }
            }
            if (!(grid[i][j] & 4)) { // East wall
                int new_room_size = rooms[find_room_id(i, j)] + rooms[find_room_id(i, j + 1)];
                if (new_room_size > best_new_room_size) {
                    best_new_room_size = new_room_size;
                    best_wall_x = i;
                    best_wall_y = j;
                    best_wall_dir = 'E';
                }
            }
            if (!(grid[i][j] & 8)) { // South wall
                int new_room_size = rooms[find_room_id(i, j)] + rooms[find_room_id(i + 1, j)];
                if (new_room_size > best_new_room_size) {
                    best_new_room_size = new_room_size;
                    best_wall_x = i;
                    best_wall_y = j;
                    best_wall_dir = 'S';
                }
            }
        }
    }

    printf("%d\n%d\n%d\n%d %d %c\n", room_count, max_room_size, best_new_room_size, best_wall_x + 1, best_wall_y + 1, best_wall_dir);

    return 0;
}