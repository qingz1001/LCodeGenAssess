#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int cmp(const void *a, const void *b){
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if(int_a < int_b) return -1;
    else if(int_a > int_b) return 1;
    else return 0;
}

int main(){
    int nums[3];
    scanf("%d %d %d", &nums[0], &nums[1], &nums[2]);
    qsort(nums, 3, sizeof(int), cmp);
    int d1 = nums[1] - nums[0];
    int d2 = nums[2] - nums[1];
    if(d1 == d2){
        printf("%d\n", nums[2] + d1);
    }
    else{
        if(d1 < d2){
            printf("%d\n", nums[1] + d1);
        }
        else{
            printf("%d\n", nums[0] + d2);
        }
    }
    return 0;
}