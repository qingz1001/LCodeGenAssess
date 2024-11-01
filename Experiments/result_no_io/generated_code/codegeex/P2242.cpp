#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int positions[15000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    int min_length = positions[n-1] - positions[0] + 1;
    for (int i = 1; i <= n - m; i++) {
        int current_length = positions[i + m - 1] - positions[i - 1] + 1;
        if (current_length < min_length) {
            min_length = current_length;
        }
    }

    printf("%d\n", min_length);
    return 0;
}