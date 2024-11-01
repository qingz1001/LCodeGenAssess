#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int nums[3];
    scanf("%d %d %d", &nums[0], &nums[1], &nums[2]);
    
    qsort(nums, 3, sizeof(int), compare);
    
    int d1 = nums[1] - nums[0];
    int d2 = nums[2] - nums[1];
    
    if (d1 == d2) {
        printf("%d\n", nums[2] + d1);
    } else if (d1 > d2) {
        printf("%d\n", nums[0] + d2);
    } else {
        printf("%d\n", nums[1] + d1);
    }
    
    return 0;
}