#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000

int main() {
    int a, b, c;
    int x, y, z;
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d %d", &x, &y, &z);

    // Sort the positions to simplify calculations
    if (a > b) { int temp = a; a = b; b = temp; }
    if (a > c) { int temp = a; a = c; c = temp; }
    if (b > c) { int temp = b; b = c; c = temp; }

    if (x > y) { int temp = x; x = y; y = temp; }
    if (x > z) { int temp = x; x = z; z = temp; }
    if (y > z) { int temp = y; y = z; z = temp; }

    // Check if it's possible to reach the target positions
    if (a + c != x + z && a + b != x + y && b + c != y + z) {
        printf("NO\n");
        return 0;
    }

    int steps = 0;

    // Calculate the minimum number of jumps needed
    if (a + c == x + z) {
        steps += abs(b - y);
    } else if (a + b == x + y) {
        steps += abs(c - z);
    } else if (b + c == y + z) {
        steps += abs(a - x);
    }

    printf("YES\n");
    printf("%d\n", steps);

    return 0;
}