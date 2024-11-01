#include <stdio.h>
#include <stdlib.h>

#define MAXN 50
#define MAXM 50

int n, m;
int map[MAXN + 1][MAXM + 1];
int room_size[MAXN * MAXM + 1];
int visited[MAXN * MAXM + 1];
int max_room_size = 0;
int room_count = 0;
int best_wall_size = 0;
int best_wall_x = 0, best_wall_y = 0;
char best_wall_direction;

void dfs(int x, int y, int room_id) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int dir[] = {'E', 'W', 'S', 'N'};
    visited[x * m + y] = room_id;
    room_size[room_id]++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !(map[x][y] & (1 << i)) && !visited[nx * m + ny]) {
            dfs(nx, ny, room_id);
        }
    }
}

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!visited[i * m + j]) {
                room_count++;
                dfs(i, j, room_count);
                if (room_size[room_count] > max_room_size) {
                    max_room_size = room_size[room_count];
                }
            }
        }
    }

    printf("%d\n", room_count);
    printf("%d\n", max_room_size);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + (k == 2 ? 1 : (k == 3 ? -1 : 0));
                int ny = j + (k == 1 ? 1 : (k == 0 ? -1 : 0));
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !(map[i][j] & (1 << k))) {
                    int new_room_size = room_size[visited[i * m + j]] + room_size[visited[nx * m + ny]];
                    if (new_room_size > best_wall_size || (new_room_size == best_wall_size && ny > best_wall_y) || (new_room_size == best_wall_size && ny == best_wall_y && j < best_wall_x)) {
                        best_wall_size = new_room_size;
                        best_wall_x = j;
                        best_wall_y = i;
                        best_wall_direction = dir[k];
                    }
                }
            }
        }
    }

    printf("%d\n", best_wall_size);
    printf("%d %d %c\n", best_wall_y, best_wall_x, best_wall_direction);

    return 0;
}