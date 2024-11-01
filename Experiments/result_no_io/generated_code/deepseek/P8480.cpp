#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max_val = INT_MIN;
    int min_val = INT_MAX;

    for (int i = 0; i < n; i++) {
        max_val = max(max_val, a[i]);
        min_val = min(min_val, a[i]);
    }

    for (int i = 0; i < m; i++) {
        if (max_val - min_val == 0) {
            max_val *= 2;
        } else {
            if (max_val - min_val < 2) {
                max_val *= 2;
            } else {
                max_val += 2;
                min_val -= 2;
            }
        }
    }

    printf("%d\n", max_val - min_val);

    free(a);
    return 0;
}