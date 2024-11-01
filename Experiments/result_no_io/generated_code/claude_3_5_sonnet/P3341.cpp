#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100005
#define MAX_RC 100005

typedef struct {
    int x, y;
} Point;

Point pieces[MAX_N * 2];
int board[MAX_RC][MAX_RC];
int r, c, n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char dir[] = "UDLR";

bool is_valid(int x, int y) {
    return x >= 1 && x <= r && y >= 1 && y <= c;
}

int get_dir(char ch) {
    for (int i = 0; i < 4; i++) {
        if (dir[i] == ch) return i;
    }
    return -1;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);

    memset(board, 0, sizeof(board));

    for (int i = 1; i <= n; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        board[a][b] = board[c][d] = i;
        pieces[i * 2 - 1] = (Point){a, b};
        pieces[i * 2] = (Point){c, d};
    }

    scanf("%d", &m);
    int count = 0;

    for (int i = 0; i < m; i++) {
        int x, y;
        char d1, d2;
        scanf("%d %d %c %c", &x, &y, &d1, &d2);

        int dir1 = get_dir(d1);
        int dir2 = get_dir(d2);

        int x1 = x + dx[dir1], y1 = y + dy[dir1];
        int x2 = x + dx[dir2], y2 = y + dy[dir2];

        while (is_valid(x1, y1) && board[x1][y1] == 0) {
            x1 += dx[dir1];
            y1 += dy[dir1];
        }

        while (is_valid(x2, y2) && board[x2][y2] == 0) {
            x2 += dx[dir2];
            y2 += dy[dir2];
        }

        if (is_valid(x1, y1) && is_valid(x2, y2) && board[x1][y1] == board[x2][y2] && board[x1][y1] != 0) {
            board[x1][y1] = board[x2][y2] = 0;
            count += 2;
        }
    }

    int max_count = 0;
    for (int i = 1; i <= n; i++) {
        Point p1 = pieces[i * 2 - 1];
        Point p2 = pieces[i * 2];
        if (board[p1.x][p1.y] != 0) max_count += 2;
    }

    printf("%d %d\n", count, max_count);

    return 0;
}