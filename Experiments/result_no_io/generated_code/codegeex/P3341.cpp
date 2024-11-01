#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point p1, p2;
} Color;

typedef struct {
    int x, y;
    char dir1, dir2;
} Move;

int main() {
    int r, c, n, m;
    scanf("%d%d%d%d", &r, &c, &n, &m);

    Color colors[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &colors[i].p1.x, &colors[i].p1.y, &colors[i].p2.x, &colors[i].p2.y);
    }

    Move moves[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %c %d %c", &moves[i].x, &moves[i].dir1, &moves[i].y, &moves[i].dir2);
    }

    // Process each move and count the number of removed pieces
    int totalRemoved = 0;
    int maxRemoved = 0;

    for (int i = 0; i < m; i++) {
        int removed = 0;
        for (int j = 0; j < n; j++) {
            if ((colors[j].p1.x == moves[i].x && colors[j].p1.y == moves[i].y) ||
                (colors[j].p2.x == moves[i].x && colors[j].p2.y == moves[i].y)) {
                // Check if the move is valid for this color
                if ((colors[j].p1.x == moves[i].x && (moves[i].dir1 == 'U' || moves[i].dir1 == 'D')) ||
                    (colors[j].p1.y == moves[i].y && (moves[i].dir1 == 'L' || moves[i].dir1 == 'R'))) {
                    removed++;
                }
                if ((colors[j].p2.x == moves[i].x && (moves[i].dir2 == 'U' || moves[i].dir2 == 'D')) ||
                    (colors[j].p2.y == moves[i].y && (moves[i].dir2 == 'L' || moves[i].dir2 == 'R'))) {
                    removed++;
                }
            }
        }
        totalRemoved += removed;
        if (removed > maxRemoved) {
            maxRemoved = removed;
        }
    }

    printf("%d %d\n", totalRemoved, maxRemoved);

    return 0;
}