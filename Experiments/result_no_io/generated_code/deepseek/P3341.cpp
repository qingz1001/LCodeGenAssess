#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

typedef struct {
    int x1, y1, x2, y2;
} Pair;

typedef struct {
    int x, y;
    char dir1, dir2;
} Move;

int r, c, n, m;
Pair pairs[MAX_SIZE];
Move moves[MAX_SIZE];
int board[MAX_SIZE][MAX_SIZE];

int dx[4] = {-1, 1, 0, 0}; // U, D, L, R
int dy[4] = {0, 0, -1, 1};
char dir_map[4] = {'U', 'D', 'L', 'R'};

int is_valid_move(int x, int y, char dir1, char dir2) {
    int dir1_idx = -1, dir2_idx = -1;
    for (int i = 0; i < 4; i++) {
        if (dir_map[i] == dir1) dir1_idx = i;
        if (dir_map[i] == dir2) dir2_idx = i;
    }
    if (dir1_idx == -1 || dir2_idx == -1) return 0;

    int x1 = x, y1 = y, x2 = x, y2 = y;
    while (x1 >= 0 && x1 < r && y1 >= 0 && y1 < c) {
        x1 += dx[dir1_idx];
        y1 += dy[dir1_idx];
        if (board[x1][y1] != 0) break;
    }
    while (x2 >= 0 && x2 < r && y2 >= 0 && y2 < c) {
        x2 += dx[dir2_idx];
        y2 += dy[dir2_idx];
        if (board[x2][y2] != 0) break;
    }

    if (x1 < 0 || x1 >= r || y1 < 0 || y1 >= c || x2 < 0 || x2 >= r || y2 < 0 || y2 >= c) return 0;
    if (board[x1][y1] == board[x2][y2] && board[x1][y1] != 0) return board[x1][y1];
    return 0;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &pairs[i].x1, &pairs[i].y1, &pairs[i].x2, &pairs[i].y2);
        board[pairs[i].x1][pairs[i].y1] = i + 1;
        board[pairs[i].x2][pairs[i].y2] = i + 1;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %c %c", &moves[i].x, &moves[i].y, &moves[i].dir1, &moves[i].dir2);
    }

    int removed_count = 0;
    int max_possible_removed = 0;

    for (int i = 0; i < m; i++) {
        int color = is_valid_move(moves[i].x, moves[i].y, moves[i].dir1, moves[i].dir2);
        if (color) {
            removed_count++;
            board[pairs[color - 1].x1][pairs[color - 1].y1] = 0;
            board[pairs[color - 1].x2][pairs[color - 1].y2] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (board[pairs[i].x1][pairs[i].y1] != 0) max_possible_removed++;
    }

    printf("%d %d\n", removed_count, max_possible_removed);

    return 0;
}