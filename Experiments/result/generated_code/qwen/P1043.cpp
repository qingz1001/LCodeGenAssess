#include <stdio.h>
#include <stdlib.h>

#define MOD 10

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min_sum = 0, max_sum = 0;

    // Calculate minimum sum
    for (int i = 0; i < n; i++) {
        min_sum += arr[i];
        if (i >= m - 1) {
            min_sum -= arr[i - m + 1];
        }
        if (min_sum < 0) {
            min_sum = 0;
        }
    }
    min_sum %= MOD;

    // Calculate maximum sum
    for (int i = 0; i < n; i++) {
        max_sum += arr[i];
        if (i >= m - 1) {
            max_sum -= arr[i - m + 1];
        }
        if (max_sum > 0) {
            max_sum = 0;
        }
    }
    max_sum %= MOD;

    printf("%d\n%d\n", min_sum, max_sum);

    free(arr);
    return 0;
}