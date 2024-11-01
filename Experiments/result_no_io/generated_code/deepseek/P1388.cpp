#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int calculate(int *nums, int *ops, int n) {
    int result = nums[0];
    for (int i = 0; i < n - 1; i++) {
        if (ops[i] == 0) {
            result += nums[i + 1];
        } else {
            result *= nums[i + 1];
        }
    }
    return result;
}

int maxResult(int *nums, int n, int k) {
    int *ops = (int *)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        ops[i] = (i < k) ? 1 : 0;
    }

    int max_result = INT_MIN;
    do {
        max_result = max(max_result, calculate(nums, ops, n));
    } while (next_permutation(ops, n - 1));

    free(ops);
    return max_result;
}

int next_permutation(int *arr, int len) {
    int i = len - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }
    if (i < 0) {
        return 0;
    }

    int j = len - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    for (int k = i + 1, l = len - 1; k < l; k++, l--) {
        temp = arr[k];
        arr[k] = arr[l];
        arr[l] = temp;
    }
    return 1;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int result = maxResult(nums, n, k);
    printf("%d\n", result);

    free(nums);
    return 0;
}