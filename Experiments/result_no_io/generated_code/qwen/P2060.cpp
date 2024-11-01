#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int xp, yp, xs, ys;
    scanf("%d %d %d %d", &xp, &yp, &xs, &ys);

    int dx = abs(xs - xp);
    int dy = abs(ys - yp);

    int moves = min(dx, dy) + abs(dx - dy) / 2;

    printf("%d\n", moves);

    return 0;
}