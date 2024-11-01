#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int max = 0, min = 1000000000;

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        // Update max and min
        if (a > max) max = a;
        if (a < min) min = a;
    }

    // Perform m operations to maximize the range
    for (int i = 0; i < m; i++) {
        // Increase the maximum value
        max = max * 2;
        // Decrease the minimum value
        if (min % 2 == 0) min /= 2;
    }

    // Calculate the final range
    int result = max - min;

    printf("%d\n", result);

    return 0;
}