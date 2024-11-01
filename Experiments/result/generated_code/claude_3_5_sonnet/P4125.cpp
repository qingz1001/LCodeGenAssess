#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point p1, p2;
} Segment;

Segment segments[MAXN];
int moves[MAXN][2];
int n;

bool intersect(Segment s1, Segment s2) {
    int x1 = s1.p1.x, y1 = s1.p1.y, x2 = s1.p2.x, y2 = s1.p2.y;
    int x3 = s2.p1.x, y3 = s2.p1.y, x4 = s2.p2.x, y4 = s2.p2.y;
    
    int d1 = (x4-x3)*(y1-y3) - (y4-y3)*(x1-x3);
    int d2 = (x4-x3)*(y2-y3) - (y4-y3)*(x2-x3);
    int d3 = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
    int d4 = (x2-x1)*(y4-y1) - (y2-y1)*(x4-x1);
    
    return (d1*d2 < 0 && d3*d4 < 0);
}

bool canMove(int id, int dir, bool removed[]) {
    Segment s = segments[id];
    int dx = 0, dy = 0;
    
    if (dir == 0) dx = -1;
    else if (dir == 1) dy = 1;
    else if (dir == 2) dx = 1;
    else dy = -1;
    
    Segment moved = {
        {s.p1.x + dx, s.p1.y + dy},
        {s.p2.x + dx, s.p2.y + dy}
    };
    
    for (int i = 1; i <= n; i++) {
        if (i != id && !removed[i] && intersect(moved, segments[i])) {
            return false;
        }
    }
    return true;
}

int findFirstIllegalMove() {
    bool removed[MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        int id = moves[i][0], dir = moves[i][1];
        if (!canMove(id, dir, removed)) {
            return i;
        }
        removed[id] = true;
    }
    return -1;
}

void findValidMoves() {
    bool removed[MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!removed[j]) {
                for (int dir = 0; dir < 4; dir++) {
                    if (canMove(j, dir, removed)) {
                        printf("%d %d\n", j, dir);
                        removed[j] = true;
                        goto next;
                    }
                }
            }
        }
        next:;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d %d", &segments[i].p1.x, &segments[i].p1.y, &segments[i].p2.x, &segments[i].p2.y);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &moves[i][0], &moves[i][1]);
    }
    
    int firstIllegal = findFirstIllegalMove();
    printf("%d\n", firstIllegal);
    
    findValidMoves();
    
    return 0;
}