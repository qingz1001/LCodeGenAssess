#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 35

int n, m, q;
int board[MAXN][MAXN];
int fixed[MAXN][MAXN];

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

struct State {
    int blankx, blanky, sx, sy, tx, ty;
} state;

void read_board() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1) {
                fixed[i][j] = 1;
            }
        }
    }
}

void read_query(int case_num) {
    scanf("%d %d %d %d %d %d", &state.blankx, &state.blanky, &state.sx, &state.sy, &state.tx, &state.ty);
    printf("Case %d: ", case_num);
}

int is_valid_move(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && !fixed[x][y];
}

int bfs(int sx, int sy, int ex, int ey) {
    if (sx == ex && sy == ey) return 0;
    int vis[MAXN][MAXN] = {0};
    vis[sx][sy] = 1;
    int step = 0;
    while (1) {
        step++;
        int new_vis[MAXN][MAXN] = {0};
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!vis[i][j]) continue;
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (is_valid_move(nx, ny)) {
                        if (nx == ex && ny == ey) return step;
                        if (!new_vis[nx][ny]) {
                            new_vis[nx][ny] = 1;
                            board[nx][ny] = board[i][j];
                            board[i][j] = 1;
                            vis[nx][ny] = 1;
                            board[i][j] = 0;
                        }
                    }
                }
            }
        }
        memcpy(vis, new_vis, sizeof(new_vis));
    }
    return -1;
}

int solve_case() {
    int result = bfs(state.sx, state.sy, state.tx, state.ty);
    return result;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    read_board();
    for (int i = 1; i <= q; i++) {
        read_query(i);
        int result = solve_case();
        printf("%d\n", result);
    }
    return 0;
}