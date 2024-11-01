#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += a[i];
    }

    int max_subarray_sum = a[0], min_subarray_sum = a[0];
    int current_max = a[0], current_min = a[0];

    for (int i = 1; i < n; i++) {
        current_max = MAX(a[i], current_max + a[i]);
        max_subarray_sum = MAX(max_subarray_sum, current_max);

        current_min = MIN(a[i], current_min + a[i]);
        min_subarray_sum = MIN(min_subarray_sum, current_min);
    }

    int result = MAX(max_subarray_sum, total_sum - min_subarray_sum);
    if (result == 0 && max_subarray_sum != 0) {
        result = max_subarray_sum;
    }

    printf("%d\n", result);

    free(a);
    return 0;
}