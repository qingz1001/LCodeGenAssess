#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int solve(int dx, int dy) {
    dx = abs(dx);
    dy = abs(dy);
    if (dx < dy) {
        int temp = dx;
        dx = dy;
        dy = temp;
    }
    
    if (dx == 1 && dy == 0) return 3;
    if (dx == 2 && dy == 2) return 4;
    
    int delta = dx - dy;
    if (dy > delta) return delta - 2 * ((delta - dy) / 3);
    
    return delta - 2 * ((delta - dy) / 4);
}

int main() {
    int xp, yp, xs, ys;
    scanf("%d %d %d %d", &xp, &yp, &xs, &ys);
    
    int dx = abs(xs - xp);
    int dy = abs(ys - yp);
    
    int result = solve(dx, dy);
    printf("%d\n", result);
    
    return 0;
}