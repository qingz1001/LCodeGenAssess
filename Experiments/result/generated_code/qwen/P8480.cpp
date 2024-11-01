#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Find the minimum and maximum values in the array
    int min_val = a[0];
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) min_val = a[i];
        if (a[i] > max_val) max_val = a[i];
    }

    // The maximum possible difference after m operations is achieved by either
    // increasing the minimum value or decreasing the maximum value as much as possible.
    // Since each operation can increase or decrease the value by at most 2,
    // we need to consider the impact of m operations on both the minimum and maximum values.
    int new_min = min_val + 2 * m;
    int new_max = max_val - 2 * m;

    // Ensure that the new minimum and maximum are valid
    if (new_min < 0) new_min = 0;
    if (new_max < 0) new_max = 0;

    // Calculate the maximum possible difference
    int max_diff = new_max - new_min;

    printf("%d\n", max_diff);

    free(a);
    return 0;
}