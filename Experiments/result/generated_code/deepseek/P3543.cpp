#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005

int n, a, b;
int heights[MAXN];

int gcd(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int g = gcd(a, b);
    for (int i = 0; i < n; i++) {
        if (heights[i] % g != 0) {
            printf("-1\n");
            return 0;
        }
    }

    int total_operations = 0;
    for (int i = 0; i < n; i++) {
        int h = heights[i] / g;
        int x = abs(h % a);
        int y = abs(h % b);
        total_operations += x + y;
    }

    printf("%d\n", total_operations);
    return 0;
}