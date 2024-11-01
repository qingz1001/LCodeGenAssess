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
        int a1 = segments[i].x1, b1 = segments[i].y1;
        int a2 = segments[i].x2, b2 = segments[i].y2;

        // Check if the move is blocked by another segment
        if (direction == 0) { // Left
            if ((a1 <= x1 && a2 <= x1) || (b1 == y1 || b2 == y1)) continue;
            if ((a1 > x1 && a2 > x1) || (b1 < y1 && b2 < y1) || (b1 > y1 && b2 > y1)) continue;
            return 0;
        } else if (direction == 1) { // Up
            if ((b1 >= y1 && b2 >= y1) || (a1 == x1 || a2 == x1)) continue;
            if ((b1 < y1 && b2 < y1) || (a1 < x1 && a2 < x1) || (a1 > x1 && a2 > x1)) continue;
            return 0;
        } else if (direction == 2) { // Right
            if ((a1 >= x1 && a2 >= x1) || (b1 == y1 || b2 == y1)) continue;
            if ((a1 < x1 && a2 < x1) || (b1 < y1 && b2 < y1) || (b1 > y1 && b2 > y1)) continue;
            return 0;
        } else if (direction == 3) { // Down
            if ((b1 <= y1 && b2 <= y1) || (a1 == x1 || a2 == x1)) continue;
            if ((b1 > y1 && b2 > y1) || (a1 < x1 && a2 < x1) || (a1 > x1 && a2 > x1)) continue;
            return 0;
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

    // Generate a valid sequence of moves
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", moves[i].id + 1, moves[i].direction);
    }

    return 0;
}