#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int positions[15000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    int min_length = 0;
    for (int i = 0; i < m - 1; i++) {
        min_length += positions[i + 1] - positions[i];
    }

    printf("%d\n", min_length);
    return 0;
}