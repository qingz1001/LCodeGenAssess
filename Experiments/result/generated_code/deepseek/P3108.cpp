#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100000

typedef struct {
    int x, y;
    char orientation;
} Mirror;

Mirror mirrors[MAXN];
int N, Bx, By;

bool can_reach_barn(int x, int y, char orientation) {
    int dx = (orientation == '\\') ? 1 : -1;
    int dy = (orientation == '\\') ? 1 : -1;

    int cx = 0, cy = 0;
    int dir = 0; // 0: north, 1: east, 2: south, 3: west

    while (true) {
        if (dir == 0) { // moving north
            cy++;
            if (cy > 1000000000) break;
            for (int i = 0; i < N; i++) {
                if (mirrors[i].y == cy && mirrors[i].x == cx) {
                    if (mirrors[i].orientation == '\\') dir = 1;
                    else dir = 3;
                    break;
                }
            }
        } else if (dir == 1) { // moving east
            cx++;
            if (cx > 1000000000) break;
            for (int i = 0; i < N; i++) {
                if (mirrors[i].x == cx && mirrors[i].y == cy) {
                    if (mirrors[i].orientation == '\\') dir = 0;
                    else dir = 2;
                    break;
                }
            }
        } else if (dir == 2) { // moving south
            cy--;
            if (cy < -1000000000) break;
            for (int i = 0; i < N; i++) {
                if (mirrors[i].y == cy && mirrors[i].x == cx) {
                    if (mirrors[i].orientation == '\\') dir = 3;
                    else dir = 1;
                    break;
                }
            }
        } else if (dir == 3) { // moving west
            cx--;
            if (cx < -1000000000) break;
            for (int i = 0; i < N; i++) {
                if (mirrors[i].x == cx && mirrors[i].y == cy) {
                    if (mirrors[i].orientation == '\\') dir = 2;
                    else dir = 0;
                    break;
                }
            }
        }

        if (cx == x && cy == y) {
            if (orientation == '\\') dir = (dir + 1) % 4;
            else dir = (dir + 3) % 4;
        }

        if (cx == Bx && cy == By) return true;
    }

    return false;
}

int main() {
    scanf("%d %d %d", &N, &Bx, &By);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].orientation);
    }

    int count = 0;
    for (int y = 1; y <= By; y++) {
        if (can_reach_barn(0, y, '\\')) count++;
        if (can_reach_barn(0, y, '/')) count++;
    }

    printf("%d\n", count);
    return 0;
}