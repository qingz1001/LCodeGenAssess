#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXR 100005
#define MAXC 100005

typedef struct {
    int a, b, c, d;
} Piece;

int main() {
    int r, c, n, m;
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    Piece pieces[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &pieces[i].a, &pieces[i].b, &pieces[i].c, &pieces[i].d);
    }
    scanf("%d", &m);

    int moves[MAXR][MAXC][2];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < 2; ++k) {
                moves[i][j][k] = -1;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        int x, y;
        char dir1[3], dir2[3];
        scanf("%d %d %s %s", &x, &y, dir1, dir2);
        --x, --y;
        if (dir1[0] == 'U' && dir2[0] == 'D') {
            moves[x][y][0] = i;
        } else if (dir1[0] == 'D' && dir2[0] == 'U') {
            moves[x][y][0] = i;
        } else if (dir1[0] == 'L' && dir2[0] == 'R') {
            moves[x][y][1] = i;
        } else if (dir1[0] == 'R' && dir2[0] == 'L') {
            moves[x][y][1] = i;
        }
    }

    int removed = 0;
    int max_removed = 0;
    for (int i = 0; i < n; ++i) {
        int a = pieces[i].a - 1, b = pieces[i].b - 1, c = pieces[i].c - 1, d = pieces[i].d - 1;
        if (moves[a][b][0] != -1 && moves[c][d][0] != -1 && moves[a][b][0] == moves[c][d][0]) {
            ++removed;
            max_removed += 2;
        }
        if (moves[a][b][1] != -1 && moves[c][d][1] != -1 && moves[a][b][1] == moves[c][d][1]) {
            ++removed;
            max_removed += 2;
        }
    }

    printf("%d %d\n", removed, max_removed);

    return 0;
}