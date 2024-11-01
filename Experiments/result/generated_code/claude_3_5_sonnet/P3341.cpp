#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100005
#define MAX_RC 100005

int r, c, n, m;
int board[MAX_RC][MAX_RC];
int color_count[MAX_N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_valid(int x, int y) {
    return x >= 1 && x <= r && y >= 1 && y <= c;
}

int dir_to_index(char dir) {
    if (dir == 'U') return 0;
    if (dir == 'D') return 1;
    if (dir == 'L') return 2;
    return 3;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);

    memset(board, 0, sizeof(board));
    memset(color_count, 0, sizeof(color_count));

    for (int i = 1; i <= n; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        board[a][b] = board[c][d] = i;
        color_count[i] = 2;
    }

    scanf("%d", &m);
    int player_removed = 0;

    for (int i = 0; i < m; i++) {
        int x, y;
        char dir1, dir2;
        scanf("%d %d %c %c", &x, &y, &dir1, &dir2);

        int d1 = dir_to_index(dir1);
        int d2 = dir_to_index(dir2);

        int x1 = x, y1 = y;
        int x2 = x, y2 = y;

        while (is_valid(x1 + dx[d1], y1 + dy[d1]) && board[x1 + dx[d1]][y1 + dy[d1]] == 0) {
            x1 += dx[d1];
            y1 += dy[d1];
        }
        x1 += dx[d1];
        y1 += dy[d1];

        while (is_valid(x2 + dx[d2], y2 + dy[d2]) && board[x2 + dx[d2]][y2 + dy[d2]] == 0) {
            x2 += dx[d2];
            y2 += dy[d2];
        }
        x2 += dx[d2];
        y2 += dy[d2];

        if (is_valid(x1, y1) && is_valid(x2, y2) && board[x1][y1] == board[x2][y2] && board[x1][y1] != 0) {
            int color = board[x1][y1];
            board[x1][y1] = board[x2][y2] = 0;
            color_count[color] -= 2;
            player_removed += 2;
        }
    }

    int max_removed = 0;
    for (int i = 1; i <= n; i++) {
        max_removed += color_count[i];
    }

    printf("%d %d\n", player_removed, max_removed);

    return 0;
}