#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int xp, yp, xs, ys;
    scanf("%d %d %d %d", &xp, &yp, &xs, &ys);
    
    int dx = abs(xs - xp);
    int dy = abs(ys - yp);
    
    if (dx > dy) {
        int temp = dx;
        dx = dy;
        dy = temp;
    }
    
    int steps = dy + (dx - dy) / 3;
    
    printf("%d\n", steps);
    
    return 0;
}