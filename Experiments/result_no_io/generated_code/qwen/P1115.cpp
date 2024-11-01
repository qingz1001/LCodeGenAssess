#include <stdio.h>
#include <stdlib.h>

int maxSubArray(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    int max_current = nums[0];
    int max_global = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        max_current = fmax(nums[i], max_current + nums[i]);
        if (max_current > max_global) {
            max_global = max_current;
        }
    }
    
    return max_global;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    printf("%d\n", maxSubArray(nums, n));
    
    free(nums);
    return 0;
}