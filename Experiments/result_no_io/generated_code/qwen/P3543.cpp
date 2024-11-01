#include <stdio.h>
#include <stdlib.h>

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

    int total = 0;
    for (int i = 0; i < n; i++) {
        total += abs(heights[i]);
    }

    int g = gcd(a, b);
    if (total % g != 0) {
        printf("-1\n");
        return 0;
    }

    int ops = 0;
    for (int i = 0; i < n; i++) {
        if (heights[i] != 0) {
            int target = (abs(heights[i]) / g) * (heights[i] > 0 ? 1 : -1);
            int steps = abs(target) / a + (abs(target) % a != 0);
            ops += steps;
        }
    }

    printf("%d\n", ops);

    return 0;
}