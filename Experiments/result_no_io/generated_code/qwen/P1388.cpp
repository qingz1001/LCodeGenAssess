#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculate(int* nums, int n, int k, int pos, int sum, int mul) {
    if (pos == n) {
        return sum + mul;
    }
    int result = 0;
    for (int i = pos; i < n - 1; i++) {
        int nextSum = sum + mul * nums[i];
        int nextMul = nums[i + 1];
        result = max(result, calculate(nums, n, k - 1, i + 1, nextSum, nextMul));
    }
    result = max(result, calculate(nums, n, k, n, sum + mul * nums[n - 1], 0));
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int result = calculate(nums, n, k, 0, 0, nums[0]);
    printf("%d\n", result);

    free(nums);
    return 0;
}