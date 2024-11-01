#include <stdio.h>
#include <stdlib.h>

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

    int max_val = a[0], min_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) max_val = a[i];
        if (a[i] < min_val) min_val = a[i];
    }

    for (int i = 0; i < m; i++) {
        int new_max_val = max(max_val + 2, max_val * 2);
        int new_min_val = min(min_val - 2, min_val / 2);
        max_val = new_max_val;
        min_val = new_min_val;
    }

    printf("%d\n", max_val - min_val);

    free(a);
    return 0;
}