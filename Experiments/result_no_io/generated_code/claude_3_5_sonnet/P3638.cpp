#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 9
#define MAX_W 500
#define MAX_H 500

typedef struct {
    int x, y;
} Point;

char map[MAX_H][MAX_W + 1];
int n, w, h;
Point robots[MAX_N + 1];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

int min(int a, int b) {
    return a < b ? a : b;
}

bool can_merge(int a, int b) {
    return (a == b - 1) || (b == a - 1);
}

void move_robot(int id, int dir) {
    int x = robots[id].x, y = robots[id].y;
    while (1) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx < 0 || nx >= w || ny < 0 || ny >= h || map[ny][nx] == 'x') break;
        if (map[ny][nx] == 'A') dir = (dir + 3) % 4;
        if (map[ny][nx] == 'C') dir = (dir + 1) % 4;
        x = nx;
        y = ny;
    }
    robots[id].x = x;
    robots[id].y = y;
}

int dfs(int mask, int moves) {
    if (__builtin_popcount(mask) == 1) return moves;
    
    int result = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (!(mask & (1 << (i - 1)))) continue;
        for (int dir = 0; dir < 4; dir++) {
            Point original = robots[i];
            move_robot(i, dir);
            int new_mask = mask;
            for (int j = 1; j <= n; j++) {
                if (i != j && (mask & (1 << (j - 1))) && 
                    robots[i].x == robots[j].x && robots[i].y == robots[j].y && 
                    can_merge(i, j)) {
                    new_mask &= ~(1 << (j - 1));
                }
            }
            if (new_mask != mask) {
                int sub_result = dfs(new_mask, moves + 1);
                result = min(result, sub_result);
            }
            robots[i] = original;
        }
    }
    return result;
}

int main() {
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < w; j++) {
            if (map[i][j] >= '1' && map[i][j] <= '9') {
                int id = map[i][j] - '0';
                robots[id] = (Point){j, i};
            }
        }
    }

    int result = dfs((1 << n) - 1, 0);
    printf("%d\n", result == INT_MAX ? -1 : result);
    return 0;
}