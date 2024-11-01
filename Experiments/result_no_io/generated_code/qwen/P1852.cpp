#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int a, b, c, x, y, z;
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d %d", &x, &y, &z);

    // Sort the positions to simplify calculations
    if (a > b) { int t = a; a = b; b = t; }
    if (a > c) { int t = a; a = c; c = t; }
    if (b > c) { int t = b; b = c; c = t; }

    if (x > y) { int t = x; x = y; y = t; }
    if (x > z) { int t = x; x = z; z = t; }
    if (y > z) { int t = y; y = z; z = t; }

    if ((a == x && b == y && c == z) ||
        (a == x && b == z && c == y) ||
        (a == y && b == x && c == z) ||
        (a == y && b == z && c == x) ||
        (a == z && b == x && c == y) ||
        (a == z && b == y && c == x)) {
        printf("YES\n");
        printf("%d\n", abs(a - x) + abs(b - y) + abs(c - z));
    } else {
        printf("NO\n");
    }

    return 0;
}