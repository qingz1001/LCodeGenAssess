#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int is_safe(int ax, int ay, int bx, int by) {
    int dx = abs(bx - ax);
    int dy = abs(by - ay);
    
    if (dx == 0 && dy == 0) return 0;
    if (dx == 0 || dy == 0) return 0;
    
    int g = gcd(dx, dy);
    dx /= g;
    dy /= g;
    
    int x = ax, y = ay;
    while (x != bx || y != by) {
        x += (bx > ax) ? dx : -dx;
        y += (by > ay) ? dy : -dy;
        if (x == bx && y == by) return 0;
        if (x > bx || y > by || x < ax || y < ay) break;
    }
    
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    while (n--) {
        int ax, ay, bx, by;
        scanf("%d %d", &ax, &ay);
        scanf("%d %d", &bx, &by);
        
        if (is_safe(ax, ay, bx, by)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    
    return 0;
}