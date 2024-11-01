#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maxSubArray(int* nums, int numsSize) {
    int max_ending_here = nums[0];
    int max_so_far = nums[0];
    for (int i = 1; i < numsSize; i++) {
        max_ending_here = MAX(nums[i], max_ending_here + nums[i]);
        max_so_far = MAX(max_so_far, max_ending_here);
    }
    return max_so_far;
}

int minSubArray(int* nums, int numsSize) {
    int min_ending_here = nums[0];
    int min_so_far = nums[0];
    for (int i = 1; i < numsSize; i++) {
        min_ending_here = MIN(nums[i], min_ending_here + nums[i]);
        min_so_far = MIN(min_so_far, min_ending_here);
    }
    return min_so_far;
}

int maxTwoSubArrays(int* nums, int numsSize) {
    int max_sum = INT_MIN;
    int total_sum = 0;

    for (int i = 0; i < numsSize; i++) {
        total_sum += nums[i];
    }

    int max_straight_sum = maxSubArray(nums, numsSize);
    int min_straight_sum = minSubArray(nums, numsSize);

    int max_wrap_sum = total_sum - min_straight_sum;

    if (max_wrap_sum == 0) {
        max_wrap_sum = INT_MIN;
    }

    max_sum = MAX(max_straight_sum, max_wrap_sum);

    return max_sum;
}

int main() {
    int n;
    scanf("%d", &n);
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int result = maxTwoSubArrays(a, n);
    printf("%d\n", result);

    free(a);
    return 0;
}