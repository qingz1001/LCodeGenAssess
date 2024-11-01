#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1000

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point start, end;
} Segment;

Segment segments[MAX_N];
int moves[MAX_N][2];
int n;

bool intersect(Segment s1, Segment s2) {
    int x1 = s1.start.x, y1 = s1.start.y;
    int x2 = s1.end.x, y2 = s1.end.y;
    int x3 = s2.start.x, y3 = s2.start.y;
    int x4 = s2.end.x, y4 = s2.end.y;

    int d1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    int d2 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
    int d3 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    int d4 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;
    return false;
}

bool canMove(int index, int direction) {
    Segment moving = segments[index];
    if (direction == 0 || direction == 2) {
        if (moving.start.x > moving.end.x) {
            Point temp = moving.start;
            moving.start = moving.end;
            moving.end = temp;
        }
        moving.start.x = moving.end.x = (direction == 0) ? -1e9 : 1e9;
    } else {
        if (moving.start.y > moving.end.y) {
            Point temp = moving.start;
            moving.start = moving.end;
            moving.end = temp;
        }
        moving.start.y = moving.end.y = (direction == 3) ? -1e9 : 1e9;
    }

    for (int i = 0; i < n; i++) {
        if (i != index && intersect(moving, segments[i]))
            return false;
    }
    return true;
}

int findFirstIllegalMove() {
    for (int i = 0; i < n; i++) {
        if (!canMove(moves[i][0] - 1, moves[i][1]))
            return i + 1;
    }
    return -1;
}

void findValidMoves() {
    bool used[MAX_N] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                for (int d = 0; d < 4; d++) {
                    if (canMove(j, d)) {
                        printf("%d %d\n", j + 1, d);
                        used[j] = true;
                        break;
                    }
                }
                if (used[j]) break;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &segments[i].start.x, &segments[i].start.y,
              &segments[i].end.x, &segments[i].end.y);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &moves[i][0], &moves[i][1]);
    }

    int firstIllegalMove = findFirstIllegalMove();
    printf("%d\n", firstIllegalMove);

    findValidMoves();

    return 0;
}