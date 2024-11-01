#include <stdio.h>

int main() {
    int n, dist;
    scanf("%d %d", &n, &dist);

    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    int max_deletions = 0;
    for (int i = 1; i < n - 1; i++) {
        if (positions[i + 1] - positions[i - 1] <= dist) {
            max_deletions++;
        }
    }

    printf("%d\n", max_deletions);
    return 0;
}