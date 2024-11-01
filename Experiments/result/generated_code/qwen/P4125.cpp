#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int x1, y1, x2, y2;
} LineSegment;

int isLegalMove(LineSegment segments[], int n, int moveIndex, int direction) {
    int p = moveIndex - 1;
    int dx = (direction == 0 ? -1 : (direction == 2 ? 1 : 0));
    int dy = (direction == 1 ? 1 : (direction == 3 ? -1 : 0));

    for (int i = 0; i < n; i++) {
        if (i != p) {
            int x1 = segments[i].x1, y1 = segments[i].y1, x2 = segments[i].x2, y2 = segments[i].y2;
            if ((dx > 0 && x1 <= segments[p].x1 && x2 >= segments[p].x1 &&
                 (y1 <= segments[p].y1 && y2 >= segments[p].y1)) ||
                (dx < 0 && x1 >= segments[p].x1 && x2 <= segments[p].x1 &&
                 (y1 <= segments[p].y1 && y2 >= segments[p].y1)) ||
                (dy > 0 && y1 <= segments[p].y1 && y2 >= segments[p].y1 &&
                 (x1 <= segments[p].x1 && x2 >= segments[p].x1)) ||
                (dy < 0 && y1 >= segments[p].y1 && y2 <= segments[p].y1)) {
                return 0;
            }
        }
    }
    return 1;
}

void performMove(LineSegment segments[], int n, int moveIndex, int direction) {
    int p = moveIndex - 1;
    int dx = (direction == 0 ? -1 : (direction == 2 ? 1 : 0));
    int dy = (direction == 1 ? 1 : (direction == 3 ? -1 : 0));

    if (direction == 0 || direction == 2) {
        segments[p].x1 += dx;
        segments[p].x2 += dx;
    } else {
        segments[p].y1 += dy;
        segments[p].y2 += dy;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    LineSegment segments[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    int moves[MAX_N][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &moves[i][0], &moves[i][1]);
    }

    int illegalMoveRound = -1;
    for (int i = 0; i < n; i++) {
        if (!isLegalMove(segments, n, moves[i][0], moves[i][1])) {
            illegalMoveRound = i + 1;
            break;
        }
        performMove(segments, n, moves[i][0], moves[i][1]);
    }

    printf("%d\n", illegalMoveRound);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", moves[i][0], moves[i][1]);
    }

    return 0;
}