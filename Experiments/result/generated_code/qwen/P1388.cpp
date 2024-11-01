#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculate(int *arr, int n, int k) {
    if (k == 0) {
        int result = 1;
        for (int i = 0; i < n; i++) {
            result *= arr[i];
        }
        return result;
    }

    int max_result = 0;
    for (int i = 1; i <= k; i++) {
        int left = calculate(arr, i, i - 1);
        int right = calculate(arr + i, n - i, k - i);
        max_result = max(max_result, left * right);
    }

    return max_result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d\n", calculate(arr, n, k));

    free(arr);
    return 0;
}