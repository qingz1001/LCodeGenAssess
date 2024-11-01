#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

typedef struct {
    int x1, y1, x2, y2;
} Segment;

typedef struct {
    int id, direction;
} Move;

Segment segments[MAXN];
Move moves[MAXN];
int n;

int is_valid_move(int idx, int direction) {
    int x1 = segments[idx].x1, y1 = segments[idx].y1;
    int x2 = segments[idx].x2, y2 = segments[idx].y2;

    for (int i = 0; i < n; i++) {
        if (i == idx) continue;
        int sx1 = segments[i].x1, sy1 = segments[i].y1;
        int sx2 = segments[i].x2, sy2 = segments[i].y2;

        if (direction == 0) { // Left
            if (y1 == sy1 && y2 == sy2 && ((x1 < sx1 && x2 < sx2) || (x1 > sx1 && x2 > sx2))) {
                return 0;
            }
        } else if (direction == 1) { // Up
            if (x1 == sx1 && x2 == sx2 && ((y1 < sy1 && y2 < sy2) || (y1 > sy1 && y2 > sy2))) {
                return 0;
            }
        } else if (direction == 2) { // Right
            if (y1 == sy1 && y2 == sy2 && ((x1 < sx1 && x2 < sx2) || (x1 > sx1 && x2 > sx2))) {
                return 0;
            }
        } else if (direction == 3) { // Down
            if (x1 == sx1 && x2 == sx2 && ((y1 < sy1 && y2 < sy2) || (y1 > sy1 && y2 > sy2))) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &moves[i].id, &moves[i].direction);
        moves[i].id--; // Convert to 0-based index
    }

    int invalid_move_round = -1;
    for (int i = 0; i < n; i++) {
        if (!is_valid_move(moves[i].id, moves[i].direction)) {
            invalid_move_round = i + 1;
            break;
        }
    }

    printf("%d\n", invalid_move_round);

    // Generate a valid sequence
    for (int i = 0; i < n; i++) {
        int valid_direction = -1;
        for (int d = 0; d < 4; d++) {
            if (is_valid_move(moves[i].id, d)) {
                valid_direction = d;
                break;
            }
        }
        printf("%d %d\n", moves[i].id + 1, valid_direction);
    }

    return 0;
}