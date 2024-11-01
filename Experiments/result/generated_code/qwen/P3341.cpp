#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int x1, y1, x2, y2;
} ChessPiece;

int main() {
    int r, c, n, m;
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    ChessPiece pieces[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &pieces[i].x1, &pieces[i].y1, &pieces[i].x2, &pieces[i].y2);
    }
    scanf("%d", &m);

    // Simulate the player's moves and count the number of pieces removed
    int removed = 0;
    for (int i = 0; i < m; ++i) {
        int x, y;
        char dir1, dir2;
        scanf("%d %d %c %c", &x, &y, &dir1, &dir2);

        // Check if the move is valid
        int found = 0;
        for (int j = 0; j < n; ++j) {
            if ((dir1 == 'U' && dir2 == 'D' && pieces[j].x1 == x && pieces[j].y1 == y - 1 && pieces[j].x2 == x && pieces[j].y2 == y + 1) ||
                (dir1 == 'D' && dir2 == 'U' && pieces[j].x1 == x && pieces[j].y1 == y + 1 && pieces[j].x2 == x && pieces[j].y2 == y - 1) ||
                (dir1 == 'L' && dir2 == 'R' && pieces[j].x1 == x - 1 && pieces[j].y1 == y && pieces[j].x2 == x + 1 && pieces[j].y2 == y) ||
                (dir1 == 'R' && dir2 == 'L' && pieces[j].x1 == x + 1 && pieces[j].y1 == y && pieces[j].x2 == x - 1 && pieces[j].y2 == y)) {
                removed += 2;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid move\n");
            return 1;
        }
    }

    // Calculate the maximum possible removals
    int max_removed = 0;
    for (int i = 0; i < n; ++i) {
        max_removed += 2;
    }

    printf("%d %d\n", removed, max_removed);

    return 0;
}