#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100000
#define INF 1000000000

typedef struct {
    int x, y;
    char orientation;
} Mirror;

Mirror mirrors[MAXN];
int N, Bx, By;

bool is_valid_position(int x, int y) {
    for (int i = 0; i < N; i++) {
        if (mirrors[i].x == x && mirrors[i].y == y) {
            return false;
        }
    }
    return true;
}

int count_valid_positions() {
    int count = 0;
    int dx = Bx, dy = By;

    while (dx != 0 || dy != 0) {
        if (dx % 2 == dy % 2) {
            int x = dx / 2;
            int y = dy / 2;
            if (is_valid_position(x, y)) {
                count++;
            }
        }
        dx -= dy;
        dy = -dx;
    }

    return count;
}

int main() {
    scanf("%d %d %d", &N, &Bx, &By);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].orientation);
    }

    int result = count_valid_positions();
    printf("%d\n", result);

    return 0;
}