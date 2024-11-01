#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000000

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);

    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int height[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &height[i]);
    }

    int diff = 0;
    for (int i = 1; i < n; i++) {
        diff += abs(height[i] - height[i - 1]);
    }

    if (diff % a != 0) {
        printf("-1\n");
        return 0;
    }

    int operations = diff / a;
    int excess = 0;

    for (int i = 0; i < n; i++) {
        int current_height = height[i];
        if (current_height % b != 0) {
            int needed = b - (current_height % b);
            if (needed > excess) {
                operations += (needed - excess) / a + ((needed - excess) % a != 0);
                excess = 0;
            } else {
                excess -= needed;
            }
        }
        excess += current_height / b;
    }

    printf("%d\n", operations);
    return 0;
}