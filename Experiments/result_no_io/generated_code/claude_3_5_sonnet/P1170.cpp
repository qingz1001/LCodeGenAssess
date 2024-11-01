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
    
    return gcd(dx, dy) == 1;
}

int main() {
    int n, ax, ay, bx, by;
    scanf("%d", &n);
    
    while (n--) {
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